;
; Example competition entry.
; Currently has 6457 bytes of code and data.  It uses at most 8 bytes of stack
; (not including the return address of the z80dis call).
; This makes the size of the entry 6465 bytes.

distab:	ascii	"NOP|LD BC,w|LD (BC),A|INC BC|INC B|DEC B|LD B,n|RLCA|"
	ascii	"EX AF,AF'|ADD HL,BC|LD A,(BC)|DEC BC|INC C|DEC C|LD C,n|RRCA|"
	ascii	"DJNZ b|LD DE,w|LD (DE),A|INC DE|INC D|DEC D|LD D,n|RLA|"
	ascii	"JR b|ADD HL,DE|LD A,(DE)|DEC DE|INC E|DEC E|LD E,n|RRA|"
	ascii	"JR NZ,b|LD HL,w|LD (w),HL|INC HL|INC H|DEC H|LD H,n|DAA|"
	ascii	"JR Z,b|ADD HL,HL|LD HL,(w)|DEC HL|INC L|DEC L|LD L,n|CPL|"
	ascii	"JR NC,b|LD SP,w|LD (w),A|INC SP|INC (HL)|DEC (HL)|LD (HL),n|SCF|"
	ascii	"JR C,b|ADD HL,SP|LD A,(w)|DEC SP|INC A|DEC A|LD A,n|CCF|"

	ascii	"LD B,B|LD B,C|LD B,D|LD B,E|LD B,H|LD B,L|LD B,(HL)|LD B,A|"
	ascii	"LD C,B|LD C,C|LD C,D|LD C,E|LD C,H|LD C,L|LD C,(HL)|LD C,A|"
	ascii	"LD D,B|LD D,C|LD D,D|LD D,E|LD D,H|LD D,L|LD D,(HL)|LD D,A|"
	ascii	"LD E,B|LD E,C|LD E,D|LD E,E|LD E,H|LD E,L|LD E,(HL)|LD E,A|"
	ascii	"LD H,B|LD H,C|LD H,D|LD H,E|LD H,H|LD H,L|LD H,(HL)|LD H,A|"
	ascii	"LD L,B|LD L,C|LD L,D|LD L,E|LD L,H|LD L,L|LD L,(HL)|LD L,A|"
	ascii	"LD (HL),B|LD (HL),C|LD (HL),D|LD (HL),E|LD (HL),H|LD (HL),L|HALT|LD (HL),A|"
	ascii	"LD A,B|LD A,C|LD A,D|LD A,E|LD A,H|LD A,L|LD A,(HL)|LD A,A|"

	ascii	"ADD A,B|ADD A,C|ADD A,D|ADD A,E|ADD A,H|ADD A,L|ADD A,(HL)|ADD A,A|"
	ascii	"ADC A,B|ADC A,C|ADC A,D|ADC A,E|ADC A,H|ADC A,L|ADC A,(HL)|ADC A,A|"
	ascii	"SUB B|SUB C|SUB D|SUB E|SUB H|SUB L|SUB (HL)|SUB A|"
	ascii	"SBC A,B|SBC A,C|SBC A,D|SBC A,E|SBC A,H|SBC A,L|SBC A,(HL)|SBC A,A|"
	ascii	"AND B|AND C|AND D|AND E|AND H|AND L|AND (HL)|AND A|"
	ascii	"XOR B|XOR C|XOR D|XOR E|XOR H|XOR L|XOR (HL)|XOR A|"
	ascii	"OR B|OR C|OR D|OR E|OR H|OR L|OR (HL)|OR A|"
	ascii	"CP B|CP C|CP D|CP E|CP H|CP L|CP (HL)|CP A|"

	ascii	"RET NZ|POP BC|JP NZ,w|JP w|CALL NZ,w|PUSH BC|ADD A,n|RST t|"
	ascii	"RET Z|RET|JP Z,w|c|CALL Z,w|CALL w|ADC A,n|RST t|"
	ascii	"RET NC|POP DE|JP NC,w|OUT (n),A|CALL NC,w|PUSH DE|SUB n|RST t|"
	ascii	"RET C|EXX|JP C,w|IN A,(n)|CALL C,w|x|SBC A,n|RST t|"
	ascii	"RET NV|POP HL|JP NV,w|EX (SP),HL|CALL NV,w|PUSH HL|AND n|RST t|"
	ascii	"RET V|JP (HL)|JP V,w|EX DE,HL|CALL V,w|e|XOR n|RST t|"
	ascii	"RET P|POP AF|JP P,w|DI|CALL P,w|PUSH AF|OR n|RST t|"
	ascii	"RET M|LD SP,HL|JP M,w|EI|CALL M,w|y|CP n|RST t|"

