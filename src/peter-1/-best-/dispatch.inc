; Dispatch routines have to return with "C"
; set 7,c for match failed
dispatch:
	djnz	skip_1
	jr	end_rule
; end_rule / end_table both terminate 
; <cmd_end_rule>
skip_1:
	djnz	skip_2
; <cmd_end_table>
end_rule:
	ld	a,0
	ld	(de),a
	pop	bc		; skip return
	ret
skip_2:
	djnz	skip_3
; <cmd_alu>
; $alu[ ($code[$i] >> 3) & 7];
; @alu = ( 'ADD A,', 'ADC A,', 'SUB ', 'SBC A,', 'AND ', 'XOR ', 'OR ', 'CP ' );
	ld	a,(reg_r)
	ld	iy,alu_tab
	jp	tab_out

skip_3:
	djnz	skip_4
; <cmd_b>
	ld	a,(reg_r)
	add	a,'0'
	ld	(de),a
	inc	de
	ret

skip_4:
	djnz	skip_5
; <cmd_cbs>
	ld	a,(reg_r)
	ld	iy,cbs_tab
	jp	tab_out

skip_5:
	djnz	skip_6
; <cmd_cc>
	ld	a,(reg_r)
	ld	iy,cc_tab
	jp	tab_out

skip_6:
	djnz	skip_7
; <cmd_dd>
;	$ddss[$dd_reg];
	ld	iy,ddss_tab
	ld	a,(reg_dd)
	jp	tab_out

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
; $rel = $code[$i];
; if ($rel >= 0x80) { $rel -= 256; }
; $disasm .= sprintf '$%04X', ($addr + $i + 1 + $rel) & 0xffff;
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
	push	hl			; TODO: push seems unnecessary
	ld	a,'('
	ld	(de),a
	inc	de
	ld	iy,reg_hl
	call	tab_out_entry
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
	pop	hl
	ret
skip_10:
	djnz	skip_11
; <cmd_lit>
	ld	b,(ix+1)
	inc	ix
	ld	a,(reg_op)
	cp	a,b
	jr	z,lit_match
	set	7,c;no match
	ret
lit_match:
	inc	hl
	ret

skip_11:
	djnz	skip_12
; <cmd_n1>
	ld	a,(reg_low)
	cp	1
	jp	byte_match_advance

skip_12:
	djnz	skip_13
; <cmd_n2>
	ld	a,(reg_low)
	cp	2
	jp	byte_match_advance

skip_13:
	djnz	skip_14
; <cmd_n3>
	ld	a,(reg_low)
	cp	3
	jp	byte_match_advance

skip_14:
	djnz	skip_15
; <cmd_n5>
	ld	a,(reg_low)
	cp	5
	jp	byte_match_advance

skip_15:
	djnz	skip_16
; <cmd_n9>
	ld	a,(reg_low)
	cp	9
	jp	byte_match_advance

skip_16:
	djnz	skip_17
; <cmd_n>
	ld	a,(hl)
	inc	hl
	call	dollar_hex
	ret

skip_17:
	djnz	skip_18
; <cmd_nA>
	ld	a,(reg_low)
	cp	0xa
	jp	byte_match_advance

skip_18:
	djnz	skip_19
; <cmd_nB>
	ld	a,(reg_low)
	cp	0xb
	jp	byte_match_advance

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
	call	hex2
	ret

skip_20:
	djnz	skip_21
; <cmd_np>
	ld	a,'('
	ld	(de),a
	inc	de

	call	cmd_nn_impl

	ld	a,')'
	ld	(de),a
	inc	de
	ret

skip_21:
	djnz	skip_22
; <cmd_page00>
; TODO: can "ld a,(reg_page)" before these, if we'd like
; but that means re-arranging the opcodes
; or re-loading A after, if necessary
cmd_page00_impl
	ld	a,(reg_page)
	cp	a,0*64		; TODO "or a"?
	jp	byte_match

skip_22:
	djnz	skip_23
; <cmd_page01>
	ld	a,(reg_page)
	cp	a,1*64
	jp	byte_match

skip_23:
	djnz	skip_24
; <cmd_page10>
	ld	a,(reg_page)
	cp	a,2*64
	jp	byte_match

skip_24:
	djnz	skip_25
; <cmd_page11>
	ld	a,(reg_page)
	cp	a,3*64
	jp	byte_match

skip_25:
	djnz	skip_26
; <cmd_qq>
	ld	iy,qq_tab
	ld	a,(reg_dd)
	jp	tab_out

skip_26:
	djnz	skip_27
; <cmd_r6>
	ld	a,(reg_r)
	cp	6
	jp	byte_match_advance

