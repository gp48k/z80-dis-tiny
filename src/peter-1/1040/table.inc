table_start:
	defb	rule_00_11-rule_00_10
	defb	rule_00_10-rule_00_01
	defb	rule_00_01-rule_00_00
rule_00:
rule_00_00:
	defb	cmd_t36,_lds,prt_hl_disp,__c,prt_n	; 0x36
	defb	cmd_s6,_lds,prt_r,__c,prt_n
	defb	cmd_t2A,_lds,_reghl,__c,prt_np	; 0x2A
	defb	cmd_t3A,_lds,_Ac,prt_np	; 0x3A
	defb	cmd_nA,_lds,_Ac,__p,prt_dd,__q
	defb	cmd_n1,_lds,prt_dd,__c,prt_nn

	defb	cmd_t22,_lds,prt_np,__c,_reghl	; 0x22
	defb	cmd_t32,_lds,prt_np,_cA	; 0x32
	defb	cmd_n2,_lds,__p,prt_dd,__q,_cA

	defb	cmd_t08,_exs,_af,__c,_af,__a	; 0x08
	defb	cmd_t34,_incs,prt_hl_disp	; 0x34
	defb	cmd_s4,_incs,prt_r
	defb	cmd_t35,_decs,prt_hl_disp	; 0x35
	defb	cmd_s5,_decs,prt_r
	defb	cmd_t00,_N,_O,_P	; 0x00
	defb	cmd_n9,_A,_D,_D,__s,_reghl,__c,prt_dd

	defb	cmd_t27,_D,_A,_A	; 0x27
	defb	cmd_t2F,_cp,_L	; 0x2F
	defb	cmd_t37,_S,_C,_F	; 0x37
	defb	cmd_t3F,_C,_C,_F	; 0x3F

	defb	cmd_s7,prt_cbs,_A

	defb	cmd_n3,_incs,prt_dd
	defb	cmd_nB,_decs,prt_dd
	defb	cmd_t18,_jrs,prt_e	; 0x18
	defb	cmd_t10,_D,_J,_nz,__s,prt_e	; 0x10

; in theory, only JR cc is left but trouble removing "cmd_jr"
	; only JR cc is left in table
	defb	cmd_hack_inc,_jrs,prt_rc,__c,prt_e

; Also, can remove, all cases handled
;;full	defb	cmd_end_table

rule_00_01:
	defb	cmd_t36,_H,_A,_L,_T	; 0x76
	defb	cmd_r6,_lds,prt_hl_disp,__c,prt_s
	defb	cmd_s6,_lds,prt_r,__c,prt_hl_disp
	defb	cmd_hack_inc,_lds,prt_r,__c,prt_s
;;full	defb	cmd_end_table
rule_00_10:
	defb	cmd_s6,prt_alu,prt_hl_disp
	defb	cmd_hack_inc,prt_alu,prt_s
;;full	defb	cmd_end_table
rule_00_11:
	defb	cmd_s6,prt_alu,prt_n
	defb	cmd_t39,_lds,_sp,__c,_reghl	; 0xF9
	defb	cmd_t25,_pushs,_reghl	; 0xE5
	defb	cmd_n5,_pushs,prt_qq
	defb	cmd_t21,_pops,_reghl	; 0xE1
	defb	cmd_n1,_pops,prt_qq
	defb	cmd_t2B,_exs,_de,__c,_hl	; 0xEB
	defb	cmd_t19,_E,_X,_X	; 0xD9
	defb	cmd_t23,_exs,__p,_sp,__q,__c,_reghl	; 0xE3
	defb	cmd_t33,_D,_I	; 0xF3
	defb	cmd_t3B,_E,_I	; 0xFB
	defb	cmd_t03,_jps,prt_nn	; 0xC3
	defb	cmd_s2,_jps,prt_cc,__c,prt_nn
	defb	cmd_t29,_jps,__p,_reghl,__q	;0xE9
	defb	cmd_t0D,_calls,prt_nn	; 0xCD
	defb	cmd_s4,_calls,prt_cc,__c,prt_nn
	defb	cmd_t09,_ret	; 0xC9
	defb	cmd_s0,_ret,__s,prt_cc
	defb	cmd_s7,_R,_S,_T,__s,prt_rst
	defb	cmd_t1B,_in,__s,_Ac,__p,prt_n,__q	; 0xDB
	defb	cmd_t13,_out,__s,__p,prt_n,__q,_cA	; 0xD3
	defb	cmd_end_table

	defb	rule_ed_11-rule_ed_10
	defb	rule_ed_10-rule_ed_01
	defb	rule_ed_01-rule_ed_00
