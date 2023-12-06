; v6.29
; Ven Reddy
	
	org	$00
z80dis_start0:
	jr	rst00
	org	$08
	jr	rst08
	org	$10
	jr	rst10
	org	$18
	jr	rst18
	org	$20
	jr	rst20
z80dis_end0:
	org	$28
; ******************** RST $28 - add comma
z80dis_start:
rst28	push	af
	ld	a,','
	call	rst30
	pop	af
	ret
	org	$30
; ******************** RST $28 - A -> (DE)
rst30	ld	(de),a
	inc	de
	ret
	org	$38
; ******************** RST $30 - LDIR, b=3
rst38	ld	c,3
	ldir
	ret
; ******************** RST $18 - print out memory adress offset
rst18	push	de
	ld	hl,(hl_mem)
	ld	a,(hl)
	inc	hl
	ld	(hl_mem),hl
	ld	e,a
	add	a,a
	sbc	a,a
	ld	d,a
	add	hl,de
	pop	de
	ld	a,0101b
	call	dechx16
	ret
; ******************** RST $08 - displays register pairs including SP
rst08	ld	hl,reg16_s
	rra
	add	a,a
	ld	c,a
	add	hl,bc
	ld	c,2
	cp	110b
	jr	c,rst08c0
	inc	hl
	inc	hl
rst08c0	ldir
	ret
; ******************** RST $20 - jump table, BC table, A index into table
rst20	pop	hl		; remove caller ret addr on stack
	ld     	h,0
    	ld     	l,a
    	add    	hl,hl
    	add    	hl,bc
    	ld     	a,(hl)
    	inc    	hl
    	ld     	h,(hl)
    	ld     	l,a
	ld	b,0		; put b back to zero, other code expects b=0
    	jp     	(hl)	
; ******************** RST $10 - setup indexing in IXH, IXL and A returns with IXL
rst10	push	af
	and	00111000b
	rra
	rra
	rra
	ld	ixh,a
	pop	af
	and	111b
	ld	ixl,a
	ret	
; ******************** RST $00 function, show 8 bit reg with comma L/R support
rst00	push	af		; save index value
	rst	$28		; write a comma
	dec	de
	pop	af		; get index value
	bit	6, a		; test comma on right of reg?
	push	af		; save results
	jr	z, cont		; yes, overwrite above comma
	inc	de		; increment buffer ptr
cont:	and	00000111b	; force to 0-7 
	ld	c, a		; get index value
	ld	hl, reg8_s	; get reg string
	add	hl, bc		; index into string
	ld	a, (hl)		; get value
	ld	(de), a		; store it to buffer
	cp	'.'		; a '.' means expand to (HL) or IX, IY
	jr	nz, rst00e0	; no, then rst00e1
	ld	a,'('
	rst	$30
	ld	a,(ddfdflg)	; get ix,iy  flags
	or	a
	jr	z, justhl	; nothing set, move to hl
	ld	hl,ixiy_s	; display IX or IY
	ld	c,2
	ldir
	bit	2,a		; show +/- for IX/IY
	jr	z,rst00e2	
	jr	rst00os
justhl:	
	ld	hl,hl_s
	ld	c, 2
	ldir
	jr	rst00e2		; add comma to right?
rst00os	ld	hl,(hl_mem)			; +/- offset
	ld	c,(hl)
	bit	7,c		; number's sign?
	ld	a,'+'
	jr	z,plus
	ld	a,c
	neg
	ld	c,a
	ld	a,'-'
plus	rst	$30
	ld	a,'$'
	rst	$30
	ld	a,(hl)
	inc	hl
	ld	(hl_mem),hl
	and	01111111b
	call	dechx8
	xor	a
	ld	(ddfdflg),a
rst00e2	ld	a,')'
	ld	(de),a
rst00e0	inc	de		; inc de as we copied reg to buf
rst00e1	pop	af		; get comparision state
	bit 	7, a
	ret	z
	bit	6, a
	ret	nz
	rst	$28
	ret

	; this should be typical init routine
