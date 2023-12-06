
reg_op		defb	1
reg_disp	defb	1

	include	def.inc
	include	deftok.inc

z80dis:
	ld	BC,'H'+'L'*256+0x8000
	ld	(reg_hl),BC
	push	hl
	pop	ix

	; IX/IY displacement always at third byte
	ld	a,(ix+2)
	ld	(reg_disp),a

	ld	ix,rule_00

	ld	c,0
	ld	a,(hl)
	cp	0xdd
	jr	nz,not_ix
	set	0,c			; ixy
	ld	a,'X'+0x80
	jr	load_regname
not_ix:
	cp	0xfd
	jr	nz,not_iy
	set	0,c			; ixy
	ld	a,'Y'+0x80
load_regname:
	ld	(reg_hl+1),a
	ld	a,'I'
	ld	(reg_hl),a
	inc	hl			; skip dd/fd
	ld	a,(hl)		; get opcode
	; fall through for ed/cb detection
not_iy:
	cp	0xed
	jr	nz,not_ed
	ld	ix,rule_ed
	inc	hl			; skip ed
not_ed:
	cp	0xcb
	jr	nz,end_setup
	ld	ix,rule_cb
	inc	hl			; skip cb
	bit	0,c			; ixy	
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
	exx

	push	ix
	pop	hl

	ld	de,0
	jr	z,no_offset
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

	dec	hl	; decode loop needs -1
	push	hl
	pop	ix

	exx

decode_loop:
	inc 	ix
decode_int:
	ld	b,(ix+0)	; byte code
	call	dispatch
	bit	7,c;fail?
	jr	z,decode_loop	; command matched
	res	7,c;clear
; skip to next rule
rule_skip:
	ld	a,(ix+0)
	cp	1
	inc	ix
	jr	nz,rule_skip
	jr	decode_int	

	include	dispatch.inc

	include	table.inc

