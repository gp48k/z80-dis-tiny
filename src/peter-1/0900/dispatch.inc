; Dispatch routines are of two types
; The commands are handled "directly" and match/don't match
; (one match per rule)
; The print opcodes loop, printing the answer
; The ranges don't overlap so the match command of the
; next rules acts as a terminator for the previous rule's print
; (and: makes it easy to skip)

dispatch:
reg_op	equ	$+1
	ld	a,0		; TODO: added because prt_rst/prt_s moved
	push	af
	ld	a,b
	sub	8
	jr	c,special_cmp_s
	ld	b,a
; <cmd_s0>
; <cmd_s1>
; <cmd_s2>
; <cmd_s3>
; <cmd_s4>
; <cmd_s5>
; <cmd_s6>
; <cmd_s7>

	sub	0xC		; only n0 .. nB used
	jr	c,special_cmp_n
	ld	b,a
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

	sub	64
	jr	c,special_cmp_t
	ld	b,a
	pop	af		; reg_op (used by reg_r)

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

; <cmd_GAP>	-- fixup so DJNZ works from here

; <cmd_s6_special>
	djnz	skip_39s
; always matches but sets flag is s==6
	and	a,7
	cp	a,6
	jr	nz,not_s6
	set	FLAG_s6,c
not_s6:
	inc	hl
	jr	print_loop
	
special_cmp_t:
	pop	af	;reg_op
	and	a,0x3f
	jr	special_cmp

special_cmp_n
	pop	af		;reg_op back
	and	a,15		;reg_low
	jr	special_cmp

special_cmp_s
	pop	af		;reg_op back
	and	a,7
special_cmp:
	cp	a,b	

byte_match_advance:
	jr	nz,byte_match
	inc	hl
byte_match:
	jr	z,print_loop

; skip to next rule
rule_skip:
	inc	ix
	ld	a,(ix+0)
	cp	cmd_end_table+1
	jr	c,decode_match		; back to top
	jr	rule_skip

	; evaluate print
print_loop:
	inc	ix
	ld	a,(ix+0)
	cp	cmd_end_table+1	; is it a command?
	jr	c,rule_done
	ld	b,a
	call	dispatch
	jr	print_loop
rule_done:
	xor	a
	ld	(de),a
	ret

skip_39s:
	rra
	rra
	rra
	and	a,7		; reg_r
	djnz	skip_39
; <cmd_r6>
	cp	6
	jr	byte_match_advance

skip_39:
	djnz	skip_0
; <cmd_hack_inc>
hack_inc:
	inc	hl
	jr	print_loop

skip_0:
	djnz	skip_27b
; <cmd_end_table>
	jr	rule_done

; ---- all commands are now "prt_" commands
skip_27b:
; "comma" prefix
; <_cprt_rc>
; <_cprt_move_dir>
; <_cprt_n>
; <_cprt_nn>
; <_cprt_np>
; <_cprt_b>
; <_cprt_cbs>
; <_cprt_cc>
; <_cprt_alu>
; <_cprt_r>
; <_cprt_qq>
; <_cprt_dd>
; <_cprt_e>
; <_cprt_hl_disp>
; <_cprt_rst>
; <_cprt_move_op>
; <_cprt_s>
; <_cBC>
; <_cDE>
; <_cregHL>
; <_cSP>
; <_cAF>
; <_cHL>
; <_cA>
; <__cp>
; <_cpCq>
; <_cI>
; <_cR>

; <_sprt_rc>
; <_sprt_move_dir>
; <_sprt_n>
; <_sprt_nn>
; <_sprt_np>
; <_sprt_b>
; <_sprt_cbs>
; <_sprt_cc>
; <_sprt_alu>
; <_sprt_r>
; <_sprt_qq>
; <_sprt_dd>
; <_sprt_e>
; <_sprt_hl_disp>
; <_sprt_rst>
; <_sprt_move_op>
; <_sprt_s>
; <_sBC>
; <_sDE>
; <_sregHL>
; <_sSP>
; <_sAF>
; <_sHL>
; <_sA2>
; <__sp>
; <_spCq>
; <_sI>
; <_sR>



num_prefix	equ	28

	ex	af,af'
	ld	a,','
	ld	(de),a
	dec	de
	ld	a,b
	sub	a,num_prefix*2 + 1
	jr	nc,no_prefix
	; space prefix?
	inc	de
	add	a,num_prefix
	jr	nc,prefix_done
	ld	a,' '
	ld	(de),a
	; adjust opcode to prt_ range
	ld	a,b
	sub	num_prefix+1	; +1 for the inc b below
	
