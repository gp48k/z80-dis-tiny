; Dispatch routines have to return with "C"
; set 7,c for match failed

; table offsets
;alu_tab_off	equ	0
cbs_tab_off	equ	8
cc_tab_off	equ	16
ddss_tab_off	equ	24
reg_hl_off	equ	ddss_tab_off+2
qq_tab_off	equ	28
reg_tab_off	equ	32


dispatch:
	djnz	skip_1
	jr	end_rule
; end_rule / end_table both terminate 
; <cmd_end_rule>
skip_1:
	djnz	skip_7
; <cmd_end_table>
end_rule:
	xor	a
	ld	(de),a
	pop	bc		; skip return
	ret

skip_7:
	djnz	skip_8
; <cmd_disp>
	bit	0,c		; ixy
	ret	z
	inc	hl		; skip displacement byte
	ret

skip_8:
	djnz	skip_9
; <cmd_e>
	ld	a,(hl)		; branch offset
	inc	hl
	push	hl

	push	de
	ld	e,a
	add	a,a
	sbc	a,a
	ld	d,a
	add	hl,de
	pop	de

	ld	a,h
	call	dollar_hex
	ld	a,l
	call	hex2
	pop	hl
	ret
skip_9:
	djnz	skip_10
; <cmd_hl>
	; (HL) or IX+- DISP stuff
	ld	a,'('
	ld	(de),a
	inc	de
	ld	a,reg_hl_off
	call	str_tab_out
	bit	0,c
	jr	z,HL_only
	; +- reg_disp
	ld	a,'+'
	ld	(de),a
	ld	a,(reg_disp)
	or	a
	jp	p,positive
	ld	a,'-'
	ld	(de),a
	ld	a,(reg_disp)
	cpl	
	inc	a
positive:
	inc	de
	call	dollar_hex
HL_only:
	ld	a,')'
	ld	(de),a
	inc	de
	ret

skip_10:
	ld	a,(reg_op)
	djnz	skip_39a
; <cmd_rst>
	and	a,0x38
	jp	dollar_hex

skip_39a:
	djnz	skip_39
; <cmd_s>
	and	a,7		;reg_s
	jr	reg_tab_out

skip_39:
	djnz	skip_40
; <cmd_hack_inc>
hack_inc:
	inc	hl
	ret

skip_40:
; <cmd_jr>
	djnz	skip_21
	and	a,~0x18
	cp	0x20
	jr	z,hack_inc
	set	7,c;no match
	ret

; TODO -- we can get rid of some dec b/inc a for the 'comparisons' here.
; (seems like the 'dispatch' here could be optimized a bit, e.g. multiple subs)
skip_21:
	push	af
	ld	a,b
	sub	9
	jp	c,special_cmp_s
	inc	a
	ld	b,a
; <cmd_s0>

; <cmd_s1>

; <cmd_s2>

; <cmd_s3>

; <cmd_s4>

; <cmd_s5>

; <cmd_s6>

; <cmd_s7>

	sub	0xD		; only n0 .. nB used
	jp	c,special_cmp_n
	inc	a
	ld	b,a
	pop	af		; reg_op (used by reg_r)
; <cmd_n0>
; <cmd_n1>
; <cmd_n2>
; <cmd_n3>
; <cmd_n4>
; <cmd_n5>
; <cmd_n6>
; <cmd_n7>
; <cmd_n8>
; <cmd_n9>
; <cmd_nA>
; <cmd_nB>

	rra
	rra
	rra
	and	a,7		; reg_r
	djnz	skip_19a
; <cmd_rc>
	and	a,3		; only two bits valid
	add	a,cc_tab_off
	jr	str_tab_out

skip_19a:
	djnz	skip_19
; <cmd_n>
	ld	a,(hl)
	inc	hl
	jp	dollar_hex

skip_19:
	djnz	skip_20
; <cmd_nn>
cmd_nn_impl:
	inc	hl
	ld	a,(hl)
	call	dollar_hex
	dec	hl
	ld	a,(hl)
	inc	hl
	inc	hl
	jp	hex2

skip_20:
	djnz	skip_3
; <cmd_np>
	ld	a,'('
	ld	(de),a
	inc	de

	call	cmd_nn_impl

	jr	HL_only

skip_3:
	djnz	skip_4
; <cmd_b>
	add	a,'0'
	ld	(de),a
	inc	de
	ret

skip_4:
	djnz	skip_5
; <cmd_cbs>
	add	a,cbs_tab_off
	jr	str_tab_out

skip_5:
	djnz	skip_27a
; <cmd_cc>
	add	a,cc_tab_off
	jr	str_tab_out


skip_27a:
	djnz	skip_27b
; <cmd_alu>
	;add	a,alu_tab_off
	jr	str_tab_out

skip_27b:
	djnz	skip_27
; <cmd_r6>
	cp	6
	jr	byte_match_advance

skip_27:
	djnz	skip_25
; <cmd_r>
reg_tab_out:
	add	a,reg_tab_off
	jr	str_tab_out

skip_25:
; reg_dd is a shift of reg_r
	rra
	djnz	skip_6
; <cmd_qq>
	add	a,qq_tab_off
	jr	str_tab_out

skip_6:
	djnz	skip_29
; <cmd_dd>
	add	a,ddss_tab_off
	jr	str_tab_out

skip_29:
	djnz	skip_31
; <cmd_reghl>
	ld	a,reg_hl_off
	jr	str_tab_out

skip_31:

	ld	a,b
	sub	66		; 1..65 range
	jr	c,cmd_t_impl

	inc	a
	inc	a
	ld	b,a
	jr	skip_end

cmd_t_impl:
	ld	a,(reg_op)
	and	a,0x3f
	dec	b
	cp	a,b
	jr	byte_match_advance