z80dis	ld	bc, 0		; keep b = 0, reduce instruction
	ld	iy,reg16_s	; restore HL for IX, IY 
	ld	(iy+4),'H'
	ld	(iy+5),'L'
	xor	a
	ld	(ddfdflg),a	; clear out DD/FD flags

z80dis1	ld	a, (hl)		; get instruction
	inc	hl
	ld	(hl_mem),hl
	push	af
	rst	$10
	pop	af

	;put return address on stack
	ld	hl, discont		; return back to discont
	push	hl
	
	; Extended opcodes are handled in the DI routines
	; A has full current opcode value
	and	11000000b
	rla				; has to go thru carry flag, so 3x
	rla
	rla
	ld	bc,di_lut
	rst	$20
di_lut	defw	di00_en
	defw	di01_en
	defw	di10_en
	defw	di11_en

discont	ld	hl,(hl_mem)
	if 0
	ld	a, '|'		; disable for prod
	ld	(de), a
	inc	de
	ret
	else
	xor	a		; enable for prod
	ld	(de), a
	ret
	endif

; ****************************** DI Group ******************************
di00_en	ld	a,ixh
	push	af
	ld	a,ixl
	ld	bc,di0vt
	rst	$20
di0vt	defw	di0c0
	defw	di0c1
	defw	di0c2
	defw	di0c3
	defw	di0c4
	defw	di0c5
	defw	di0c6
	defw	di0c7
; -------------------- DI Group 00 - Col 000	
di0c0	pop	af
	cp	000b
	jr	nz, di00c9
	; nop - doesn't need hl increment, not accessing next byte
	ld	hl, nop_s		; nop
	rst	$38
	ret
di00c9	cp	001b
	jr	nz, di00ca
	ld	hl, exaf_s		; ex af,af'
	ld	c, 9
	ldir
	ret
di00ca	cp	010b			; row 010b
	jr	nz, di00cb
	ld	hl, djnz_s		; djnz
	ld	c, 5
	ldir
	rst	$18
	ret
di00cb	ld	hl,jr_s
	rst	$38
	dec	a
	dec	a
	dec	a
	push	af
	call	flags
	pop	af
	or	a
	jr	z,di00cb1
	rst	$28
di00cb1	rst	$18
	ret
; -------------------- DI Group 00 - Col 001
di0c1	pop	af
	bit 	0, a		; ADD or LD?
	jr	z, di00c61
	ld	hl, add_s	; ADD, always has HL
	ld	c, 4
	ldir
	push	af
	ld	a,4		; display HL
	rst	$08
	pop	af
	rst	$28
	dec	a
	rst	$08
	ret
di00c61	ld	hl, ld_s	; TODO: move this to RST right above and use as call, for ld_s
	rst	$38
	cp	110b
	jr	z,di00c62
	inc	a
di00c62	rst	$08
	rst	$28
	ld	hl, (hl_mem)
	ld	a,1001b
	call	dechx16
	inc	hl
	ld	(hl_mem), hl
	ret
; -------------------- DI Group 00 - Col 010
di0c2	pop	af
	ld	(a_mem),a
	ld	hl,ld_s
	rst	$38
	cp	100b
	jr	nc,di0c21	; work on upperhalf
	push	af
	xor	a
	ld	(dirdir),a	; set to nop
	pop	af
	bit	0,a
	jr	z,di0c22	; work on lower half odd
	push	af
	ld	a,$c9
	ld	(dirdir),a
	ld	a,7
	rst	$00
	pop	af
	rst	$28
di0c22	push	af
	ld	a,'('
	rst	$30
	pop	af
	rst	$08
	ld	a,')'
	rst	$30
dirdir	ret			; set to nop or ret to control flow
	rst	$28
	ld	a,7
	rst	$00
	ret
di0c21	xor	a		; set up default paths
	ld	(dirdir1),a
	ld	(dirdir2),a
	ld	a,(a_mem)
	; addr or reg first?
	bit	0,a
	jr	z,di0mem	; do mem
	xor	a
	ld	a,$c9
	ld	(dirdir2),a
	ld	a,(a_mem)
di0c27	bit	1,a
	jr	z,di0c24
	ld	a,7
	rst	$00		; show A
	jr	di0c26
