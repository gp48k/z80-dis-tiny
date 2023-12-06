table_start:
	defb	rule_00_11-rule_00_10
	defb	rule_00_10-rule_00_01
	defb	rule_00_01-rule_00_00
rule_00:
rule_00_00:
	defb	cmd_t36,cmd_disp,_lds,cmd_hl,__c,cmd_n,cmd_end_rule	; 0x36
	defb	cmd_s6,_lds,cmd_r,__c,cmd_n,cmd_end_rule
	defb	cmd_t2A,_lds,cmd_reghl,__c,cmd_np,cmd_end_rule	; 0x2A
	defb	cmd_t3A,_lds,_Ac,cmd_np,cmd_end_rule	; 0x3A
	defb	cmd_nA,_lds,_Ac,__p,cmd_dd,__q,cmd_end_rule
	defb	cmd_n1,_lds,cmd_dd,__c,cmd_nn,cmd_end_rule

	defb	cmd_t22,_lds,cmd_np,__c,cmd_reghl,cmd_end_rule	; 0x22
	defb	cmd_t32,_lds,cmd_np,_cA,cmd_end_rule	; 0x32
	defb	cmd_n2,_lds,__p,cmd_dd,__q,_cA,cmd_end_rule

	defb	cmd_t08,_exs,_af,__c,_af,__a,cmd_end_rule	; 0x08
	defb	cmd_t34,cmd_disp,_incs,cmd_hl,cmd_end_rule	; 0x34
	defb	cmd_s4,_incs,cmd_r,cmd_end_rule
	defb	cmd_t35,cmd_disp,_decs,cmd_hl,cmd_end_rule	; 0x35
	defb	cmd_s5,_decs,cmd_r,cmd_end_rule
	defb	cmd_t00,_N,_O,_P,cmd_end_rule	; 0x00
	defb	cmd_n9,_A,_D,_D,__s,cmd_reghl,__c,cmd_dd,cmd_end_rule

	defb	cmd_t27,_D,_A,_A,cmd_end_rule	; 0x27
	defb	cmd_t2F,_cp,_L,cmd_end_rule	; 0x2F
	defb	cmd_t37,_S,_C,_F,cmd_end_rule	; 0x37
	defb	cmd_t3F,_C,_C,_F,cmd_end_rule	; 0x3F

	defb	cmd_s7,cmd_cbs,_A,cmd_end_rule

	defb	cmd_n3,_incs,cmd_dd,cmd_end_rule
	defb	cmd_nB,_decs,cmd_dd,cmd_end_rule
	defb	cmd_t18,_jrs,cmd_e,cmd_end_rule	; 0x18
	defb	cmd_jr,_jrs,cmd_rc,__c,cmd_e,cmd_end_rule
	defb	cmd_t10,_D,_J,_nz,__s,cmd_e,cmd_end_rule	; 0x10
	defb	cmd_end_table
rule_00_01:
	defb	cmd_t36,_H,_A,_L,_T,cmd_end_rule	; 0x76
	defb	cmd_s6,cmd_disp,_lds,cmd_r,__c,cmd_hl,cmd_end_rule
	defb	cmd_r6,cmd_disp,_lds,cmd_hl,__c,cmd_s,cmd_end_rule
	defb	cmd_hack_inc,_lds,cmd_r,__c,cmd_s,cmd_end_rule
	defb	cmd_end_table
rule_00_10:
	defb	cmd_s6,cmd_alu,cmd_disp,cmd_hl,cmd_end_rule
	defb	cmd_hack_inc,cmd_alu,cmd_s,cmd_end_rule
	defb	cmd_end_table
rule_00_11:
	defb	cmd_s6,cmd_alu,cmd_n,cmd_end_rule
	defb	cmd_t39,_lds,_sp,__c,cmd_reghl,cmd_end_rule	; 0xF9
	defb	cmd_t25,_pushs,cmd_reghl,cmd_end_rule	; 0xE5
	defb	cmd_n5,_pushs,cmd_qq,cmd_end_rule
	defb	cmd_t21,_pops,cmd_reghl,cmd_end_rule	; 0xE1
	defb	cmd_n1,_pops,cmd_qq,cmd_end_rule
	defb	cmd_t2B,_exs,_de,__c,_hl,cmd_end_rule	; 0xEB
	defb	cmd_t19,_E,_X,_X,cmd_end_rule	; 0xD9
	defb	cmd_t23,_exs,__p,_sp,__q,__c,cmd_reghl,cmd_end_rule	; 0xE3
	defb	cmd_t33,_D,_I,cmd_end_rule	; 0xF3
	defb	cmd_t3B,_E,_I,cmd_end_rule	; 0xFB
	defb	cmd_t03,_jps,cmd_nn,cmd_end_rule	; 0xC3
	defb	cmd_s2,_jps,cmd_cc,__c,cmd_nn,cmd_end_rule
	defb	cmd_t29,_jps,__p,cmd_reghl,__q,cmd_end_rule	;0xE9
	defb	cmd_t0D,_calls,cmd_nn,cmd_end_rule	; 0xCD
	defb	cmd_s4,_calls,cmd_cc,__c,cmd_nn,cmd_end_rule
	defb	cmd_t09,_ret,cmd_end_rule	; 0xC9
	defb	cmd_s0,_ret,__s,cmd_cc,cmd_end_rule
	defb	cmd_s7,_R,_S,_T,__s,cmd_rst,cmd_end_rule
	defb	cmd_t1B,_in,__s,_Ac,__p,cmd_n,__q,cmd_end_rule	; 0xDB
	defb	cmd_t13,_out,__s,__p,cmd_n,__q,_cA,cmd_end_rule	; 0xD3
	defb	cmd_end_table

	defb	rule_ed_11-rule_ed_10
	defb	rule_ed_10-rule_ed_01
	defb	rule_ed_01-rule_ed_00
