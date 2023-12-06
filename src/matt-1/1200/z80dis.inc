z80dis:
        xor     a
        ld      (isixiy),a
        ld      a,(hl)
        inc     hl
        jr      disw

rst8:
rrca3
        rrca
        rrca
        rrca
        and     7
        ret
        nop
        nop

rst10:
out_str_ind_hi
        rst     rrca3
        jr      out_str_ind
disw    cp      $40
        jr      disx
        nop

rst18:
out_str_ind
        jr      out_str_ind_p1-1

disx    jp      c,grp_00
        jr      disy

        pop     bc
rst20:
out_str_ind_p1
        inc     a
        jr      osi2
osi0    push    af
osi1    ld      a,(bc)
        inc     bc
        jr      osiz

rst28:
out_str_arg_hi
        rst     rrca3
        jr      out_str_arg
disy    cp      $80
        jr      disz
        nop

rst30:
out_str_arg
        ld      (otsarg),a
        jr      out_str
        nop
        nop
        nop

rst38:
out_str
ots0    pop     bc
        ld      a,(bc)
        inc     bc
        push    bc
        rlca
        push    af
        rrca
        jr      nc,ots1
        and     $3f
        add     a,32
ots1    ld      bc,ots2
        push    bc
        ld      (de),a
        sub     a,'3'
        ld      b,a
otsarg  equ     $+1
        ld      a,0
        jp      z,out_reg
        dec     b
        jp      z,hexb_at_hl
        dec     b
        jp      z,hexw_at_hl
        dec     b
        jp      z,out_hlixiy
        dec     b
        jp      z,out_rp0
        dec     b
        jp      z,out_rp
        dec     b
        jp      z,out_cond
        pop     bc
        inc     de
ots2    pop     af
        jr      nc,ots0
        rlca
        ret     c
        pop     bc
        xor     a
        ld      (de),a
        ret

osiz    rlca
        jr      nc,osi1
        pop     af
osi2    dec     a
        jr      nz,osi0
        jr      out_str+1

disz    jp      c,grp_40
        cp      $c0
        jp      c,grp_80

grp_c0
        push    af
        and     7
        ld      b,a
gc00    jr      nz,gc01
isretc
        pop     af
        rst     out_str_arg_hi
        defb    'RET ','9'-32+128

gc01    djnz    gc02
        pop     af
        rst     rrca3
        rra
        jr      c,gc010
ispop
        rst     out_str_arg
        defb    'POP ','8'-32+128

gc010   or      a
        ld      b,a
        jr      nz,gc011
isret
        rst     out_str
        defb    'RE','T'-32+128
gc011   djnz    gc012
isexx
        rst     out_str
        defb    'EX','X'-32+128
gc012   dec     b
        ld      a,b
        rst     out_str_ind
        defb    'JP ','(6',')'-32+128
        defb    'LD SP,','6'-32+128

gc02    djnz    gc03
isjpc
        rst     out_str
        defb    'JP',' '-32+64+128
        jr      callc0

gc03    djnz    gc04
        pop     af
        rst     rrca3
        ld      b,a
gc030   jr      nz,gc031
isjp
        scf
        push    af
        jr      isjpc
gc031   dec     b
        jp      z,grp_cb        ;CB
gc032   djnz    gc033
isout
        rst     out_str
        defb    'OUT ','(4),','A'-32+128
gc033   djnz    gc034
isinp
        rst     out_str
        defb    'IN A,','(4',')'-32+128
gc034   djnz    gc035
isexsphl
        rst     out_str
        defb    'EX (SP),','6'-32+128
gc035   dec     b
        ld      a,b
        rst     out_str_ind
        defb    'EX DE,H','L'-32+128
        defb    'D','I'-32+128
        defb    'E','I'-32+128

gc04    djnz    gc05
iscallc
        rst     out_str
        defb    'CALL',' '-32+64+128
callc0  pop     af
        jp      c,hexw_at_hl
        rst     out_str_arg_hi
        defb    '9,','5'-32+128

gc05    djnz    gc06
        pop     af
        rst     rrca3
        rra
        jr      c,gc05x