skip_27:
	djnz	skip_28
; <cmd_r>
; $reg[$r_reg];
	ld	a,(reg_r)
reg_tab_out:
	ld	iy,reg_tab	
	ld	(mod_r+2),a
mod_r	ld	a,(iy+0)	; self-modify
	ld	(de),a	
	inc	de
	ret

skip_28:
	djnz	skip_29
; <cmd_rc>
;if (($code[$i] & ~0x18) != 0x20) { return 0; }
;	$disasm .= "JR " . $cc_r[ ($code[$i] >> 3) & 3 ];
	ld	a,(reg_op)
	and	a,~0x18
	cp	0x20
	jr	z,cmd_rc_match
	set	7,c;no match
	ret
cmd_rc_match:
	inc	hl
	ld	a,'J'
	ld	(de),a
	inc	de
	ld	a,'R'
	ld	(de),a
	inc	de
	ld	a,' '
	ld	(de),a
	inc	de
	ld	a,(reg_r)
	and	a,3		; only two bits valid
	ld	iy,cc_tab
	jp	tab_out

skip_29:
	djnz	skip_30
; <cmd_reghl>
	ld	iy,reg_hl
	jp	tab_out_entry

skip_30:
	djnz	skip_31
; <cmd_rst>
	ld	a,(reg_op)
	and	a,0x38
	call	dollar_hex
	ret

skip_31:
	ld	a,b
	cp	2
	ld	a,(reg_s)
	jr	z,cmd_s1_impl
	djnz	skip_32
; <cmd_s0>
	cp	0		; TODO: "or a" shorter?
	jp	byte_match_advance

skip_32:
	djnz	skip_33
; <cmd_s1>
cmd_s1_impl:
	cp	1
	jp	byte_match_advance

skip_33:
	djnz	skip_33a
; <cmd_s2>
	cp	2
	jp	byte_match_advance

skip_33a:
	djnz	skip_34
; <cmd_s3>
	cp	3
	jp	byte_match_advance

skip_34:
	djnz	skip_35
; <cmd_s4>
	cp	4
	jp	byte_match_advance

skip_35:
	djnz	skip_36
; <cmd_s5>
	cp	5
	jp	byte_match_advance

skip_36:
	djnz	skip_37
; <cmd_s6>
	cp	6
	jp	byte_match_advance

skip_37:
	djnz	skip_38
; <cmd_s7>
	cp	7
	jp	byte_match_advance

skip_38:
	djnz	skip_39
; <cmd_s>
	ld	a,(reg_s)
	jp	reg_tab_out

skip_39:
	djnz	skip_40
; <cmd_hack_inc>
	inc	hl
	ret

skip_40:
	; literal output byte
	ld	a,b
	ld	(de),a
	inc	de
	ret

alu_tab:
	defb 'ADD A',','+0x80, 'ADC A',','+0x80, 'SUB',' '+0x80, 'SBC A',','+0x80, 'AND',' '+0x80, 'XOR',' '+0x80, 'OR',' '+0x80, 'CP',' '+0x80
cbs_tab:
	defb	'RL','C'+0x80, 'RR','C'+0x80, 'R','L'+0x80, 'R','R'+0x80, 'SL','A'+0x80, 'SR','A'+0x80, '?'+0x80, 'SR','L'+0x80
cc_tab:
	defb	'N','Z'+0x80, 'Z'+0x80, 'N','C'+0x80, 'C'+0x80, 'N','V'+0x80, 'V'+0x80, 'P'+0x80, 'M'+0x80
ddss_tab
	defb	'B','C'+0x80, 'D','E'+0x80
reg_hl	defb	'H','L'+0x80, 'S','P'+0x80
qq_tab	defb	'B','C'+0x80, 'D','E'+0x80, 'H','L'+0x80, 'A','F'+0x80

reg_tab
	defb	'BCDEHL?A'


tab_out:
	ld	b,a
	or	a
	jr	nz,skip_tab
	; output entry
tab_out_entry
	ld	a,(iy+0)
	push	af
	and	a,0x7f
	ld	(de),a
	inc	de
	inc	iy
	pop	af
	or	a
	ret	m
	jr	tab_out_entry
skip_tab:
	ld	a,(iy+0)
	inc	iy
	or	a
	jp	p,skip_tab
	djnz	skip_tab
	jr	tab_out_entry

byte_match:
	ret	z
	set	7,c;no match
	ret
byte_match_advance:
	jr	nz,byte_match
	inc	hl
	jr	byte_match

; TODO bad "push af" here
hex2:	push	af
	jr	hex_int

dollar_hex:
	push	af
	ld	a,'$'
	ld	(de),a
	inc	de
	pop	af
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