di0c24	ld	a,4
	rst	$08		; show HL
di0c26	ld	a,(a_mem)

dirdir1 nop			; flow ctrl point
	call	$28	
	; memory loc
di0mem	ld	hl,(hl_mem)
	push	hl
	ld	a,1011b
	call	dechx16
	pop	hl
	inc	hl
	inc	hl
	ld	(hl_mem),hl
dirdir2 nop			; flow ctrl point
	call	$28
	ld	a,$c9
	ld	(dirdir1),a
	ld	a,(a_mem)
	jr	di0c27
; -------------------- DI Group 00 - Col 011	
di0c3	pop	af
	ld	hl, dec_s
	bit 	0, a
	jr	nz, di00c3
	ld	hl, inc_s
di00c3	ld	c, 4
	ldir
	ld	a, ixh
	rst	$08
	ret
; -------------------- DI Group 00 - Col 100	
di0c4	ld	hl,inc_s
di0c4en	ld	a,(ddfdflg)	; set ixiy to show offset value
	bit	0,a
	jr	z,di0c4c
	set	2,a
	ld	(ddfdflg),a
di0c4c	pop	af
	ld	c, 4
	ldir
	rst	$00
	ret
; -------------------- DI Group 00 - Col 101	
di0c5	ld	hl, dec_s
	jr	di0c4en
; -------------------- DI Group 00 - Col 110	
di0c6:	ld	hl,ld_s	
	rst	$38
	ld	a,(ddfdflg)
	or	a
	jr	z,di0c6n
	set	2,a
	ld	(ddfdflg),a
di0c6n	pop	af
	set	7,a		; set comma right side
	rst	$00
	ld	a,'$'
	rst	$30
	ld	hl,(hl_mem)
	ld	c,(hl)
	push	hl
	call	dechx8
	pop	hl
	inc	hl
	ld	(hl_mem),hl
	ret
; -------------------- DI Group 00 - Col 111	
di0c7:	pop	af
	ld	hl, rlca_s
	ld	c, a
	add	c
	add	c
	ld	c, a
	add	hl, bc
	rst	$38
	ld	a, ixh
	cp	010b		; add A if RLCA or RRCA
	ret	nc
	ld	a, 'A'
	ld	(de), a
	inc	de
	ret
; -------------------- DI Group 01 - Col ALL
di01_en	ld	a, ixh		; check if HALT
	cp	6
	jr	nz,di01c0
	ld	a, ixl
	cp	6
	jr	nz,di01c0
	ld	hl,halt_s
	ld	c,4
	ldir
	ret
di01c0	ld	a,(ddfdflg)
	or	a
	jr	z,di01c1
	set	2,a
	ld	(ddfdflg),a
di01c1	ld	hl,ld_s
	rst	$38
	ld	a,ixh
	set	7, a
	rst	$00
	ld	a,ixl
	rst	$00
	ret
; -------------------- DI Group 10 - All rows(?)
di10_en	ld	a,ixh
	ld	hl,addx_s
	ld	c,a		; mult by 3, opcode 3 char each
	add	c
	add	c
	ld	c,a
	add	hl,bc		; index into
	ld	a,ixh
	cp	110b		; 2 char or 3 char
	ld	c,2
	jr	nc,di10c0
	ld	c,3
di10c0	ldir
	ld	a,' '
	rst	$30
	ld	a,ixh
	cp	100b
	jr	nc,di10cx0
	cp	010b
	jr	z, di10cx0
	ld	a, 'A'
	rst	$30
	rst	$28
di10cx0	ld	hl,ddfdflg
	bit	0,(hl)
	jr	z,di10cx1
	set	2,(hl)
di10cx1	ld	a,ixl
	rst	$00
	ret
; -------------------- DI Group 11 - Entry
di11_en	ld	bc,di11tbl
	ld	a,ixl		; column driven
	rst	$20
di11tbl	defw 	di11_c0
	defw	di11_c1
	defw	di11_c2
	defw	di11_c3
	defw	di11_c4
	defw	di11_c5
	defw	di11_c6
	defw	di11_c7