ispush
        rst     out_str_arg
        defb    'PUSH ','8'-32+128

gc05x   or      a
        ld      b,a
        jr      nz,gc051
gc050   scf
        push    af
        jr      iscallc
gc051   dec     b
                                ;DD
        ; a=1
        jr      z,jpz80dis_p1
gc052   dec b
        jp      z,grp_ed        ;ED
gc053
                                ;FD
        ; a=3
        dec     a ; a=2
jpz80dis_p1
        jp      z80dis+1
gc06    djnz    gc07
isalun
        pop     af
        jr      grp_80

gc07
isrst
        rst     out_str
        defb    'RST',' '-32+64+128
        pop     af
        and     $38
        ld      b,a
        jp      hex_b

grp_80        
        push    af
        rst     rrca3
        call    isalux
        defb    'ADD A',','-32+128
        defb    'ADC A',','-32+128
        defb    'SUB',' '-32+128
        defb    'SBC A',','-32+128
        defb    'AND',' '-32+128
        defb    'XOR',' '-32+128
        defb    'OR',' '-32+128
        defb    'CP',' '-32+128
isalux
        pop     bc
        rst     out_str_ind_p1
        pop     af
        jp      c,out_reg
        jp      hexb_at_hl

grp_40
        cp      $76
        jr      nz,isld
ishalt
        rst     out_str
        defb    'HAL','T'-32+128
isld
        scf
isld_p1
        push    af
        rst     out_str_arg_hi
        defb    'LD 3',','-32+64+128
        pop     af
        jp      c,out_reg
        jp      hexb_at_hl
        
grp_00
        push    af
        and     7
        ld      b,a
g000    jr      nz,g001
        pop     af
        rst     rrca3
        ld      b,a
        jr      nz,g0001
g0000
isnop
        rst     out_str
        defb    'NO','P'-32+128
