; current sizesize: 859+12 stack = 871

	org	0x10000 - (dollar_hex - origin) + 0x10
origin:
	include	def.inc
	include	deftok.inc
	include	token.inc

; C register bit flags
FLAG_ixy	equ	1
FLAG_s6		equ	0

z80dis:
	push	de	; use DE to hold the rule table

	push	hl

	; IX/IY displacement always at third byte
	inc	hl
	inc	hl
	ld	a,(hl)

	pop	hl

	ld	iyl,a

	; use BC for regname
	ld	bc,0
	org	$-2
	token	"HL"			; C = $90 => FLAG_ixy = 0, FLAG_s6 = 0

	ld	a,(hl)
	cp	0xdd
	jr	nz,not_ix
	ld	bc,0
	org	$-2
	token	"IX"			; C = $92 => FLAG_ixy = 1, FLAG_s6 = 0
	jr	load_ixy_regname
not_ix:
	cp	0xfd
	jr	nz,not_iy
	ld	bc,0
	org	$-2
	token	"IY"			; C = $92 => FLAG_ixy = 1, FLAG_s6 = 0
load_ixy_regname:
	inc	hl			; skip dd/fd
	ld	a,(hl)			; get opcode
	; fall through for ed/cb detection
not_iy:
	ld	(reg_hl),bc
	ld	de,table_start

	cp	0xed
	jr	nz,not_ed
	ld	e,((rule_ed - table_start) & 0xff00) + (rule_ed & 0xff)		; must stay on same page
	inc	hl			; skip ed
not_ed:
	cp	0xcb
	jr	nz,end_setup
	ld	e,((rule_cb - table_start) & 0xff00) + (rule_cb & 0xff)		; must stay on same page
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