; -------------------- DI Group 11 - Col 000
di11_c0	ld	hl,ret_s
	ld	c,4
	ldir
	ld	a,ixh
	inc	a
	call	flags
	ret
; -------------------- DI Group 11 - Col 001
di11_c1	ld	a,ixh
	ld	c,3
	bit	0,a
	jr	nz,di11c11
	ld	hl, pop_s
	ld	c,4
	ldir
di11c1e	cp	110b
	jr	z,di11c15
	rst	$08
	ret
di11c15	ld	hl,af_s
	ld	c,2
	ldir
	ret	
di11c11	cp	1
	jr	nz,di11c12
	ld	hl,ret_s
	jr	di11c1x
di11c12	cp	3
	jr	nz,di11c13
	ld	hl,exx_s
di11c1x	ldir
	ret
di11c13	cp	5
	jr	nz,di11c14
	ld	hl,jp_s
	ldir
	ld	a,6
	rst	$00
	ret
di11c14	ld	hl,ld_s
	ldir
	ld	a,6
	rst	$08
	rst	$28
	ld	a,4
	rst	$08
	ret
; -------------------- DI Group 11 - Col 010
di11_c2	ld	hl,jp_s	
	rst	$38
	ld	a,ixh
	inc	a
	call	flags
	rst	$28		; comma
	ld	hl,(hl_mem)
	ld	a,1001b
	call	dechx16
	inc	hl
	ld	(hl_mem),hl
	ret
; -------------------- DI Group 11 - Col 011	
di11_c3	ld	a,ixh
	cp	0
	jr	nz,di11cb
	ld	hl,jp_s
	ld	c,3
di11c3e0	ldir
	ld	hl,(hl_mem)
	ld	a,1001b
	call	dechx16
	inc	hl
	ld	(hl_mem),hl
	ret
di11cb	cp	1		; <CB> instruction
	jp	z, do_cb
di11c30	cp	2		; OUT instruction
	jr	nz,di11c31
	ld	hl,out_s
	ld	c,4
	ldir
	call	di11c37
	ld	a,01000111b
	rst	$00
	ret
di11c31	cp	3		; IN A, instruction
	jr	nz,di11c32
	ld	hl,in_s
	rst	$38
	ld	a,10001111b
	rst	$00
di11c37	ld	a,'('
	rst	$30
	ld	a,'$'
	rst	$30
	ld	hl,(hl_mem)
	ld	c,(hl)
	inc	hl
	ld	(hl_mem),hl
	call	dechx8
	ld	a,')'
	rst	$30
	ret
di11c32	cp	4
	jr	nz,di11c33
	ld	hl,exaf_s
	rst	$38
	ld	a,'('
	rst	$30
	ld	a,6
	rst	$08
	ld	a,')'
	rst	$30
	rst	$28
di11c36 ld	a,4
	rst	$08
	ret
di11c33	cp	5
	jr	nz,di11c34
	ld	hl,exde_s
	ld	c,8
	ldir
	ret
di11c34	cp	6
	ld	hl,di_s
	jr	z,di11c35
	ld	hl,ei_s
di11c35	ld	c,2
	ldir
	ret
; -------------------- DI Group 11 - Col 100		
di11_c4 ld	hl,call_s
	ld	c,5
	ldir
	ld	a,ixh
	inc	a
	call	flags
	rst	$28
	ld	hl,(hl_mem)
	ld	a,1001b
	call	dechx16
	inc	hl
	ld	(hl_mem),hl
	ret
; -------------------- DI Group 11 - Col 101
di11_c5	ld	a,ixh
	bit	0,a		; DI Group 11 - Col 101
	jr	nz,di11c50
	ld	hl,push_s
	ld	bc,5
	ldir
	jp	di11c1e
di11c50	cp	001b
	jr	nz,di11c51
	ld	hl,call_s	; CALL instruction
	ld	c,5		; all we need to do is CALL only
	jp	di11c3e0
di11c51	cp	011b
	jr	z,do_dd
	cp	101b
	jp	z,do_ed
	jr	do_fd
	
