#
# check.pl -- measure and test a disassembler
#

@ARGV == 1 || die "usage: check.pl assembler.inc\n";

$src = $ARGV[0];
$src =~ s'\\'/'g;

# Assemble just the disassembler to get the code and data sizes.

$bds = 'x-size.bds';
unlink($bds);
system('zmac', '-o', $bds, $src);
-f $bds || die "check.pl: failed to assemble '$src'\n";

$low = 0x10000;
$high = -1;
open(BDS, "<$bds") || die "check.pl: can't read '$bds': $!\n";
while (<BDS>) {
	chomp;
	@r = split(' ');
	if ($r[2] eq 'u') {
		$addr = hex($r[0]);
		$len = hex($r[3]);
		$type = hex($r[4]);
		for ($i = 0; $i < $len; $i++) {
			$usage[$addr + $i] = $type;
		}
		$low = $addr if $addr < $low;
		$high = $addr + $len - 1 if $addr + $len -1 > $high;
	}
}
close BDS;

$code = $data = $both = 0;
foreach (@usage) {
	$u = $_ & 3;
	if ($u == 3) {
		$both++;
	}
	else {
		$code++ if $u & 1;
		$data++ if $u & 2;
	}
}

$total = $code + $data + $both;
print "$total: $code code $data data $both both\n";

# So much for the raw numbers, now apply the "2 contiguous regions" rule.

$gap = 0;
for ($i = $low; $i <= $high; $i++) {
	if ($usage[$i] eq '') {
		$gap0 = $i if $gap == 0;
		$gap++;
	}
	else {
		if ($gap > $gap_len) {
			$gap_len = $gap;
			$gap_low = $gap0;
		}
		$gap = 0;
	}
}

if ($gap_len > 0) {
	$gap_high = $gap_low + $gap_len - 1;
	print "found $gap_len gap at $addr [ $gap_low $gap_high ]\n";
	$regsize = ($gap_low - $low) + ($high - $gap_high);
	$regions = 2;
}
else {
	$regsize = $high - $low + 1;
	$regions = 1;
}
print "$regsize bytes in $regions regions\n";

# Assemble with framework to test against valid.inc

$vwrap = 'x-vwrap.z';
open(VWRAP, ">$vwrap") || die "check.pl: can't write '$vwrap': $!\n";
print VWRAP <<EOV;
	include	$src

	include	testbed.inc
start:
	ld	sp,\$d000
	ld	hl,valid
	ld	de,valid_len
	call	disblock
	jr	\$

	org	\$8000
valid:
	include	valid.inc
valid_len equ \$-valid
	end	start
EOV
close VWRAP;

$cmd = 'x-vwrap.cmd';
unlink($cmd);
system('zmac', '-o', $cmd, $vwrap);
-f $cmd || die "check.pl: failed to assemble '$vwrap'\n";

# Check that valid.inc comes out correctly

open(VALID, "<valid.inc") || die "check.pl: can't read 'valid.inc': $!\n";
open(TEST1, "rz80 -nostats $cmd|") || die "check.pl: can't run rz80 on '$cmd': $!\n";
$n = 1;
while (<TEST1>) {
	chomp;
	$v = <VALID>;
	chomp $v;
	if ($_ ne $v) {
		print "Disassembly failure on line $n\n";
		print "valid.inc :$_\n";
		print "disassmbly:$v\n";
		exit 1;
	}
	$n++;
}
close VALID;
close TEST1;

print "valid.inc checks out\n";

# Run again to get statistics.
open(STAT, "rz80 $cmd|") || die "check.pl: can't run rz80 on '$cmd': $!\n";
while (<STAT>) {
	if (/^(\d+)\s+cycles\s+(\d+)\s+instructions/) {
		$cyc = $1;
		$inst = $2;
	}
}
close STAT;
if ($cyc eq '') {
	print "Huh, no run statistics.\n";
}
else {
	$cyc_line = int($cyc / $n + 0.5);
	print "$cyc cycles $inst instructions; $cyc_line cycles/line\n";
}

# Run once more to get stack usage.

# We'll assume that, even with a gap, tracking stack usage over $low .. $high
# will give the correct answer.  Based on the theory that nothing will be
# running in the gap.

$stack_track = '';
$normal = 0;
if ($high < 0x8000) {
	$stack_track = sprintf('-stack-track %x %x ', $low, $high);
	$normal = 1;
}
open(RUN, "rz80 -t -t $stack_track $cmd|") || die "check.pl: can't run rz80 on '$cmd': $!\n";
while (<RUN>) {
	last if /cycles/;
	next unless /SP\=(\S\S\S\S)\s(\S\S\S\S)/;
	$sp = hex($1);
	$pc = hex($2);
	$seen{$sp}++ if $normal && $pc >= $low && $pc <= $high;
	$seen{$sp}++ if !$normal && $pc > $gap_high || $pc < $gap_low;
}
close RUN;

$stack_low = -1;
$sep = '';
foreach (sort { $a <=> $b; } keys(%seen)) {
	$stack_low = $_ if $stack_low == -1;
	$stack_high = $_;
	printf "$sep%04x", $_;
	$sep = ' ';
}
print "\n";

$stack = $stack_high - $stack_low;

print "$stack bytes stack\n";

$measured_size = $regsize + $stack;
$code_both = $code + $both;
print "$src =========== $measured_size =========== $code_both $data $stack $cyc_line\n";

# Check that invalid.inc is reasonable.

$iwrap = 'x-iwrap.z';
open(IWRAP, ">$iwrap") || die "check.pl: can't write '$iwrap': $!\n";
print IWRAP <<EOV;
	include	$src

dishex_output equ 1

	include	testbed.inc
start:
	ld	sp,\$d000
	ld	hl,invalid
	ld	de,invalid_len
	call	disblock
	jr	\$

	org	\$8000
invalid:
	include	invalid.inc
invalid_len equ \$-invalid
	end	start
EOV
close IWRAP;

$icmd = 'x-iwrap.cmd';
unlink($icmd);
system('zmac', '-o', $icmd, $iwrap);
-f $icmd || die "check.pl: failed to assemble '$iwrap'\n";

# Check that valid.inc comes out correctly

open(TEST2, "rz80 -nostats $icmd|") || die "check.pl: can't run rz80 on '$icmd': $!\n";
$bad = 0;
$iline = 0;
while (<TEST2>) {
	chomp;
	if (!/^([0-9A-F]{4}): /) {
		print "bad line: $_\n";
		$bad = 1;
		last;
	}

	$addr = $1;
	$iline++ if $addr =~ /[048C]$/;

	if (/[\x00-\x1f\x7f-\xff]/) {
		$a = unpack('C', $&);
		print "non ASCII ($a): $_\n";
		$bad = 1;
		last;
	}
}
close TEST2;

if ($iline != 1088) {
	print "$iline lines instead of 1088\n";
	$bad = 1;
}

if ($bad) {
	print "FAILURE on invalid.inc\n";
}
else {
	print "invalid.inc checks out\n";
}
