table_start:
rule_00:
	defb	rule_00_00-rule_00
	defb	rule_00_01-rule_00
	defb	rule_00_10-rule_00
	defb	rule_00_11-rule_00
rule_ed:
	defb	rule_ed_00-rule_ed
	defb	rule_ed_01-rule_ed
	defb	rule_ed_10-rule_ed
	defb	rule_ed_11-rule_ed
rule_cb:
	defb	rule_cb_00-rule_cb
	defb	rule_cb_01-rule_cb
	defb	rule_cb_10-rule_cb
	defb	rule_cb_11-rule_cb
rule_ed_00:	; empty
rule_ed_01:
	defb	cmd_t17,_ld,_sA2,_cI	; 0x57
	defb	cmd_t1F,_ld,_sA2,_cR	; 0x5F
	defb	cmd_t07,_ld,_sI,_cA	; 0x47
	defb	cmd_t0F,_ld,_sR,_cA	; 0x4F
	defb	cmd_nB,_ld,_sprt_dd,__cP,prt_nn,__q
	defb	cmd_n3,_ld,__sP,prt_nn,__q,_cprt_dd
	defb	cmd_t04,_N,_E,_G	; 0x44
	defb	cmd_s6,_I,_M,_sprt_im	; 0x46 0x56 0x5e
	defb	cmd_nA,_adc,_sHL,_cprt_dd
	defb	cmd_n2,_sbcX,_sHL,_cprt_dd
	defb	cmd_s0,_in,_sprt_r,_cpCq
	defb	cmd_t0D,_ret,_I	; 0x4D
	defb	cmd_t05,_ret,_N	; 0x45
	defb	cmd_t27,_rr,_D	; 0x67
	defb	cmd_t2F,_R,_ld	; 0x6F
	defb	cmd_s1,_out,_spCq,_cprt_r
rule_ed_10:
	defb	cmd_t23,_out,prt_move_dir	; 0xA3
	defb	cmd_t2B,_out,prt_move_dir	; 0xAB
	defb	cmd_accept,prt_move_op,prt_move_dir
rule_ed_11: ; empty
rule_cb_00:
	defb	cmd_s6_special,prt_cbs,_sprt_s
rule_cb_01:
	defb	cmd_s6_special,_B,_I,_T,_sprt_b,_cprt_s
rule_cb_10:
	defb	cmd_s6_special,_R,_E,_S,_sprt_b,_cprt_s
rule_cb_11:
	defb	cmd_s6_special,_S,_E,_T,_sprt_b,_cprt_s
rule_00_01:
	defb	cmd_t36,_H,_A,_L,_T	; 0x76
	defb	cmd_accept,_ld,_sprt_r,_cprt_s
rule_00_10:
	defb	cmd_accept,prt_alu,prt_s
rule_00_11:
	defb	cmd_s6,prt_alu,prt_n
	defb	cmd_t39,_ld,_sSP,_cregHL	; 0xF9
	defb	cmd_n5,_P,_U,_S,_H,_sprt_qq
	defb	cmd_n1,_P,_O,_P,_sprt_qq
	defb	cmd_t2B,_ex,_sDE,_cHL	; 0xEB
	defb	cmd_t19,_ex,_X	; 0xD9
	defb	cmd_t23,_ex,__sP,_sp,__q,_cregHL	; 0xE3
	defb	cmd_t33,_D,_I	; 0xF3
	defb	cmd_t3B,_E,_I	; 0xFB
	defb	cmd_t03,_jp,_sprt_nn	; 0xC3
	defb	cmd_s2,_jp,_sprt_cc,_cprt_nn
	defb	cmd_t29,_jp,__sP,_reghl,__q	;0xE9
	defb	cmd_t0D,_call,_sprt_nn	; 0xCD
	defb	cmd_s4,_call,_sprt_cc,_cprt_nn
	defb	cmd_t09,_ret	; 0xC9
	defb	cmd_s0,_ret,_sprt_cc
	defb	cmd_s7,_R,_S,_T,_sprt_rst
	defb	cmd_t1B,_in,_sA2,__cP,prt_n,__q	; 0xDB
	defb	cmd_t13,_out,__sP,prt_n,__q,_cA	; 0xD3
rule_00_00:
	defb	cmd_s6,_ld,_sprt_r,_cprt_n
	defb	cmd_t2A,_ld,_sregHL,_cprt_np	; 0x2A
	defb	cmd_t3A,_ld,_sA2,_cprt_np	; 0x3A
	defb	cmd_nA,_ld,_sA2,__cP,prt_dd,__q
	defb	cmd_n1,_ld,_sprt_dd,_cprt_nn

	defb	cmd_t22,_ld,_sprt_np,_cregHL	; 0x22
	defb	cmd_t32,_ld,_sprt_np,_cA	; 0x32
	defb	cmd_n2,_ld,__sP,prt_dd,__q,_cA

	defb	cmd_t08,_ex,_sAF,_cAF,__a	; 0x08
	defb	cmd_s4,_inc,_sprt_r
	defb	cmd_s5,_dec,_sprt_r
	defb	cmd_t00,_N,_O,_P	; 0x00
	defb	cmd_n9,_add,_sregHL,_cprt_dd

	defb	cmd_t27,_D,_A,_A	; 0x27
	defb	cmd_t2F,_cp,_L	; 0x2F
	defb	cmd_t37,_S,_C,_F	; 0x37
	defb	cmd_t3F,_C,_C,_F	; 0x3F

	defb	cmd_s7,prt_cbs,_A

	defb	cmd_n3,_inc,_sprt_dd
	defb	cmd_nB,_dec,_sprt_dd
	defb	cmd_t18,_jr,_sprt_e	; 0x18
	defb	cmd_t10,_D,_J,_nz,_sprt_e	; 0x10

	; only JR cc is left in table
	defb	cmd_accept,_jr,_sprt_rc,_cprt_e