; ****************************** DD Group ****************************** 	
do_dd	ld	iy,reg16_s
	ld	(iy+5),'X'
	ld	(iy+4),'I'
	ld	a,01b
	ld	(ddfdflg),a
	ld	hl,ixiy_s+1	; make sure IX is IX
	res	0,(hl)
dodd_e0	pop	af		; remove return from stack
	ld	hl,(hl_mem)
	jp	z80dis1
	
; ****************************** FD Group ******************************		
do_fd	ld	iy,reg16_s
	ld	(iy+5),'Y'
	ld	(iy+4),'I'
	ld	a,01b
	ld	(ddfdflg),a
	ld	hl,ixiy_s+1	; turn IX into IY
	set	0,(hl)
	jr	dodd_e0
	
; -------------------- DI Group 11 - Col 110
di11_c6	ld	a,ixh
	ld	hl,addx_s	; using extended ADD string
	ld	c,a
	add	c
	add	c
	ld	c,a
	add	hl,bc
	ld	a,ixh
	cp	110b
	ld	c,2
	jr	nc,di11c0
	ld	c,3
di11c0	ldir
	ld	a,' '
	rst	$30
	ld	a,ixh
	cp	100b
	jr	nc, di11cx1
	cp	010b
	jr	z, di11cx1
	ld	a, 'A'
	rst	$30
	rst	$28
di11cx1	ld	a,'$'
	rst	$30
	ld	hl,(hl_mem)
	ld	c,(hl)
	call	dechx8
	inc	hl
	ld	(hl_mem),hl
	ret
; -------------------- DI Group 11 - Col 111	
di11_c7	ld	hl,rst_s
	ld	c,4
	ldir
	ld	a,'$'
	rst	$30
	ld	a,ixh
	rla
	rla
	rla
	ld	c,a
	jp	dechx8

; ****************************** CB Group ******************************
do_cb	ld	hl,(hl_mem)
	ld	a,(ddfdflg)
	or	a			; instead of bit 0,a
	jr	z,do_cbx		; continue if not DD/FD mode
	inc	hl			; skip past offset to get instr.
do_cbx	ld	a,(hl)			; get instruction
	inc	hl
	ld	(hl_mem),hl
	push	af
	rst	$10
	pop	af
	and	11000000b
	;or	a
	jp	nz, cbcnt0	; must be BIT, SET, RES blocks (01,10,11)
cb00	ld	a, ixh
	push 	de
	pop 	iy
	ld	hl, rlc_s
	ld	c, 2
	cp	010b
	jr	z, cb00ct5
	cp	011b
	jr	z, cb00ct5
	inc	c
cb00ct5	ldir
	bit	0, a
	jr	z, cb00ct6
	ld	(iy+1), 'R'
cb00ct6	bit	2, a
	jr	z, cb00ex0
	ld	(iy), 'S'
	ld	(iy+2), 'A'
	bit	1, a
	jr	z, cb00ex0
	ld	(iy+2), 'L'
	; use index to look up register
cb00ex0	ld	a, ' '
	rst	$30
	ld	a,ixl
cb00ex2	ld	hl,ddfdflg
	bit	0,(hl)
	jr	z,cb00ex1	; no DD/FD IX/IY so cont.
	set	2,(hl)
	ld	hl,(hl_mem)
	push	hl
	dec	hl
	dec	hl
	ld	(hl_mem),hl
	rst	$00
	pop	hl
	ld	(hl_mem),hl
	ret
cb00ex1	rst	$00
	ret
cbcnt0	ld	hl,bit_s	; 'BIT' string
	cp	40h
	jr	z,entry
	ld	hl,res_s	; 'RES' string
	cp	80h
	jr	z,entry	
	ld	hl,set_s	; 'SET' string
entry	ld	c,4
	ldir			; move string to buffer
	ld	a,ixh
	add	a,30h
	rst	$30
	ld	a, ixl
	or	11000000b	; turn on comma to left of register
	jr	cb00ex2
	rst	$00
	ret

; ****************************** ED Group ******************************	
do_ed	ld	hl,(hl_mem)
	ld	a,(hl)
	inc	hl
	ld	(hl_mem),hl
	push	af
	rst	$10			; prep IXH and IXL
	pop	af
	and	11000000b
	;or	a
	;jp	z, qmark
	ret	z
	cp	01000000b
	jp	z, ed_01
	cp	10000000b
	ret	nz
