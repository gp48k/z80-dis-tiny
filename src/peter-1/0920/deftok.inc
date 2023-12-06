_firststr	equ	O+1	; or O+1?

; original table tokens

_A	equ	_firststr+special_off+0
__p	equ	_firststr+special_off+1
_pCq	equ	_firststr+special_off+2
_I2	equ	_firststr+special_off+3
_R	equ	_firststr+special_off+4

; alu_tab
_add	equ	_firststr+alu_tab_off+0
_adc	equ	_firststr+alu_tab_off+1
_sbcX	equ	_firststr+alu_tab_off+3
_cp	equ	_firststr+alu_tab_off+7

; cbs_tab
_rlc	equ	_firststr+cbs_tab_off
_rrc	equ	_rlc+1
_rl	equ	_rrc+1
_rr	equ	_rl+1
_sla	equ	_rr+2
_sra	equ	_sla+1
_qmark	equ	_sra+1
_srl	equ	_qmark+1
	
; cc_tab
_nz	equ	_firststr+cc_tab_off

; ddss_tab (only need "HL", SP)
_reghl	equ	_firststr+ddss_tab_off+2
_sp	equ	_reghl+1

; qq_tab
_bc	equ	_firststr+qq_tab_off
_de	equ	_bc+1
_hl	equ	_de+1
_af	equ	_hl+1

; reg_tab
_B	equ	_firststr+reg_tab_off
_C	equ	_B+1
_D	equ	_C+1
_E	equ	_D+1

; composite tokens
; First two replace unused '?' entries
_jr	equ	_firststr+cbs_tab_off+6
_bit	equ	_firststr+reg_tab_off+6
;
_set	equ	_firststr+tab_end_off
_res	equ	_set+1
_inc	equ	_res+1
_dec	equ	_inc+1
_push	equ	_dec+1
_pop	equ	_push+1
_ret	equ	_pop+1
_call	equ	_ret+1
_ims	equ	_call+1
_jp	equ	_ims+1
_ld	equ	_jp+1
_cp2	equ	_ld+1
_in	equ	_cp2+1
_ot	equ	_in+1
_out	equ	_ot+1
_ex	equ	_out+1
_inr	equ	_ex+1
_dnr	equ	_inr+1
_ir	equ	_dnr+1
_dr	equ	_ir+1
_Ac	equ	_dr+1
__a	equ	_Ac+1
__q	equ	__a+1
_0	equ	__q+1
_1	equ	_0+1
_2	equ	_1+1

; _xx is amount to shift down the literals from their natural 'c'+O command value
; if ' ' is the first literal, then _xx can be at most 31
; change to ' as first, _xx can be 38
; using _B as first _xx can be 65
; O is the amount the djnz dispatch naturally consumes

_firstlit	equ	_2+1

_xx	equ	70
O2	equ	_firstlit-_xx

_I	equ	_inr

_F	equ	'F'+O2
_G	equ	'G'+O2
_H	equ	'H'+O2
_J	equ	'J'+O2
_L	equ	'L'+O2
_N	equ	'N'+O2
_O	equ	'O'+O2
_P	equ	'P'+O2
_S	equ	'S'+O2
_T	equ	'T'+O2
_X	equ	'X'+O2