cbtab:	ascii	"RLC B|RLC C|RLC D|RLC E|RLC H|RLC L|RLC (HL)|RLC A|"
	ascii	"RRC B|RRC C|RRC D|RRC E|RRC H|RRC L|RRC (HL)|RRC A|"
	ascii	"RL B|RL C|RL D|RL E|RL H|RL L|RL (HL)|RL A|"
	ascii	"RR B|RR C|RR D|RR E|RR H|RR L|RR (HL)|RR A|"
	ascii	"SLA B|SLA C|SLA D|SLA E|SLA H|SLA L|SLA (HL)|SLA A|"
	ascii	"SRA B|SRA C|SRA D|SRA E|SRA H|SRA L|SRA (HL)|SRA A|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"SRL B|SRL C|SRL D|SRL E|SRL H|SRL L|SRL (HL)|SRL A|"
	ascii	"BIT 0,B|BIT 0,C|BIT 0,D|BIT 0,E|BIT 0,H|BIT 0,L|BIT 0,(HL)|BIT 0,A|"
	ascii	"BIT 1,B|BIT 1,C|BIT 1,D|BIT 1,E|BIT 1,H|BIT 1,L|BIT 1,(HL)|BIT 1,A|"
	ascii	"BIT 2,B|BIT 2,C|BIT 2,D|BIT 2,E|BIT 2,H|BIT 2,L|BIT 2,(HL)|BIT 2,A|"
	ascii	"BIT 3,B|BIT 3,C|BIT 3,D|BIT 3,E|BIT 3,H|BIT 3,L|BIT 3,(HL)|BIT 3,A|"
	ascii	"BIT 4,B|BIT 4,C|BIT 4,D|BIT 4,E|BIT 4,H|BIT 4,L|BIT 4,(HL)|BIT 4,A|"
	ascii	"BIT 5,B|BIT 5,C|BIT 5,D|BIT 5,E|BIT 5,H|BIT 5,L|BIT 5,(HL)|BIT 5,A|"
	ascii	"BIT 6,B|BIT 6,C|BIT 6,D|BIT 6,E|BIT 6,H|BIT 6,L|BIT 6,(HL)|BIT 6,A|"
	ascii	"BIT 7,B|BIT 7,C|BIT 7,D|BIT 7,E|BIT 7,H|BIT 7,L|BIT 7,(HL)|BIT 7,A|"
	ascii	"RES 0,B|RES 0,C|RES 0,D|RES 0,E|RES 0,H|RES 0,L|RES 0,(HL)|RES 0,A|"
	ascii	"RES 1,B|RES 1,C|RES 1,D|RES 1,E|RES 1,H|RES 1,L|RES 1,(HL)|RES 1,A|"
	ascii	"RES 2,B|RES 2,C|RES 2,D|RES 2,E|RES 2,H|RES 2,L|RES 2,(HL)|RES 2,A|"
	ascii	"RES 3,B|RES 3,C|RES 3,D|RES 3,E|RES 3,H|RES 3,L|RES 3,(HL)|RES 3,A|"
	ascii	"RES 4,B|RES 4,C|RES 4,D|RES 4,E|RES 4,H|RES 4,L|RES 4,(HL)|RES 4,A|"
	ascii	"RES 5,B|RES 5,C|RES 5,D|RES 5,E|RES 5,H|RES 5,L|RES 5,(HL)|RES 5,A|"
	ascii	"RES 6,B|RES 6,C|RES 6,D|RES 6,E|RES 6,H|RES 6,L|RES 6,(HL)|RES 6,A|"
	ascii	"RES 7,B|RES 7,C|RES 7,D|RES 7,E|RES 7,H|RES 7,L|RES 7,(HL)|RES 7,A|"
	ascii	"SET 0,B|SET 0,C|SET 0,D|SET 0,E|SET 0,H|SET 0,L|SET 0,(HL)|SET 0,A|"
	ascii	"SET 1,B|SET 1,C|SET 1,D|SET 1,E|SET 1,H|SET 1,L|SET 1,(HL)|SET 1,A|"
	ascii	"SET 2,B|SET 2,C|SET 2,D|SET 2,E|SET 2,H|SET 2,L|SET 2,(HL)|SET 2,A|"
	ascii	"SET 3,B|SET 3,C|SET 3,D|SET 3,E|SET 3,H|SET 3,L|SET 3,(HL)|SET 3,A|"
	ascii	"SET 4,B|SET 4,C|SET 4,D|SET 4,E|SET 4,H|SET 4,L|SET 4,(HL)|SET 4,A|"
	ascii	"SET 5,B|SET 5,C|SET 5,D|SET 5,E|SET 5,H|SET 5,L|SET 5,(HL)|SET 5,A|"
	ascii	"SET 6,B|SET 6,C|SET 6,D|SET 6,E|SET 6,H|SET 6,L|SET 6,(HL)|SET 6,A|"
	ascii	"SET 7,B|SET 7,C|SET 7,D|SET 7,E|SET 7,H|SET 7,L|SET 7,(HL)|SET 7,A|"