no_prefix:
	ld	b,a
	inc	b	; adjust for the extra + 1 subtraction
prefix_done:
	inc	de
	ex	af,af'

	djnz	skip_19b
; <prt_rc>
	and	a,3		; only two bits valid
	add	a,cc_tab_off
	jr	sto_tramp

skip_19b:
; <prt_move_dir>
	djnz	skip_19a
	and	a,3
	add	a,inr_tab_off
	jr	sto_tramp

skip_19a:
	djnz	skip_19
; <prt_n>
	ld	a,(hl)
	inc	hl

	rst	dollar_hex	;call	dollar_hex
	ret

skip_19:
	djnz	skip_20
; <prt_nn>
prt_nn_impl:
	inc	hl
	ld	a,(hl)
	rst	dollar_hex	;call	dollar_hex
	dec	hl
	ld	a,(hl)
	inc	hl
	inc	hl
	rst	hex2
	ret

skip_20:
	djnz	skip_3
; <prt_np>
	ld	a,'('
	rst	print_a

	call	prt_nn_impl

	jr	HL_only

skip_3:
	djnz	skip_4
; <prt_b>
	add	a,'0'
	rst	print_a
	ret

skip_4:
	djnz	skip_5
; <prt_cbs>
	add	a,cbs_tab_off
	jr	sto_tramp

skip_5:
	djnz	skip_27a
; <prt_cc>
	add	a,cc_tab_off
sto_tramp:
	jr	str_tab_out_tramp2

skip_27a:
	djnz	skip_27
; <prt_alu>
	push	af
	add	a,alu_tab_off
	call	str_tab_out
	ld	a,' '
	rst	print_a
	pop	af
	; Only 0,1,3 need "A," appended
	xor	2
	dec	a
	cp	3
	ret	nc
	ld	a,_Ac-_firststr
str_tab_out_tramp2:
	jr	str_tab_out

skip_27:
	djnz	skip_25
; <prt_r>
reg_tab_out:
	cp	6
	jr	z,hl_disp
	add	a,reg_tab_off
	jr	str_tab_out

skip_25:
; reg_dd is a shift of reg_r
	rra
	djnz	skip_6
; <prt_qq>
	cp	a,3
	jr	c,no_inc_qq
	inc	a
	inc	b	; re-trigger DJNZ

skip_6:
	djnz	skip_8
; <prt_dd>
no_inc_qq:
	;add	a,ddss_tab_off	; zero
	jr	str_tab_out

skip_8:
	djnz	skip_9a
; <prt_e>
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
	rst	dollar_hex	;call	dollar_hex
	ld	a,l
	rst	hex2
	pop	hl
	ret

skip_9a:
; <prt_hl_disp>
	djnz	skip_10
hl_disp:
	bit	FLAG_ixy,c	; ixy
	jr	z,hl_command
	inc	hl		; skip displacement byte
hl_command:
	; (HL) or IX+- DISP stuff
	ld	a,'('
	rst	print_a
	ld	a,reg_hl_off
	call	str_tab_out
	bit	FLAG_ixy,c
	jr	z,HL_only
	; +- reg_disp
	ex	de,hl
	ld	b,'+'
reg_disp	equ	$+1
	ld	a,0		;reg_disp
	or	a
	jp	p,positive
	ld	b,'-'
	cpl	
	inc	a
positive:
	ld	(hl),b
	ex	de,hl
	inc	de
	rst	dollar_hex	;call	dollar_hex
HL_only:
	ld	a,')'
	rst	print_a
	ret

skip_10:
	ld	a,(reg_op)
	djnz	skip_11
; <prt_rst>
	and	a,0x38
	jp	dollar_hex

skip_11:
	djnz	skip_39a
; <prt_move_op>
	and	3
	add	a,ldr_tab_off
	jr	str_tab_out

skip_39a:
	djnz	skip_end
; <prt_s>
	and	a,7		;reg_s
	bit	FLAG_s6,c
	jr	nz,hl_command
	jr	reg_tab_out

skip_end:

	; literal output byte
	ld	a,b
	cp	_firstlit-O
	jr	nc,lit_out

	dec	a		; TODO: can 'match this "dec a" with the lit out one
str_tab_out:
	push	hl		; save disasm src position
	ld	b,a
	inc	b
	ld	hl,str_tab
str_again:
	push	de		; position
