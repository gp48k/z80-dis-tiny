
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

	ld	ix,rule_00-1

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
	ld	ix,rule_ed-1
	inc	hl			; skip ed
not_ed:
	cp	0xcb
	jr	nz,end_setup
	ld	ix,rule_cb-1
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

