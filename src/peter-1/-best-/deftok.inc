_0	equ	'0'+O
_1	equ	'1'+O
_2	equ	'2'+O
_A	equ	'A'+O
_B	equ	'B'+O
_C	equ	'C'+O
_D	equ	'D'+O
_E	equ	'E'+O
_F	equ	'F'+O
_G	equ	'G'+O
_H	equ	'H'+O
_I	equ	'I'+O
_J	equ	'J'+O
_L	equ	'L'+O
_M	equ	'M'+O
_N	equ	'N'+O
_O	equ	'O'+O
_P	equ	'P'+O
_R	equ	'R'+O
_S	equ	'S'+O
_T	equ	'T'+O
_U	equ	'U'+O
_X	equ	'X'+O
_Z	equ	'Z'+O
__a	equ	39+O
__c	equ	','+O
__p	equ	'('+O
__q	equ	')'+O
__s	equ	' '+O

_first	equ	'Z'+1
; original table tokens
; cbs_tab
_rlc	equ	_first+O+cbs_tab_off
_rrc	equ	_rlc+1
_rl	equ	_rrc+1
_rr	equ	_rl+1
_sla	equ	_rr+2
_sra	equ	_sla+1
_qmark	equ	_sra+1
_srl	equ	_qmark+1
	
; cc_tab
_nz	equ	_first+O+cc_tab_off

; ddss_tab (only need "HL", SP)
_reghl	equ	_first+O+ddss_tab_off+2
_sp	equ	_reghl+1

; qq_tab
_bc	equ	_first+O+qq_tab_off
_de	equ	_bc+1
_hl	equ	_de+1
_af	equ	_hl+1

; composite tokens
_ld	equ	_first+O+40
_bit	equ	_ld+1
_set	equ	_bit+1
_res	equ	_set+1
_lds	equ	_res+1
_cp	equ	_lds+1
_incs	equ	_cp+1
_decs	equ	_incs+1
_pushs	equ	_decs+1
_pops	equ	_pushs+1
_ret	equ	_pops+1
_calls	equ	_ret+1
_ims	equ	_calls+1
_jrs	equ	_ims+1
_jps	equ	_jrs+1
_in	equ	_jps+1
_out	equ	_in+1
_exs	equ	_out+1
_ir	equ	_exs+1
_dr	equ	_ir+1
_cA	equ	_dr+1
_Ac	equ	_cA+1
;	equ	_Ac+1


