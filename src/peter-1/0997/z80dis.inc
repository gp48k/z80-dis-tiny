
	include	def.inc
	include	deftok.inc

; C register bit flags
FLAG_ixy	equ	0
FLAG_s6		equ	1

z80dis:
	push	de	; use DE to old the rule table

	push	hl

	; IX/IY displacement always at third byte
	inc	hl
	inc	hl
	ld	a,(hl)

	ld	hl,'H'+'L'*256+0x8000
	ld	(reg_hl),hl

	pop	hl

	ld	(reg_disp),a

	ld	de,rule_00

	ld	c,0
	ld	a,(hl)
	cp	0xdd
	jr	nz,not_ix
	ld	a,'X'+0x80
	jr	load_regname
not_ix:
	cp	0xfd
	jr	nz,not_iy
	ld	a,'Y'+0x80
load_regname:
	set	FLAG_ixy,c		; ixy
	ld	(reg_hl+1),a
	ld	a,'I'
	ld	(reg_hl),a
	inc	hl			; skip dd/fd
	ld	a,(hl)		; get opcode
	; fall through for ed/cb detection
not_iy:
	cp	0xed
	jr	nz,not_ed
	ld	de,rule_ed
	inc	hl			; skip ed
not_ed:
	cp	0xcb
	jr	nz,end_setup
	ld	de,rule_cb
	inc	hl			; skip cb
	bit	FLAG_ixy,c		; ixy	
	jr	z,noixy
	inc	hl			; skip displacement
noixy:
; top of decoding loop
not_cb:
end_setup:
; set up some other "reg"
	ld	a,(hl)		; get opcode
	ld	(reg_op),a	; save opcode

; adjust table based on reg_op
	rlca			; shift 2 high bits to low
	rlca
	and	3		; and mask them

; find offset into table, working backwards from start
	push	de
	exx

	pop	hl

	ld	de,0
	jr	z,no_offset
; SEEMS like a 16-bit add would work?
	push	hl
	ld	b,a
offset_lp:
	dec	hl
; add (hl) to de
	ld	a,(hl)
	add   a,e    ; A = A+E
	ld    e,a    ; E = A+E
	adc   a,d    ; A = A+E+D+carry
	sub   e      ; A = D+carry
	ld    d,a    ; D = D+carry

	djnz	offset_lp

	pop	hl
	add	hl,de
no_offset:

	push	hl
	pop	ix

	exx

	pop	de

decode_match:
	ld	b,(ix+0)	; cmd byte code

	include	dispatch.inc

	include	table.inc

