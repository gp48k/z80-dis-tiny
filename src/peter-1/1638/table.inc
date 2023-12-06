rule_00:
	defb	cmd_lit,0x76,'H'+O,'A'+O,'L'+O,'T'+O,cmd_end_rule
	defb	cmd_page01,cmd_s6,cmd_disp,'L'+O,'D'+O,' '+O,cmd_r,','+O,cmd_hl,cmd_end_rule
	defb	cmd_page01,cmd_r6,cmd_disp,'L'+O,'D'+O,' '+O,cmd_hl,','+O,cmd_s,cmd_end_rule
	defb	cmd_page01,cmd_hack_inc,'L'+O,'D'+O,' '+O,cmd_r,','+O,cmd_s,cmd_end_rule
	defb	cmd_lit,0x36,cmd_disp,'L'+O,'D'+O,' '+O,cmd_hl,','+O,cmd_n,cmd_end_rule
	defb	cmd_page00,cmd_s6,'L'+O,'D'+O,' '+O,cmd_r,','+O,cmd_n,cmd_end_rule
	defb	cmd_lit,0x0A,'L'+O,'D'+O,' '+O,'A'+O,','+O,'('+O,'B'+O,'C'+O,')'+O,cmd_end_rule
	defb	cmd_lit,0x1A,'L'+O,'D'+O,' '+O,'A'+O,','+O,'('+O,'D'+O,'E'+O,')'+O,cmd_end_rule
	defb	cmd_lit,0x3A,'L'+O,'D'+O,' '+O,'A'+O,','+O,cmd_np,cmd_end_rule
	defb	cmd_page00,cmd_n1,'L'+O,'D'+O,' '+O,cmd_dd,','+O,cmd_nn,cmd_end_rule
	defb	cmd_lit,0x02,'L'+O,'D'+O,' '+O,'('+O,'B'+O,'C'+O,')'+O,','+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x12,'L'+O,'D'+O,' '+O,'('+O,'D'+O,'E'+O,')'+O,','+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x32,'L'+O,'D'+O,' '+O,cmd_np,','+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x22,'L'+O,'D'+O,' '+O,cmd_np,','+O,cmd_reghl,cmd_end_rule
	defb	cmd_lit,0x2A,'L'+O,'D'+O,' '+O,cmd_reghl,','+O,cmd_np,cmd_end_rule
	defb	cmd_lit,0x08,'E'+O,'X'+O,' '+O,'A'+O,'F'+O,','+O,'A'+O,'F'+O,39+O,cmd_end_rule
	defb	cmd_lit,0x34,cmd_disp,'I'+O,'N'+O,'C'+O,' '+O,cmd_hl,cmd_end_rule
	defb	cmd_page00,cmd_s4,'I'+O,'N'+O,'C'+O,' '+O,cmd_r,cmd_end_rule
	defb	cmd_lit,0x35,cmd_disp,'D'+O,'E'+O,'C'+O,' '+O,cmd_hl,cmd_end_rule
	defb	cmd_page00,cmd_s5,'D'+O,'E'+O,'C'+O,' '+O,cmd_r,cmd_end_rule
	defb	cmd_lit,0x27,'D'+O,'A'+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x2F,'C'+O,'P'+O,'L'+O,cmd_end_rule
	defb	cmd_lit,0x3F,'C'+O,'C'+O,'F'+O,cmd_end_rule
	defb	cmd_lit,0x37,'S'+O,'C'+O,'F'+O,cmd_end_rule
	defb	cmd_lit,0x00,'N'+O,'O'+O,'P'+O,cmd_end_rule
	defb	cmd_page00,cmd_n9,'A'+O,'D'+O,'D'+O,' '+O,cmd_reghl,','+O,cmd_dd,cmd_end_rule
	defb	cmd_lit,0x07,'R'+O,'L'+O,'C'+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x17,'R'+O,'L'+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x0F,'R'+O,'R'+O,'C'+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x1F,'R'+O,'R'+O,'A'+O,cmd_end_rule
	defb	cmd_page00,cmd_n3,'I'+O,'N'+O,'C'+O,' '+O,cmd_dd,cmd_end_rule
	defb	cmd_page00,cmd_nB,'D'+O,'E'+O,'C'+O,' '+O,cmd_dd,cmd_end_rule
	defb	cmd_lit,0x18,'J'+O,'R'+O,' '+O,cmd_e,cmd_end_rule
	defb	cmd_rc,','+O,cmd_e,cmd_end_rule
	defb	cmd_lit,0x10,'D'+O,'J'+O,'N'+O,'Z'+O,' '+O,cmd_e,cmd_end_rule
	defb	cmd_page10,cmd_s6,cmd_alu,cmd_disp,cmd_hl,cmd_end_rule
	defb	cmd_page10,cmd_hack_inc,cmd_alu,cmd_s,cmd_end_rule
	defb	cmd_page11,cmd_s6,cmd_alu,cmd_n,cmd_end_rule
	defb	cmd_lit,0xF9,'L'+O,'D'+O,' '+O,'S'+O,'P'+O,','+O,cmd_reghl,cmd_end_rule
	defb	cmd_lit,0xE5,'P'+O,'U'+O,'S'+O,'H'+O,' '+O,cmd_reghl,cmd_end_rule
	defb	cmd_page11,cmd_n5,'P'+O,'U'+O,'S'+O,'H'+O,' '+O,cmd_qq,cmd_end_rule
	defb	cmd_lit,0xE1,'P'+O,'O'+O,'P'+O,' '+O,cmd_reghl,cmd_end_rule
	defb	cmd_page11,cmd_n1,'P'+O,'O'+O,'P'+O,' '+O,cmd_qq,cmd_end_rule
	defb	cmd_lit,0xEB,'E'+O,'X'+O,' '+O,'D'+O,'E'+O,','+O,'H'+O,'L'+O,cmd_end_rule
	defb	cmd_lit,0x08,'E'+O,'X'+O,' '+O,'A'+O,'F'+O,','+O,'A'+O,'F'+O,39+O,cmd_end_rule
	defb	cmd_lit,0xD9,'E'+O,'X'+O,'X'+O,cmd_end_rule
	defb	cmd_lit,0xE3,'E'+O,'X'+O,' '+O,'('+O,'S'+O,'P'+O,')'+O,','+O,cmd_reghl,cmd_end_rule
	defb	cmd_lit,0xF3,'D'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0xFB,'E'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0xC3,'J'+O,'P'+O,' '+O,cmd_nn,cmd_end_rule
	defb	cmd_page11,cmd_s2,'J'+O,'P'+O,' '+O,cmd_cc,','+O,cmd_nn,cmd_end_rule
	defb	cmd_lit,0xE9,'J'+O,'P'+O,' '+O,'('+O,cmd_reghl,')'+O,cmd_end_rule
	defb	cmd_lit,0xCD,'C'+O,'A'+O,'L'+O,'L'+O,' '+O,cmd_nn,cmd_end_rule
	defb	cmd_page11,cmd_s4,'C'+O,'A'+O,'L'+O,'L'+O,' '+O,cmd_cc,','+O,cmd_nn,cmd_end_rule
	defb	cmd_lit,0xC9,'R'+O,'E'+O,'T'+O,cmd_end_rule
	defb	cmd_page11,cmd_s0,'R'+O,'E'+O,'T'+O,' '+O,cmd_cc,cmd_end_rule
	defb	cmd_page11,cmd_s7,'R'+O,'S'+O,'T'+O,' '+O,cmd_rst,cmd_end_rule
	defb	cmd_lit,0xDB,'I'+O,'N'+O,' '+O,'A'+O,','+O,'('+O,cmd_n,')'+O,cmd_end_rule
	defb	cmd_lit,0xD3,'O'+O,'U'+O,'T'+O,' '+O,'('+O,cmd_n,')'+O,','+O,'A'+O,cmd_end_rule
	defb	cmd_end_table
