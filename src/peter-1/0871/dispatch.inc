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
	djnz	skip_cmd_s6_special
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
	cp	cmd_accept+1
	jr	c,decode_match		; back to top
	jr	rule_skip

	; evaluate print
print_loop:
	inc	ix
	ld	a,(ix+0)
	cp	cmd_accept+1	; is it a command?
	jr	c,rule_done
	ld	b,a
	call	dispatch
	jr	print_loop
rule_done:
	xor	a
	ld	(de),a
	ret

skip_cmd_s6_special:
	rra
	rra
	rra
	and	a,7		; reg_r
	djnz	skip_cmd_r6
; <cmd_r6>
	cp	6
	jr	byte_match_advance

skip_cmd_r6:
	djnz	skip_cmd_accept
; <cmd_accept>
hack_inc:
	inc	hl
	jr	print_loop

; ---- all commands are now "prt_" commands
skip_cmd_accept:
; "comma" prefix
; <_cprt_rc>
; <_cprt_move_dir>
; <_cprt_n>
; <_cprt_nn>
; <_cprt_np>
; <_cprb_im>
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
; <_sprt_im>
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



num_prefix	equ	29

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

	djnz	$+8 ; skip_prt_rc
; <prt_rc>
	and	a,3		; only two bits valid
	add	a,cc_tab_off
	jr	sto_tramp

skip_prt_rc:
; <prt_move_dir>
	djnz	skip_prt_move_dir
	and	a,3
	add	a,inr_tab_off
	jr	sto_tramp

skip_prt_move_dir:
	djnz	skip_prt_n
; <prt_n>
	ld	a,(hl)
	inc	hl

; MUST land at an RST boundary like $0
dollar_hex:
	push	af
	ld	a,'$'
	rst	print_a
	pop	af
	nop
	nop
	nop
hex2:
	push	af
	rra
	rra
	rra
	rra
	rst	hexone
	nop
	pop	af
hexone:	and	$f
	cp	10
	sbc	$69
	daa
	nop
print_a:
	ld	(de),a
	inc	de
	ret

skip_prt_n:
	djnz	skip_prt_nn
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

skip_prt_nn:
	djnz	skip_prt_np
; <prt_np>
	ld	a,'('
	rst	print_a

	call	prt_nn_impl

	jr	HL_only

skip_prt_np:
	djnz	skip_prt_im
; <prt_im>
	sub	1
	adc	0
	inc	b

skip_prt_im:
	djnz	skip_prt_b
; <prt_b>
	add	a,'0'
	rst	print_a
	ret

skip_prt_b:
	djnz	skip_prt_cbs
; <prt_cbs>
	add	a,cbs_tab_off
	jr	sto_tramp

skip_prt_cbs:
	djnz	skip_prt_cc
; <prt_cc>
	add	a,cc_tab_off
sto_tramp:
	jr	str_tab_out_tramp2

skip_prt_cc:
	djnz	skip_prt_alu
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

skip_prt_alu:
	djnz	skip_prt_r
; <prt_r>
reg_tab_out:
	cp	6
	jr	z,hl_disp
	add	a,reg_tab_off
	jr	str_tab_out

skip_prt_r:
; reg_dd is a shift of reg_r
	rra
	djnz	skip_prt_qq
; <prt_qq>
	cp	a,3
	jr	c,no_inc_qq
	inc	a
	inc	b	; re-trigger DJNZ

skip_prt_qq:
	djnz	skip_prt_dd
; <prt_dd>
no_inc_qq:
	;add	a,ddss_tab_off	; zero
	jr	str_tab_out

skip_prt_dd:
	djnz	skip_prt_e
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

skip_prt_e:
; <prt_hl_disp>
	djnz	skip_prt_hl_disp
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
	ld	a,iyl
	add	a,a
	sbc	a,a
	ld	b,a
	cpl
	add	a,a
	add	a,'-'
	rst	print_a
	ld	a,iyl
	xor	b
	sub	b
	rst	dollar_hex	;call	dollar_hex
HL_only:
	ld	a,')'
	rst	print_a
	ret

skip_prt_hl_disp:
	ld	a,(reg_op)
	djnz	skip_prt_rst
; <prt_rst>
	and	a,0x38
	rst	dollar_hex
	ret

skip_prt_rst:
	djnz	skip_prt_move_op
; <prt_move_op>
	and	3
	add	a,ldr_tab_off
	jr	str_tab_out

skip_prt_move_op:
	djnz	skip_prt_s
; <prt_s>
	and	a,7		;reg_s
	bit	FLAG_s6,c
	jr	nz,hl_command
	jr	reg_tab_out

skip_prt_s:

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
	srl	a
	rst	print_a
	inc	hl
	jr	nc,tab_out_entry
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
;	add	a,5	; _xx is offset to literal byte and put back subtraction
; now +5 because removed _bit,_set,_res,_push_,_pop
	rst	print_a
	ret

str_tab:

tab0_off	equ	0
;ddss_tab:
	token	"BC"
	token	"DE"
reg_hl	token	"HL"		; will change to IX/IY
	token	"SP"
	token	"AF"
	token	"HL"
tab1_off	equ	tab0_off+6

; special literals
special_off	equ	tab1_off+0
	token	"A"
	token	"("			; __p
	token	"(C)"			; _pCq
	token	"I"			; _I
	token	"R"			; _R

tab2_off	equ	special_off+5
;cc_tab:
	token	"NZ"
	token	"Z"
	token	"NC"
	token	"C"
	token	"NV"
	token	"V"
	token	"P"
	token	"M"
tab3_off	equ	tab2_off+8

;alu_tab:
	token	"ADD"
	token	"ADC"
	token	"SUB"
	token	"SBC"
	token	"AND"
	token	"XOR"
	token	"OR"
	token	"CP"
tab4_off	equ	tab3_off+8

;cbs_tab:
	token	"RLC"
	token	"RRC"
	token	"RL"
	token	"RR"
	token	"SLA"
	token	"SRA"
	token	"JR"
	token	"SRL"

tab5_off	equ	tab4_off+8

;reg_tab:
	token	"B"
	token	"C"
	token	"D"
	token	"E"
	token	"H"
	token	"L"
	token	"INC"
	token	"A"
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
; _ld and _inc inside unused entries
	token	"DEC"			; _dec
	token	"RET"			; _ret
	token	"CALL"			; _calls
	token	"JP" 			; _jp
ldr_tab_off	equ	tab6_off+4
	token	"LD"			; _ld
	token	"CP"			; _cp2
	token	"IN"			; _in
	token	"OT"			; _ot
	token	"OUT"			; _out
	token	"EX"			; _ex
inr_tab_off	equ	tab6_off+10
	token	"I"			; _inr
	token	"D"			; _dnr
	token	"IR"			; _ir
	token	"DR"			; _dr
	token	"A,"			; _Ac
	token	";"			; __a
	token	")"			; __q

