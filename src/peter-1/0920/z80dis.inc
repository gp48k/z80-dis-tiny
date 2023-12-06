
	include	def.inc
	include	deftok.inc

; C register bit flags
FLAG_ixy	equ	0
FLAG_s6		equ	1

z80dis:
	push	de	; use DE to hold the rule table

	push	hl

	; IX/IY displacement always at third byte
	inc	hl
	inc	hl
	ld	a,(hl)

	pop	hl

	ld	(reg_disp),a

	; use DE for regname
	ld	de,'H'+'L'*256+0x8000

	ld	c,0
	ld	a,(hl)
	cp	0xdd
	jr	nz,not_ix
	ld	d,'X'+0x80
	jr	load_ixy_regname
not_ix:
	cp	0xfd
	jr	nz,not_iy
	ld	d,'Y'+0x80
load_ixy_regname:
	inc	e	; H -> I
	set	FLAG_ixy,c		; ixy
	inc	hl			; skip dd/fd
	ld	a,(hl)		; get opcode
	; fall through for ed/cb detection
not_iy:
	ld	(reg_hl),de
	ld	de,rule_00

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

	push	de
	pop	ix

	neg
	jr	z,no_page_offset

	ld	(page_index),a
	ld	d,0
page_index	equ	$+2
	ld	e,(ix+0)
	add	ix,de
no_page_offset:

	pop	de	; restore original DE buffer

decode_match:
	ld	b,(ix+0)	; cmd byte code

	include	dispatch.inc

	include	table.inc