rule_ed:
	defb	cmd_lit,0x57,'L'+O,'D'+O,' '+O,'A'+O,','+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0x5F,'L'+O,'D'+O,' '+O,'A'+O,','+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0x47,'L'+O,'D'+O,' '+O,'I'+O,','+O,'A'+O,cmd_end_rule
	defb	cmd_lit,0x4F,'L'+O,'D'+O,' '+O,'R'+O,','+O,'A'+O,cmd_end_rule
	defb	cmd_page01,cmd_nB,'L'+O,'D'+O,' '+O,cmd_dd,','+O,'('+O,cmd_nn,')'+O,cmd_end_rule
	defb	cmd_page01,cmd_n3,'L'+O,'D'+O,' '+O,'('+O,cmd_nn,')'+O,','+O,cmd_dd,cmd_end_rule
	defb	cmd_lit,0xA0,'L'+O,'D'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0xB0,'L'+O,'D'+O,'I'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0xA8,'L'+O,'D'+O,'D'+O,cmd_end_rule
	defb	cmd_lit,0xB8,'L'+O,'D'+O,'D'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0xA1,'C'+O,'P'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0xB1,'C'+O,'P'+O,'I'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0xA9,'C'+O,'P'+O,'D'+O,cmd_end_rule
	defb	cmd_lit,0xB9,'C'+O,'P'+O,'D'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0x44,'N'+O,'E'+O,'G'+O,cmd_end_rule
	defb	cmd_lit,0x46,'I'+O,'M'+O,' '+O,'0'+O,cmd_end_rule
	defb	cmd_lit,0x56,'I'+O,'M'+O,' '+O,'1'+O,cmd_end_rule
	defb	cmd_lit,0x5E,'I'+O,'M'+O,' '+O,'2'+O,cmd_end_rule
	defb	cmd_page01,cmd_nA,'A'+O,'D'+O,'C'+O,' '+O,'H'+O,'L'+O,','+O,cmd_dd,cmd_end_rule
	defb	cmd_page01,cmd_n2,'S'+O,'B'+O,'C'+O,' '+O,'H'+O,'L'+O,','+O,cmd_dd,cmd_end_rule
	defb	cmd_page01,cmd_s0,'I'+O,'N'+O,' '+O,cmd_r,','+O,'('+O,'C'+O,')'+O,cmd_end_rule
	defb	cmd_lit,0xA2,'I'+O,'N'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0xB2,'I'+O,'N'+O,'I'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0xAA,'I'+O,'N'+O,'D'+O,cmd_end_rule
	defb	cmd_lit,0xBA,'I'+O,'N'+O,'D'+O,'R'+O,cmd_end_rule
	defb	cmd_page01,cmd_s1,'O'+O,'U'+O,'T'+O,' '+O,'('+O,'C'+O,')'+O,','+O,cmd_r,cmd_end_rule
	defb	cmd_lit,0xA3,'O'+O,'U'+O,'T'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0xB3,'O'+O,'T'+O,'I'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0xAB,'O'+O,'U'+O,'T'+O,'D'+O,cmd_end_rule
	defb	cmd_lit,0xBB,'O'+O,'T'+O,'D'+O,'R'+O,cmd_end_rule
	defb	cmd_lit,0x4D,'R'+O,'E'+O,'T'+O,'I'+O,cmd_end_rule
	defb	cmd_lit,0x45,'R'+O,'E'+O,'T'+O,'N'+O,cmd_end_rule
	defb	cmd_lit,0x67,'R'+O,'R'+O,'D'+O,cmd_end_rule
	defb	cmd_lit,0x6F,'R'+O,'L'+O,'D'+O,cmd_end_rule
	defb	cmd_end_table