g0001   djnz    g0002
isexafaf
        rst     out_str
        defb    'EX AF,AF',''''-32+128
g0002   djnz    g0003
isdjnz
        rst     out_str
        defb    'DJNZ',' '-32+64+128
        jp      hex_rel
g0003   djnz    g0004
isjr
        scf
g0004
isjrc
        push    af
        rst     out_str
        defb    'JR',' '-32+64+128
        pop     af
        jr      c,jrc0
        and     3
        rst     out_str_arg
        defb    '9',','-32+64+128
jrc0    jp      hex_rel

g001    djnz    g002
        pop     af
        rst     rrca3
        rrca
        jr      c,isaddw
isldw
        rst     out_str_arg
        defb    'LD 7,','5'-32+128
isaddw
        rst     out_str_arg
        defb    'ADD 6,','7'-32+128

g002    djnz    g003
        pop     af
        rst     rrca3
        cp      4
        jr      nc,g0022
        rrca
        jr      c,g0021
        rst     out_str_arg
        defb    'LD (7),','A'-32+128
g0021   rst     out_str_arg
        defb    'LD A,(7',')'-32+128
g0022   cp      6
        jr      nc,g0024
        rrca
        jr      c,g0023
        rst     out_str
        defb    'LD (5),','6'-32+128
g0023   rst     out_str
        defb    'LD 6,(5',')'-32+128
g0024   rrca
        jr      c,g0025
        rst     out_str
        defb    'LD (5),','A'-32+128
g0025   rst     out_str
        defb    'LD A,(5',')'-32+128

g003    djnz    g004
isincdecw
        pop     af
        rst     rrca3
        rrca
        jr      c,isdecw
isincw
        rst     out_str_arg
        defb    'INC ','7'-32+128
isdecw
        rst     out_str_arg
        defb    'DEC ','7'-32+128

g004    djnz    g005
isinc
        pop     af
        rst     out_str_arg_hi
        defb    'INC ','3'-32+128

g005    djnz    g006
isdec
        pop     af
        rst     out_str_arg_hi
        defb    'DEC ','3'-32+128

g006    djnz    g007
isldn
        pop     af
        or      a
        jp      isld_p1

g007    pop     af
        rst     out_str_ind_hi
        defb    'RLC','A'-32+128
        defb    'RRC','A'-32+128
        defb    'RL','A'-32+128
        defb    'RR','A'-32+128
        defb    'DA','A'-32+128
        defb    'CP','L'-32+128
        defb    'SC','F'-32+128
        defb    'CC','F'-32+128

;===============================

grp_cb
        ld      a,(isixiy)
        or      a
        jr      z,notcbixiy
        ld      (isprefixed),a
        inc     hl
notcbixiy
        call    grp_cbx
        xor     a
        ld      (isprefixed),a
        ret

grp_cbx
        ld      a,(hl)
        inc     hl
        cp      $40
        jr      c,grp_cb00
grp_cbc0
grp_cb80
grp_cb40
        push    af
        rlca
        rlca
        and     3
        dec     a
        call    bitx
        defb    'BIT',' '-32+128
        defb    'RES',' '-32+128
        defb    'SET',' '-32+128
bitx    pop     bc
        rst     out_str_ind_p1
        pop     af
        push    af
        rst     rrca3
        add     a,'0'
        ld      (de),a
        inc     de
        pop     af
        rst     out_str_arg
        defb    ',','3'-32+128

grp_cb00
        push    af
        rst     rrca3
        call    iscbalu
        defb    'RLC',' '-32+128
        defb    'RRC',' '-32+128
        defb    'RL',' '-32+128
        defb    'RR',' '-32+128
        defb    'SLA',' '-32+128
        defb    'SRA',' '-32+128
        defb    128
        defb    'SRL',' '-32+128
iscbalu
        pop     bc
        rst     out_str_ind_p1
        pop     af
        jp      c,out_reg
        jp      hexb_at_hl

grp_ed
        ld      a,(hl)
        inc     hl
        cp      $40
        jr      c,grp_ed00
        cp      $80
        jr      c,grp_ed40
        cp      $c0
        jr      nc,grp_edc0
grp_ed80
        push    af
        and     7
        ld      b,a
        pop     af
        rst     rrca3
        sub     4
        jr      c,xit80
        inc     b
        djnz    ged801
gedc00  rst     out_str_ind
        defb    'LD','I'-32+128     
        defb    'LD','D'-32+128     
        defb    'LDI','R'-32+128     
        defb    'LDD','R'-32+128     
             
ged801  djnz    ged802
        rst     out_str_ind
        defb    'CP','I'-32+128     
        defb    'CP','D'-32+128     
        defb    'CPI','R'-32+128     
        defb    'CPD','R'-32+128     

ged802  djnz    ged803
        rst     out_str_ind
        defb    'IN','I'-32+128     
        defb    'IN','D'-32+128     
        defb    'INI','R'-32+128     
        defb    'IND','R'-32+128
             
ged803  djnz    ged804
        rst     out_str_ind
        defb    'OUT','I'-32+128     
        defb    'OUT','D'-32+128     
        defb    'OTI','R'-32+128     
        defb    'OTD','R'-32+128

ged804
grp_edc0
xit80
grp_ed00
xited
        xor     a
        ld      (de),a
        ret

grp_ed40
        push    af
        and     7
        ld      b,a
        jr      nz,ged401
ged400
isinpc
        pop     af
        rst     out_str_arg_hi
        defb    'IN 3,(C',')'-32+128

ged401  djnz    ged402
isoutc
        pop     af
        rst     out_str
        defb    'OUT (C),','3'-32+128

ged402  djnz    ged403
        pop     af
        rst     rrca3
        rrca
        jr      c,isadcw
issbcw
        rst     out_str_arg
        defb    'SBC 6,','7'-32+128
isadcw
        rst     out_str_arg
        defb    'ADC 6,','7'-32+128

ged403  djnz    ged404
        pop     af
        rst     rrca3
        rrca
        jr      c,isldrpatnn
isldatnnrp
        rst     out_str_arg
        defb    'LD (5),','7'-32+128
isldrpatnn
        rst     out_str_arg
        defb    'LD 7,(5',')'-32+128

ged404  djnz    ged405
        pop     af
        and     $38
        jr      nz,xited
isneg
        rst     out_str
        defb    'NE','G'-32+128

ged405  djnz    ged406
        pop     af
        rst     out_str_ind_hi
        defb    'RET','N'-32+128
        defb    'RET','I'-32+128
        defb    128
        defb    128
        defb    128
        defb    128
        defb    128
        defb    128

ged406  djnz    ged407
        pop     af
        rst     out_str_ind_hi
        defb    'IM ','0'-32+128
        defb    128
        defb    'IM ','1'-32+128
        defb    'IM ','2'-32+128
        defb    128
        defb    128
        defb    128
        defb    128

ged407  pop     af
        rst     out_str_ind_hi
        defb    'LD I,','A'-32+128
        defb    'LD R,','A'-32+128
        defb    'LD A,','I'-32+128
        defb    'LD A,','R'-32+128
        defb    'RR','D'-32+128
        defb    'RL','D'-32+128
        defb    128
        defb    128

;===============================

out_hlixiy
        ld      a,(isixiy)
        rst     out_str_ind
        defb    'H','L'-32+128
        defb    'I','X'-32+128
        defb    'I','Y'-32+128

out_rp0
        inc     a
        and     3
        jr      z,rp0
        dec     a
out_rp
        inc     a
        and     3
        inc     a
rp0     cp      4
        jr      c,nothlixiy
        ld      b,a
isixiy  equ     $+1
        ld      a,0
        add     a,b
nothlixiy
        rst     out_str_ind
        defb    'S','P'-32+128
        defb    'A','F'-32+128
        defb    'B','C'-32+128
        defb    'D','E'-32+128
        defb    'H','L'-32+128
        defb    'I','X'-32+128
        defb    'I','Y'-32+128
        
out_cond
        and     7
        call    ocx
        defb    'N','Z'-32+128
        defb    'Z'-32+128
        defb    'N','C'-32+128
        defb    'C'-32+128
        defb    'N','V'-32+128
        defb    'V'-32+128
        defb    'P'-32+128
        defb    'M'-32+128
ocx     pop     bc
        rst     out_str_ind_p1
        ret

out_reg
        add     a,2
        and     7
        jr      z,ishl
        cp      6
        jr      c,isabcde
        ld      a,'H'-'A'+1
        jr      z,isabcde
        ld      a,'L'-'A'+1
isabcde add     a,'A'-1
        jr      rg0
ishl    ld      a,(isixiy)
        call    rgx
        defb    '(HL',')'-32+128
        defb    '(I','X'-32+128
        defb    '(I','Y'-32+128
rgx     pop     bc
        push    af
        rst     out_str_ind_p1
        pop     af
        or      a
        ret     z
isprefixed equ  $+1
iyofs   ld      a,0
        or      a
        ld      a,(hl)
        jr      z,notpfx
        dec     hl
        dec     hl
        ld      a,(hl)
        inc     hl
notpfx  inc     hl
        ld      b,a
        rlca
        ld      a,'+'
        jr      nc,ofsplus
        ld      a,b
        neg
        ld      b,a
        ld      a,'-'
ofsplus ld      (de),a
        inc     de              
        call    hex_b
        ld      a,')'
rg0     ld      (de),a
        inc     de
        xor     a
        ld      (de),a
        ret

hex_rel
        ld      a,(hl)
        inc     hl
        ld      b,0
        cp      $80
        jr      c,rel0
        dec     b
rel0    add     a,l
        ld      c,a
        ld      a,b
        adc     a,h
        ld      b,a
        jr      hex_bc

hexw_at_hl
        ld      c,(hl)
        inc     hl
        ld      b,(hl)
        inc     hl
hex_bc
        call    hex_b
        ld      b,c
        jr      hb0
hexb_at_hl
        ld      b,(hl)
        inc     hl
hex_b
        ld      a,'$'
        ld      (de),a
        inc     de
hb0     ld      a,b
        rrca
        rrca
        rrca
        rrca
        call    hb1
        ld      a,b
hb1     and     $0f
        cp      10
        jr      c,hb2
        add     'A'-'9'-1
hb2     add     '0'
        ld      (de),a
        inc     de
        xor     a
        ld      (de),a
        ret   
