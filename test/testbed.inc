;
; testbed.inc - call disassembler over a block of memory at HL for DE bytes.
;

buf:	defs	64

disblock:
	ex	de,hl
	add	hl,de
	ex	de,hl		; now DE points to end

dblp:	
	ifdef	dishex_output
	ld	a,h
	call	dshex
	ld	a,l
	call	dshex
	ld	a,':'
	out	($f8),a
	endif

	push	de
	ld	de,buf
	ld	b,64
	ld	a,'!'
fbuf:	ld	(de),a
	inc	de
	djnz	fbuf

	ld	de,buf
	call	z80dis

	ld	de,buf
	ld	a,' '
	out	($f8),a
	call	print
	pop	de
	push	hl
	or	a
	sbc	hl,de
	pop	hl
	jr	c,dblp		; keep going until reach or pass the end
	ret

print:	ld	a,(de)
	or	a
	jr	z,newline
	out	($f8),a
	inc	de
	jr	print
newline:
	ld	a,10
	out	($f8),a
	ret

	ifdef	dishex_output
dshex:	push	af
	rra
	rra
	rra
	rra
	call	dshex1
	pop	af
dshex1:	and	$f
	add	'0'
	cp	'9'+1
	jr	c,dsisdig
	add	'A'-'0'-10
dsisdig:
	out	($f8),a
	ret
	endif