idxtab:	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|ADD i,BC|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|ADD i,DE|?|?|?|?|?|?|"
	ascii	"?|LD i,w|LD (w),i|INC i|?|?|?|?|"
	ascii	"?|ADD i,i|LD i,(w)|DEC i|?|?|?|?|"
	ascii	"?|?|?|?|INC (id)|DEC (id)|LD (id),n|?|"
	ascii	"?|ADD i,SP|?|?|?|?|?|?|"

	ascii	"?|?|?|?|?|?|LD B,(id)|?|"
	ascii	"?|?|?|?|?|?|LD C,(id)|?|"
	ascii	"?|?|?|?|?|?|LD D,(id)|?|"
	ascii	"?|?|?|?|?|?|LD E,(id)|?|"
	ascii	"?|?|?|?|?|?|LD H,(id)|?|"
	ascii	"?|?|?|?|?|?|LD L,(id)|?|"
	ascii	"LD (id),B|LD (id),C|LD (id),D|LD (id),E|LD (id),H|LD (id),L|?|LD (id),A|"
	ascii	"?|?|?|?|?|?|LD A,(id)|?|"

	ascii	"?|?|?|?|?|?|ADD A,(id)|?|"
	ascii	"?|?|?|?|?|?|ADC A,(id)|?|"
	ascii	"?|?|?|?|?|?|SUB (id)|?|"
	ascii	"?|?|?|?|?|?|SBC A,(id)|?|"
	ascii	"?|?|?|?|?|?|AND (id)|?|"
	ascii	"?|?|?|?|?|?|XOR (id)|?|"
	ascii	"?|?|?|?|?|?|OR (id)|?|"
	ascii	"?|?|?|?|?|?|CP (id)|?|"

	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|z|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|POP i|?|EX (SP),i|?|PUSH i|?|?|"
	ascii	"?|JP (i)|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|LD SP,i|?|?|?|?|?|?|"

edtab:	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"

	ascii	"IN B,(C)|OUT (C),B|SBC HL,BC|LD (w),BC|NEG|RETN|IM 0|LD I,A|"
	ascii	"IN C,(C)|OUT (C),C|ADC HL,BC|LD BC,(w)|?|RETI|?|LD R,A|"
	ascii	"IN D,(C)|OUT (C),D|SBC HL,DE|LD (w),DE|?|?|IM 1|LD A,I|"
	ascii	"IN E,(C)|OUT (C),E|ADC HL,DE|LD DE,(w)|?|?|IM 2|LD A,R|"
	ascii	"IN H,(C)|OUT (C),H|SBC HL,HL|LD (w),HL|?|?|?|RRD|"
	ascii	"IN L,(C)|OUT (C),L|ADC HL,HL|LD HL,(w)|?|?|?|RLD|"
	ascii	"?|?|SBC HL,SP|LD (w),SP|?|?|?|?|"
	ascii	"IN A,(C)|OUT (C),A|ADC HL,SP|LD SP,(w)|?|?|?|?|"

	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"LDI|CPI|INI|OUTI|?|?|?|?|"
	ascii	"LDD|CPD|IND|OUTD|?|?|?|?|"
	ascii	"LDIR|CPIR|INIR|OTIR|?|?|?|?|"
	ascii	"LDDR|CPDR|INDR|OTDR|?|?|?|?|"

	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|?|?|"