rule_ed:
rule_ed_00:	; TODO: empty
	defb	cmd_end_table		; TODO could use previous table's end
rule_ed_01:
	defb	cmd_t17,_lds,_Ac,_I,cmd_end_rule	; 0x57
	defb	cmd_t1F,_lds,_Ac,_R,cmd_end_rule	; 0x5F
	defb	cmd_t07,_lds,_I,_cA,cmd_end_rule	; 0x47
	defb	cmd_t0F,_lds,_R,_cA,cmd_end_rule	; 0x4F
	defb	cmd_nB,_lds,cmd_dd,__c,__p,cmd_nn,__q,cmd_end_rule
	defb	cmd_n3,_lds,__p,cmd_nn,__q,__c,cmd_dd,cmd_end_rule
	defb	cmd_t04,_N,_E,_G,cmd_end_rule	; 0x44
	defb	cmd_t06,_ims,_0,cmd_end_rule	; 0x46
	defb	cmd_t16,_ims,_1,cmd_end_rule	; 0x56
	defb	cmd_t1E,_ims,_2,cmd_end_rule	; 0x5E
	defb	cmd_nA,_A,_D,_C,__s,_hl,__c,cmd_dd,cmd_end_rule
	defb	cmd_n2,_S,_bc,__s,_hl,__c,cmd_dd,cmd_end_rule
	defb	cmd_s0,_in,__s,cmd_r,__c,__p,_C,__q,cmd_end_rule
	defb	cmd_t0D,_ret,_I,cmd_end_rule	; 0x4D
	defb	cmd_t05,_ret,_N,cmd_end_rule	; 0x45
	defb	cmd_t27,_rr,_D,cmd_end_rule	; 0x67
	defb	cmd_t2F,_R,_ld,cmd_end_rule	; 0x6F
	defb	cmd_s1,_out,__s,__p,_C,__q,__c,cmd_r,cmd_end_rule
	defb	cmd_end_table
rule_ed_10:
	defb	cmd_t20,_ld,_I,cmd_end_rule	; 0xA0
	defb	cmd_t30,_ld,_ir,cmd_end_rule	; 0xB0
	defb	cmd_t28,_ld,_D,cmd_end_rule	; 0xA8
	defb	cmd_t38,_ld,_dr,cmd_end_rule	; 0xB8
	defb	cmd_t21,_cp,_I,cmd_end_rule	; 0xA1
	defb	cmd_t31,_cp,_ir,cmd_end_rule	; 0xB1
	defb	cmd_t29,_cp,_D,cmd_end_rule	; 0xA9
	defb	cmd_t39,_cp,_dr,cmd_end_rule	; 0x89
	defb	cmd_t22,_in,_I,cmd_end_rule	; 0xA2
	defb	cmd_t32,_in,_ir,cmd_end_rule	; 0xB2
	defb	cmd_t2A,_in,_D,cmd_end_rule	; 0xAA
	defb	cmd_t3A,_in,_dr,cmd_end_rule	; 0xBA
	defb	cmd_t23,_out,_I,cmd_end_rule	; 0xA3
	defb	cmd_t33,_O,_T,_ir,cmd_end_rule	; 0xB3
	defb	cmd_t2B,_out,_D,cmd_end_rule	; 0xAB
	defb	cmd_t3B,_O,_T,_dr,cmd_end_rule	; 0xBB
rule_ed_11: ; empty
	defb	cmd_end_table

	defb	rule_cb_11-rule_cb_10
	defb	rule_cb_10-rule_cb_01
	defb	rule_cb_01-rule_cb_00
rule_cb:
rule_cb_00:
	defb	cmd_s6,cmd_cbs,__s,cmd_hl,cmd_end_rule
	defb	cmd_hack_inc,cmd_cbs,__s,cmd_s,cmd_end_rule
	defb	cmd_end_table
rule_cb_01:
	defb	cmd_s6,_bit,cmd_b,__c,cmd_hl,cmd_end_rule
	defb	cmd_hack_inc,_bit,cmd_b,__c,cmd_s,cmd_end_rule
	defb	cmd_end_table
rule_cb_10:
	defb	cmd_s6,_res,cmd_b,__c,cmd_hl,cmd_end_rule
	defb	cmd_hack_inc,_res,cmd_b,__c,cmd_s,cmd_end_rule
	defb	cmd_end_table
rule_cb_11:
	defb	cmd_s6,_set,cmd_b,__c,cmd_hl,cmd_end_rule
	defb	cmd_hack_inc,_set,cmd_b,__c,cmd_s,cmd_end_rule
	defb	cmd_end_table

