O2	equ	O -11
__s	equ	' '+O2
__a	equ	39+O2
__p	equ	'('+O2
__q	equ	')'+O2
__c	equ	','+O2

_0	equ	'0'+O2
_1	equ	'1'+O2
_2	equ	'2'+O2

_A	equ	'A'+O2
_B	equ	'B'+O2
_C	equ	'C'+O2
_D	equ	'D'+O2
_E	equ	'E'+O2
_F	equ	'F'+O2
_G	equ	'G'+O2
_H	equ	'H'+O2
_I	equ	'I'+O2
_J	equ	'J'+O2
_L	equ	'L'+O2
_M	equ	'M'+O2
_N	equ	'N'+O2
_O	equ	'O'+O2
_P	equ	'P'+O2
_R	equ	'R'+O2
_S	equ	'S'+O2
_T	equ	'T'+O2
_U	equ	'U'+O2
_X	equ	'X'+O2
_Z	equ	'Z'+O2

_first	equ	'Z'+1
; original table tokens
; cbs_tab
_rlc	equ	_first+O2+cbs_tab_off
_rrc	equ	_rlc+1
_rl	equ	_rrc+1
_rr	equ	_rl+1
_sla	equ	_rr+2
_sra	equ	_sla+1
_qmark	equ	_sra+1
_srl	equ	_qmark+1
	
; cc_tab
_nz	equ	_first+O2+cc_tab_off

; ddss_tab (only need "HL", SP)
_reghl	equ	_first+O2+ddss_tab_off+2
_sp	equ	_reghl+1

; qq_tab
_bc	equ	_first+O2+qq_tab_off
_de	equ	_bc+1
_hl	equ	_de+1
_af	equ	_hl+1

; composite tokens
_ld	equ	_first+O2+40
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