;	jr	z, ed_10
;qmark	ld	a, '?'			; unsupport instruction
;	rst	$30
;	ret
; -------------------- ED Group 10 - Col ALL
ed_10	ld	a, ixh
	cp	100b
	;jr	c, qmark
	ret	c
	ld	a, ixl
	cp	100b
	;jr	nc,qmark
	ret	nc
	ld	hl, lut
	call	fn1
	; check if in col 3, to OUT and OT
	ld	a, ixl
	cp	011b
	jr	nz, edext1
cont1	ld	c, 2
	ld	a, ixh
	bit	1, a
	jr	nz, edext1
	dec	de
	ld	hl, ut_s
	ldir
	; check row to add: I, D, IR, DR
edext1	ld	a, ixh
	res	2, a		; covert to value: 0-5
	ld	hl, i_s
fn1	add	a, a
	ld	c, a
	add	hl, bc
	ld	c, 2
	ldir
	ret

; -------------------- ED Group 01 Entry
ed_01	ld	a,ixl
	ld	bc,edjtbl
	rst	$20

; ED Group jump table
edjtbl	defw	edc000
	defw	edc001
	defw	edc010
	defw	edc011
	defw	edc100
	defw	edc101
	defw	edc110
	defw	edc111

; -------------------- ED Group 01 Col 000
edc000	ld	hl,in_s
	;ld	c,3
	;ldir
	rst	$38
	ld	hl, reg8_s
	ld	c, ixh
	add	hl, bc
	ld	a,(hl)
	ld	(de), a
	inc	de
	rst	$28		; comma
	ld	hl, pcp_s
	;ld	c, 3
	;ldir
	call	$38
	ret

; -------------------- ED Group 01 Col 001
edc001	ld	hl, out_s
	ld	c, 4
	ldir
	ld	hl, pcp_s
	rst	$38
	rst	$28
	ld	hl, reg8_s
	ld	c, ixh
	add	hl, bc
	ld	a,(hl)
	rst	$30
	ret

; -------------------- ED Group 01 Col 010
edc010	ld	a, ixh
	ld	hl, adc_s
	rrca
	jr	c, edcnt1
	ld	hl, sbc_s
edcnt1	ld	c,4
	ldir
	ld	a,4		; display HL
	rst	$08
	rst	$28
	ld	a, ixh		; display register
	rst	$08
	ret

; -------------------- ED Group 01 Col 011
edc011	ld	hl,ld_s
	rst	$38
	xor	a
	ld	(ed4fc),a	; set flow ctrl to nop
	ld	a,ixh
	bit	0,a
	jr	z,shwmem
	ld	a,$c9		; return
	ld	(ed4fc),a
	ld	a,ixh
	rst	$08
	rst	$28
shwmem	ld	hl,(hl_mem)
	ld	a,1011b
	call	dechx16
	ld	hl,hl_mem
	inc	(hl)
	inc	(hl)
ed4fc	nop			; nop or ret	
	rst	$28
	ld	a,ixh
	rst	$08
	ret
; -------------------- ED Group 01 Col 100
edc100	ld	hl,neg_s
	ld	c,3
	ldir
	ret
; -------------------- ED Group 01 Col 101
edc101	ld	a,ixh
	ld	hl,retn_s
	ld	c,4
	ldir
	or	a
	ret	z
	ld	a,'I'
	dec	de
	rst	$30
	ret
; -------------------- ED Group 01 Col 110
edc110	ld	hl, im_s
	ld	c, 4
	ldir
	ld	a, ixh
	cp	0
	ret	z
	sub	2
	add	31h
	dec	de
	rst	$30
edexit	ret
; -------------------- ED Group 01 Col 111
edc111	ld	a, ixh
	cp	100b
	jr	c, edcnt4
	ld	hl, rrd_s
	bit	0, a
	jr	z, edcnt5
	ld	hl, rld_s
edcnt5	rst	$38
	ret