cbitab:	ascii	"?|?|?|?|?|?|RLC (if)|?|"
	ascii	"?|?|?|?|?|?|RRC (if)|?|"
	ascii	"?|?|?|?|?|?|RL (if)|?|"
	ascii	"?|?|?|?|?|?|RR (if)|?|"
	ascii	"?|?|?|?|?|?|SLA (if)|?|"
	ascii	"?|?|?|?|?|?|SRA (if)|?|"
	ascii	"?|?|?|?|?|?|?|?|"
	ascii	"?|?|?|?|?|?|SRL (if)|?|"

	ascii	"?|?|?|?|?|?|BIT 0,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 1,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 2,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 3,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 4,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 5,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 6,(if)|?|"
	ascii	"?|?|?|?|?|?|BIT 7,(if)|?|"

	ascii	"?|?|?|?|?|?|RES 0,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 1,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 2,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 3,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 4,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 5,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 6,(if)|?|"
	ascii	"?|?|?|?|?|?|RES 7,(if)|?|"

	ascii	"?|?|?|?|?|?|SET 0,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 1,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 2,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 3,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 4,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 5,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 6,(if)|?|"
	ascii	"?|?|?|?|?|?|SET 7,(if)|?|"

z80dis:	ld	ix,distab
dis:	ld	b,(hl)
	inc	hl
	inc	b
	jr	check
skip:	ld	a,(ix)
	inc	ix
	cp	'|'
	jr	nz,skip
check:	dec	b
	jr	nz,skip

echo:	xor	a
	ld	(de),a
	ld	a,(ix)
	inc	ix
	cp	'|'
	ret	z
	cp	'a'
	jr	nc,special
	ld	(de),a
	inc	de
	jr	echo

special:
	ld	iy,command
dispatch:
	cp	(iy)
	inc	iy
	jr	z,go
	inc	iy
	inc	iy
	inc	iy
	jr	dispatch
go:	jp	(iy)

emit_branch:
	ld	a,(hl)
	inc	hl
	push	hl
	push	de
	ld	e,a
	add	a,a
	sbc	a,a
	ld	d,a
	add	hl,de
	pop	de
	ld	a,'$'
	ld	(de),a
	inc	de
	ld	a,h
	call	hex
	ld	a,l
	call	hex
	pop	hl
	jr	echo

emit_byte:
	ld	a,'$'
	ld	(de),a
	inc	de
	ld	a,(hl)
	inc	hl
	call	hex
	jr	echo

emit_word:
	ld	a,'$'
	ld	(de),a
	inc	de
	ld	a,(hl)
	inc	hl
	push	af
	ld	a,(hl)
	inc	hl
	call	hex
	pop	af
	call	hex
	jr	echo

emit_rst:
	ld	a,'$'
	ld	(de),a
	inc	de
	dec	hl
	ld	a,(hl)
	inc	hl
	and	$38
	call	hex
	jr	echo

do_cb:	ld	ix,cbtab
	jp	dis

do_ed:	ld	ix,edtab
	jp	dis

do_ix:	ld	c,'X'
	jr	do_idx
do_iy:	ld	c,'Y'
do_idx:	ld	ix,idxtab
	jp	dis

emit_ixy:
	ld	a,'I'
	ld	(de),a
	inc	de
	ld	a,c
	ld	(de),a
	inc	de
	jp	echo

cbdisp:	defb	0
emit_cbdisp:
	ld	a,(cbdisp)
	ld	b,a
	jr	disp
emit_disp:
	ld	b,(hl)
	inc	hl
disp:	ld	a,'+'
	bit	7,b
	jr	z,pos
	ld	a,b
	neg
	ld	b,a
	ld	a,'-'
pos:	ld	(de),a
	inc	de
	ld	a,'$'
	ld	(de),a
	inc	de
	ld	a,b
	call	hex
	jp	echo

do_cbixy:
	ld	a,(hl)
	inc	hl
	ld	(cbdisp),a
	ld	ix,cbitab
	jp	dis

command:
	defb	'w'
	jp	emit_word
	defb	'n'
	jp	emit_byte
	defb	'b'
	jp	emit_branch
	defb	't'
	jp	emit_rst
	defb	'c'
	jp	do_cb
	defb	'e'
	jp	do_ed
	defb	'x'
	jp	do_ix
	defb	'y'
	jp	do_iy
	defb	'i'
	jp	emit_ixy
	defb	'd'
	jp	emit_disp
	defb	'f'
	jp	emit_cbdisp
	defb	'z'
	jp	do_cbixy

hex:	push	af
	rra
	rra
	rra
	rra
	call	hex1
	pop	af
hex1:	and	$f
	add	'0'
	cp	'9'+1
	jr	c,isdig
	add	'A'-'0'-10
isdig:	ld	(de),a
	inc	de
	ret