; <cmd_t00>
; <cmd_t01>
; <cmd_t02>
; <cmd_t03>
; <cmd_t04>
; <cmd_t05>
; <cmd_t06>
; <cmd_t07>
; <cmd_t08>
; <cmd_t09>
; <cmd_t0A>
; <cmd_t0B>
; <cmd_t0C>
; <cmd_t0D>
; <cmd_t0E>
; <cmd_t0F>
; <cmd_t10>
; <cmd_t11>
; <cmd_t12>
; <cmd_t13>
; <cmd_t14>
; <cmd_t15>
; <cmd_t16>
; <cmd_t17>
; <cmd_t18>
; <cmd_t19>
; <cmd_t1A>
; <cmd_t1B>
; <cmd_t1C>
; <cmd_t1D>
; <cmd_t1E>
; <cmd_t1F>
; <cmd_t20>
; <cmd_t21>
; <cmd_t22>
; <cmd_t23>
; <cmd_t24>
; <cmd_t25>
; <cmd_t26>
; <cmd_t27>
; <cmd_t28>
; <cmd_t29>
; <cmd_t2A>
; <cmd_t2B>
; <cmd_t2C>
; <cmd_t2D>
; <cmd_t2E>
; <cmd_t2F>
; <cmd_t30>
; <cmd_t31>
; <cmd_t32>
; <cmd_t33>
; <cmd_t34>
; <cmd_t35>
; <cmd_t36>
; <cmd_t37>
; <cmd_t38>
; <cmd_t39>
; <cmd_t3A>
; <cmd_t3B>
; <cmd_t3C>
; <cmd_t3D>
; <cmd_t3E>
; <cmd_t3F>

skip_end:

	; literal output byte
	ld	a,b
	cp	_first
	jr	nc,token
	add	a,O-O2		; ALMOST works
	ld	(de),a
	inc	de
	ret
token:
	sub	a,_first+O2-O	; magic offset between 'Z' last literal and end of 40-entry strtab

str_tab_out:
	push	hl
	ld	hl,str_tab
	ld	b,a
	or	a
	jr	z,tab_out_entry

skip_tab:
	ld	a,(hl)
	inc	hl
	or	a
	jp	p,skip_tab
	djnz	skip_tab

	; output entry
tab_out_entry
	ld	a,(hl)
	push	af
	and	a,0x7f
	ld	(de),a
	inc	de
	inc	hl
	pop	af
	or	a
	jp	p,tab_out_entry
	pop	hl
	ret	m

byte_match:
	ret	z
	set	7,c;no match
	ret

special_cmp_n
	dec	b
	pop	af		;reg_op back
	and	a,15		;reg_low
	jr	special_cmp

special_cmp_s
	dec	b
	pop	af		;reg_op back
	and	a,7
special_cmp:
	cp	a,b	

byte_match_advance:
	jr	nz,byte_match
	inc	hl
	jr	byte_match

dollar_hex:
	push	af
	ld	a,'$'
	ld	(de),a
	inc	de
	pop	af
hex2:
	push	af
hex_int:
	rra
	rra
	rra
	rra
	call	hexone
	pop	af
hexone:	and	$f
	add	'0'
	cp	'9'+1
	jr	c,isdigit
	add	'A'-'0'-10
isdigit:	ld	(de),a
	inc	de
	ret


str_tab:
	defb 'ADD A',','+0x80, 'ADC A',','+0x80, 'SUB',' '+0x80, 'SBC A',','+0x80, 'AND',' '+0x80, 'XOR',' '+0x80, 'OR',' '+0x80, 'CP',' '+0x80
;cbs_tab:
	defb	'RL','C'+0x80, 'RR','C'+0x80, 'R','L'+0x80, 'R','R'+0x80, 'SL','A'+0x80, 'SR','A'+0x80, '?'+0x80, 'SR','L'+0x80
;cc_tab:
	defb	'N','Z'+0x80, 'Z'+0x80, 'N','C'+0x80, 'C'+0x80, 'N','V'+0x80, 'V'+0x80, 'P'+0x80, 'M'+0x80
;ddss_tab
	defb	'B','C'+0x80, 'D','E'+0x80
reg_hl	defb	'H','L'+0x80, 'S','P'+0x80
;qq_tab	
	defb	'B','C'+0x80, 'D','E'+0x80, 'H','L'+0x80, 'A','F'+0x80
	defb	'B'+0x80,'C'+0x80,'D'+0x80,'E'+0x80,'H'+0x80,'L'+0x80,'?'+0x80,'A'+0x80
; tokens
	defb	'L','D'+0x80		; _ld
	defb	'B','I','T',' '+0x80	; _bit
	defb	'S','E','T',' '+0x80	; _set
	defb	'R','E','S',' '+0x80	; _res
	defb	'L','D',' '+0x80	; _lds
	defb	'C','P'+0x80		; _cp
	defb	'I','N','C',' '+0x80	; _incs
	defb	'D','E','C',' '+0x80	; _decs
	defb	'P','U','S','H',' '+0x80	; _pushs
	defb	'P','O','P',' '+0x80	; _pops
	defb	'R','E','T'+0x80	; _ret
	defb	'C','A','L','L',' '+0x80	; _calls
	defb	'I','M',' '+0x80	; _ims
	defb	'J','R',' '+0x80	; _jrs
	defb	'J','P',' '+0x80	; _jps
	defb	'I','N'+0x80		; _in
	defb	'O','U','T'+0x80	; _out
	defb	'E','X',' '+0x80	; _exs
	defb	'I','R'+0x80		; _ir
	defb	'D','R'+0x80		; _dr
	defb	',','A'+0x80		; _cA
	defb	'A',','+0x80		; _cA