tab_out_entry:
	ld	a,(hl)
	and	a,0x7f
	rst	print_a
	bit	7,(hl)
	inc	hl
	jr	z,tab_out_entry
	djnz	str_cont
	pop	hl	; junk de
	pop	hl	; actual hl (disasm src position)
	ret
str_cont:
	pop	de	
	jr	str_again

lit_out:
; TODO: -5?  ; TODO now -6 because of token gap reasons
; back to -5?
; now -4 because _B is "closer" by one
; now -2 because __s and __c removed
; now -4 because _I and _R added
; now -3 because _lds removed
; now -2 because _cp removed
; now -3 because _ot added
; now -2 because _B aliased to string
; now +1 because _C, _D, _E aliased to string
; now +0 because _inr added
; now -1 because _dnr added
; now -2 because _cp added
; now +0 because removing qq_tab
;	add	a,0	; _xx is offset to literal byte and put back subtraction
	rst	print_a
	ret

str_tab:

tab0_off	equ	0
;ddss_tab:
	defb	'B','C'+0x80
	defb	'D','E'+0x80
reg_hl	defb	'H','L'+0x80	; will change to IX/IY
	defb	'S','P'+0x80
	defb	'A','F'+0x80
	defb	'H','L'+0x80	; always HL
tab1_off	equ	tab0_off+6

; special literals
special_off	equ	tab1_off+0
	defb	'A'+0x80		; _A
	defb	'('+0x80		; __p
	defb	'(','C',')'+0x80	; _pCq
	defb	'I'+0x80		; _I
	defb	'R'+0x80		; _R

tab2_off	equ	special_off+5
;cc_tab:
	defb	'N','Z'+0x80, 'Z'+0x80, 'N','C'+0x80, 'C'+0x80, 'N','V'+0x80, 'V'+0x80, 'P'+0x80, 'M'+0x80
tab3_off	equ	tab2_off+8

;alu_tab:
	defb 'AD','D'+0x80, 'AD','C'+0x80, 'SU','B'+0x80, 'SB','C'+0x80, 'AN','D'+0x80, 'XO','R'+0x80, 'O','R'+0x80, 'C','P'+0x80
tab4_off	equ	tab3_off+8

;cbs_tab:
	defb	'RL','C'+0x80, 'RR','C'+0x80, 'R','L'+0x80, 'R','R'+0x80, 'SL','A'+0x80, 'SR','A'+0x80, 'J', 'R'+0x80, 'SR','L'+0x80

tab5_off	equ	tab4_off+8

;reg_tab:
	defb	'B'+0x80,'C'+0x80,'D'+0x80,'E'+0x80,'H'+0x80,'L'+0x80,'B','I','T'+0x80,'A'+0x80
tab6_off	equ	tab5_off+8

; table offsets
ddss_tab_off	equ	tab0_off
cc_tab_off	equ	tab2_off
alu_tab_off	equ	tab3_off
cbs_tab_off	equ	tab4_off
reg_tab_off	equ	tab5_off
tab_end_off	equ	tab6_off

; internal offsets into tables
reg_hl_off	equ	ddss_tab_off+2

; tokens
; _ld and _bit inside unused entries
	defb	'S','E','T'+0x80	; _set
	defb	'R','E','S'+0x80	; _res
	defb	'I','N','C'+0x80	; _inc
	defb	'D','E','C'+0x80	; _dec
	defb	'P','U','S','H'+0x80	; _push
	defb	'P','O','P'+0x80	; _pop
	defb	'R','E','T'+0x80	; _ret
	defb	'C','A','L','L'+0x80	; _calls
	defb	'I','M',' '+0x80	; _ims
	defb	'J','P'+0x80		; _jp
ldr_tab_off	equ	tab6_off+10
	defb	'L','D'+0x80		; _ld
	defb	'C','P'+0x80		; _cp2
	defb	'I','N'+0x80		; _in
	defb	'O','T'+0x80		; _ot
	defb	'O','U','T'+0x80	; _out
	defb	'E','X'+0x80		; _ex
inr_tab_off	equ	tab6_off+16
	defb	'I'+0x80		; _inr
	defb	'D'+0x80		; _dnr
	defb	'I','R'+0x80		; _ir
	defb	'D','R'+0x80		; _dr
	defb	'A',','+0x80		; _Ac
	defb	39+0x80			; __a
	defb	')'+0x80		; __q
	defb	'0'+0x80		; _0
	defb	'1'+0x80		; _1
	defb	'2'+0x80		; _2