rule_ed:
rule_ed_00:	; TODO: empty
	defb	cmd_end_table		; TODO could use previous table's end
rule_ed_01:
	defb	cmd_t17,_lds,_Ac,_I	; 0x57
	defb	cmd_t1F,_lds,_Ac,_R	; 0x5F
	defb	cmd_t07,_lds,_I,_cA	; 0x47
	defb	cmd_t0F,_lds,_R,_cA	; 0x4F
	defb	cmd_nB,_lds,prt_dd,__c,__p,prt_nn,__q
	defb	cmd_n3,_lds,__p,prt_nn,__q,__c,prt_dd
	defb	cmd_t04,_N,_E,_G	; 0x44
	defb	cmd_t06,_ims,_0	; 0x46
	defb	cmd_t16,_ims,_1	; 0x56
	defb	cmd_t1E,_ims,_2	; 0x5E
	defb	cmd_nA,_A,_D,_C,__s,_hl,__c,prt_dd
	defb	cmd_n2,_S,_bc,__s,_hl,__c,prt_dd
	defb	cmd_s0,_in,__s,prt_r,__c,__p,_C,__q
	defb	cmd_t0D,_ret,_I	; 0x4D
	defb	cmd_t05,_ret,_N	; 0x45
	defb	cmd_t27,_rr,_D	; 0x67
	defb	cmd_t2F,_R,_ld	; 0x6F
	defb	cmd_s1,_out,__s,__p,_C,__q,__c,prt_r
	defb	cmd_end_table
rule_ed_10:
	defb	cmd_t20,_ld,_I	; 0xA0
	defb	cmd_t30,_ld,_ir	; 0xB0
	defb	cmd_t28,_ld,_D	; 0xA8
	defb	cmd_t38,_ld,_dr	; 0xB8
	defb	cmd_t21,_cp,_I	; 0xA1
	defb	cmd_t31,_cp,_ir	; 0xB1
	defb	cmd_t29,_cp,_D	; 0xA9
	defb	cmd_t39,_cp,_dr	; 0x89
	defb	cmd_t22,_in,_I	; 0xA2
	defb	cmd_t32,_in,_ir	; 0xB2
	defb	cmd_t2A,_in,_D	; 0xAA
	defb	cmd_t3A,_in,_dr	; 0xBA
	defb	cmd_t23,_out,_I	; 0xA3
	defb	cmd_t33,_O,_T,_ir	; 0xB3
	defb	cmd_t2B,_out,_D	; 0xAB
	defb	cmd_t3B,_O,_T,_dr	; 0xBB
rule_ed_11: ; empty
	defb	cmd_end_table

	defb	rule_cb_11-rule_cb_10
	defb	rule_cb_10-rule_cb_01
	defb	rule_cb_01-rule_cb_00
rule_cb:
rule_cb_00:
	defb	cmd_s6_special,prt_cbs,__s,prt_s
;;full	defb	cmd_end_table
rule_cb_01:
	defb	cmd_s6_special,_bit,prt_b,__c,prt_s
;;full	defb	cmd_end_table
rule_cb_10:
	defb	cmd_s6_special,_res,prt_b,__c,prt_s
;;full	defb	cmd_end_table
rule_cb_11:
	defb	cmd_s6_special,_set,prt_b,__c,prt_s
;;full	defb	cmd_end_table