rule_cb:
	defb	cmd_page00,cmd_s6,cmd_cbs,' '+O,cmd_hl,cmd_end_rule
	defb	cmd_page00,cmd_hack_inc,cmd_cbs,' '+O,cmd_s,cmd_end_rule
	defb	cmd_page01,cmd_s6,'B'+O,'I'+O,'T'+O,' '+O,cmd_b,','+O,cmd_hl,cmd_end_rule
	defb	cmd_page01,cmd_hack_inc,'B'+O,'I'+O,'T'+O,' '+O,cmd_b,','+O,cmd_s,cmd_end_rule
	defb	cmd_page10,cmd_s6,'R'+O,'E'+O,'S'+O,' '+O,cmd_b,','+O,cmd_hl,cmd_end_rule
	defb	cmd_page10,cmd_hack_inc,'R'+O,'E'+O,'S'+O,' '+O,cmd_b,','+O,cmd_s,cmd_end_rule
	defb	cmd_page11,cmd_s6,'S'+O,'E'+O,'T'+O,' '+O,cmd_b,','+O,cmd_hl,cmd_end_rule
	defb	cmd_page11,cmd_hack_inc,'S'+O,'E'+O,'T'+O,' '+O,cmd_b,','+O,cmd_s,cmd_end_rule
	defb	cmd_end_table