edcnt4	ld	hl,ld_s
	rst	$38
	ld	c, ixh
	ld	hl, reg7
	add	hl, bc
	ld	a,(hl)
	rst	$30
	rst	$28
	ld	c, ixh		; TODO: this could be a subroutine
	ld	hl, reg8
	add	hl, bc
	ld	a,(hl)
	rst	$30
	ret

; ******************** Dec to Hex 16 bit
; Dec 2 Hex with formatting support. Either address or mem contents
; bits 0,1 and 3 control formatting and selecting of address or memory
dechx16	bit	0,a		; 
	push	af		; save to exit out?
	jr	z,dh16mc0	; no formatting requested
	bit	1,a
	jr	z,dh16mc1	; no then $ only
	ld	a, '('		; otherwise assume ($)
	rst	$30
dh16mc1	ld	a, '$'
	rst	$30
dh16mc0	pop	af
	push	af
	bit	3,a
	jr	nz,frmmem

	; otherwise load from HL register itself
	ld	c,h
	call	dechx8
	ld	c,l
	jr	dchxnt0
	
	; routine for memory location pointed to by HL
frmmem	inc	hl
	ld	c,(hl)
	call	dechx8	
	dec	hl
	ld	c,(hl)
dchxnt0	call	dechx8
	inc	hl
	pop	af		
	bit	1,a
	ret	z
	bit	0,a
	ld	a,')'
	rst	$30
	ret
	; 8 bit entry
dechx8	ld	a, c
	rra
   	rra
   	rra
   	rra
   	call  	dhconv
   	ld  	a,c
dhconv:
   	and  	$0F
   	add  	a,$90
   	daa
   	adc  	a,$40
   	daa
	rst	$30
   	ret

; ******************** Flags 
; Prints out Flags based on index, supports double and single characters	
flags	ld	hl,flags_s
	add	a,a	
	ld	c,a
	add	hl,bc
	call	aprnt
	inc	hl
aprnt	ld	a,(hl)
	or	a
	ret	z
	rst	$30
	ret
	
reg8_s	defm	'BCDE'		; keep together with hl_s
hl_s	defm	'HL.A'	
reg16_s	defm	'BCDEHLAFSP'
reg7	defm	'IR'		; AA' - ** must roll over with reg8 **
reg8	defm	'AAIR'
in_s	defm	'IN '		
out_s	defm	'OUT '
adc_s	defm	'ADC '
im_s	defm	'IM 0'
neg_s	defm	'NEG'
retn_s	defm	'RETN'
rrd_s	defm	'RRD'
rlc_s	defm	'RLC'		; use for rows 000 - 011
rld_s	defm	'R'		; keep together with ld_s
ld_s	defm	'LD '
sbc_s	defm	'SBC '
pcp_s	defm	'(C)'
bit_s	defm	'BIT '
res_s	defm	'RES '
set_s	defm	'SET '
rlca_s	defm	'RLCRRCRLARRADAACPLSCFCCF'
add_s	defm	'ADD '
nop_s	defm	'NOP'
exaf_s	defm	"EX "		; keep these together
af_s	defm	"AF,AF'"
djnz_s	defm	'DJNZ '
jr_s	defm	'JR '
halt_s	defm	'HALT'
addx_s	defm	'ADDADCSUBSBCANDXOROR.CP.'
dec_s	defm	'DEC '
inc_s	defm	'INC '
ret_s	defm	'RET '
pop_s	defm	'POP '
jp_s	defm	'JP '
exx_s	defm	'EXX'
exde_s	defm	'EX DE,HL'
di_s	defm	'DI'
ei_s	defm	'EI'
call_s	defm	'CALL '	
push_s	defm	'PUSH '
rst_s	defm	'RST '
ixiy_s	defm	'IX'		; bit is flipped to get IY
flags_s	defm	0,0,'NZ','Z',0,'NC','C',0,'NV','V',0,'P',0,'M',0
lut	defm	'LDCPINOT'
ut_s	defm	'UT'	
i_s	defm	'I',0,'D',0,'IR','DR'	
a_mem	defb	0		
hl_mem	defw	0
ddfdflg	defb	0
z80dis_end:
