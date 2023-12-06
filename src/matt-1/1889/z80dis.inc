z80dis: xor     a
        ld      (isixiy),a
        ld      a,(hl)
        inc     hl
        cp      $40
        jp      c,grp_00
        cp      $80
        jp      c,grp_40
        cp      $c0
        jp      c,grp_80

grp_c0
        push    af
        and     7
        ld      b,a
gc00    jr      nz,gc01
isretc
        call    out_str
        defb    'RET ',1
        pop     af
        jp      out_cond_hi

gc01    djnz    gc02
        pop     af
        rrca
        rrca
        rrca
        rrca
        jp      c,gc010
ispop   
        push    af
        call    out_str
        defb    'POP ',1
        jp      push0
gc010   and     3
        ld      b,a
        jr      nz,gc011
        call    out_str
        defb    'RET',0
gc011   djnz    gc012
        call    out_str
        defb    'EXX',0
gc012   djnz    gc013
        call    out_str
        defb    'JP (',1
        call    out_hlixiy
        call    out_str
        defb    ')',0
gc013   call    out_str
        defb    'LD SP,',1
        jp      out_hlixiy

gc02    djnz    gc03
isjpc
        call    out_str
        defb    'JP ',1
        jr      callc0

gc03    djnz    gc04
        pop     af
        rrca
        rrca
        rrca
        and     7
        ld      b,a
gc030   jr      nz,gc031
isjp
        scf
        push    af
        jp      isjpc
gc031   djnz    gc032
        jp      grp_cb          ;CB
gc032   djnz    gc033
isout
        call    out_str
        defb    'OUT (',1
        call    hexb_at_hl
        call    out_str
        defb    '),A',0
gc033   djnz    gc034
isinp
        call    out_str
        defb    'IN A,(',1
        call    hexb_at_hl
        call    out_str
        defb    ')',0
gc034   djnz    gc035
        call    out_str
        defb    'EX (SP),',1
        jp      out_hlixiy
gc035   djnz    gc036
        call    out_str
        defb    'EX DE,HL',0
gc036   djnz    gc037
        call    out_str
        defb    'DI',0
gc037
        call    out_str
        defb    'EI',0

gc04    djnz    gc05
iscallc
        call    out_str
        defb    'CALL ',1
callc0  pop     af
        jr      c,callc1
        call    out_cond_hi
        ld      a,','
        ld      (de),a
        inc     de
callc1  jp      hexw_at_hl

gc05    djnz    gc06
        pop     af
        rrca
        rrca
        rrca
        rrca
        jr      c,gc05x
ispush
        push    af
        call    out_str
        defb    'PUSH ',1
push0   pop     af
        jp      out_rp
gc05x   and     3
        ld      b,a
        jr      nz,gc051
gc050   scf
        push    af
        jp      iscallc
gc051   djnz    gc052
                                ;DD
        ld      a,1
        jp      z80dis+1
gc052   djnz    gc053
        jp      grp_ed          ;ED
gc053
                                ;FD
        ld      a,2
        jp      z80dis+1
gc06    djnz    gc07
isalun
        pop     af
        jp      grp_80

gc07
isrst
        call    out_str
        defb    'RST ',1
        pop     af
        and     $38
        ld      b,a
        jp      hex_b

grp_80        
        push    af
        rrca
        rrca
        rrca
        and     7
        ld      b,a
        jr      nz,g801
g800    call    isalu
        db      'ADD A,',0

g801    djnz    g802
        call    isalu
        db      'ADC A,',0

g802    djnz    g803
        call    isalu
        db      'SUB ',0

g803    djnz    g804
        call    isalu
        db      'SBC A,',0

g804    djnz    g805
        call    isalu
        db      'AND ',0

g805    djnz    g806
        call    isalu
        db      'XOR ',0

g806    djnz    g807
        call    isalu
        db      'OR ',0

g807    call    isalu
        db      'CP ',0
isalu
        pop     bc
        call    out_str+1
        pop     af
        jp      c,out_reg
        jp      hexb_at_hl

grp_40
        cp      $76
        jr      nz,isld
        call    out_str
        db      'HALT',0
isld
        scf
        push    af
        call    out_str
        db      'LD ',1
        pop     af
        push    af
        call    out_reg_hi
        ld      a,','
        ld      (de),a
        inc     de
        pop     af
        jp      c,out_reg
        jp      hexb_at_hl
        
grp_00
        push    af
        and     7
        ld      b,a
g000    jr      nz,g001
        pop     af
        rrca
        rrca
        rrca
        and     7
        ld      b,a
        jr      nz,g0001
g0000
isnop
        call    out_str
        defb    'NOP',0
g0001   djnz    g0002
isexafaf
        call    out_str
        defb    'EX AF,AF''',0
g0002   djnz    g0003
isdjnz
        call    out_str
        defb    'DJNZ ',1
        jp      hex_rel
g0003   djnz    g0004
isjr    scf
g0004
idjrc   push    af
        call    out_str
        defb    'JR ',1
        pop     af
        jr      c,jrc0
        and     3
        call    out_cond
        ld      a,','
        ld      (de),a
        inc     de
jrc0    jp      hex_rel

g001    djnz    g002
        pop     af
        rrca
        rrca
        rrca
        rrca
        jr      c,isaddw
isldw
        push    af
        call    out_str
        defb    'LD ',1
        pop     af
        call    out_rp0
        ld      a,','
        ld      (de),a
        inc     de
        jp      hexw_at_hl
isaddw
        push    af
        call    out_str
        defb    'ADD ',1
        call    out_hlixiy
        ld      a,','
        ld      (de),a
        inc     de
        pop     af
        jp      out_rp0

g003x   jp      g003
g002    djnz    g003x
        pop     af
        rrca
        rrca
        rrca
        and     7
        cp      4
        jr      nc,g0022
        srl     a
        push    af
        jr      c,g0021
        call    out_str
        defb    'LD (',1
        pop     af
        call    out_rp
        call    out_str
        defb    '),A',0
g0021   call    out_str
        defb    'LD A,(',1
        pop     af
        call    out_rp
        call    out_str
        defb    ')',0
g0022   cp      6
        jr      nc,g0024
        srl     a
        jr      c,g0023
        call    out_str
        defb    'LD (',1
        call    hexw_at_hl
        call    out_str
        defb    '),',1
        jp      out_hlixiy
g0023   call    out_str
        defb    'LD ',1
        call    out_hlixiy
        call    out_str
        defb    ',(',1
        call    hexw_at_hl
        call    out_str
        defb    ')',0
g0024   srl     a
        jr      c,g0025
        call    out_str
        defb    'LD (',1
        call    hexw_at_hl
        call    out_str
        defb    '),A',0
g0025   call    out_str
        defb    'LD A,(',1
        call    hexw_at_hl
        call    out_str
        defb    ')',0

g003    djnz    g004
isincdecw
        pop     af
        rrca
        rrca
        rrca
        rrca
        jr      c,ldw0
        call    ldw1
        db      'INC ',0
ldw0    call    ldw1
        db      'DEC ',0
ldw1    pop     bc
        push    af
        call    out_str+1
        pop     af
        jp      out_rp0

g004    djnz    g005
isinc
        call    out_str
        defb    'INC ',1
        jr      dec0

g005    djnz    g006
isdec
        call    out_str
        defb    'DEC ',1
dec0    pop     af
        jp      out_reg_hi

g006    djnz    g007
isldn
        pop     af
        or      a
        jp      isld+1

g007    pop     af
        rrca
        rrca
        rrca
        and     7
        ld      b,a
        jr      nz,g0071
g0070   call    out_str
        defb    'RLCA',0
g0071   djnz    g0072
        call    out_str
        defb    'RRCA',0
g0072   djnz    g0073
        call    out_str
        defb    'RLA',0
g0073   djnz    g0074
        call    out_str
        defb    'RRA',0
g0074   djnz    g0075
        call    out_str
        defb    'DAA',0
g0075   djnz    g0076
        call    out_str
        defb    'CPL',0
g0076   djnz    g0077
        call    out_str
        defb    'SCF',0
g0077   call    out_str
        defb    'CCF',0

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
        jp      c,grp_cb00
        cp      $80
        jp      c,grp_cb40
        cp      $c0
        jp      c,grp_cb80
grp_cbc0
        push    af
        call    out_str
        db      'SET ',1
        jr      bit0

grp_cb80
        push    af
        call    out_str
        db      'RES ',1
        jr      bit0

grp_cb40
        push    af
        call    out_str
        db      'BIT ',1
bit0    pop     af
        push    af
        rrca
        rrca
        rrca
        and     7
        add     a,'0'
        ld      (de),a
        inc     de
        ld      a,','
        ld      (de),a
        inc     de
        pop     af
        jp      out_reg

grp_cb00
        push    af
        rrca
        rrca
        rrca
        and     7
        ld      b,a
        jr      nz,gcb001
gcb000  call    iscbalu
        db      'RLC ',0

gcb001  djnz    gcb002
        call    iscbalu
        db      'RRC ',0

gcb002  djnz    gcb003
        call    iscbalu
        db      'RL ',0

gcb003  djnz    gcb004
        call    iscbalu
        db      'RR ',0

gcb004  djnz    gcb005
        call    iscbalu
        db      'SLA ',0

gcb005  djnz    gcb006
        call    iscbalu
        db      'SRA ',0

gcb006  djnz    gcb007
        pop     af
        xor     a
        ld      (de),a
        ret

gcb007  call    iscbalu
        db      'SRL ',0
iscbalu
        pop     bc
        call    out_str+1
        pop     af
        jp      c,out_reg
        jp      hexb_at_hl

grp_ed
        ld      a,(hl)
        inc     hl
        cp      $40
        jp      c,grp_ed00
        cp      $80
        jp      c,grp_ed40
        cp      $c0
        jp      c,grp_ed80
grp_edc0
        xor     a
        ld      (de),a
        ret

grp_ed80
        push    af
        and     7
        ld      b,a
        pop     af
        rrca
        rrca
        rrca
        and     7
        sub     4
        jp      c,xitc0
        inc     a
        inc     b
        djnz    gedc01
gedc00
        ld      b,a
        djnz    gedc001
gedc000
        call    out_str
        defb    'LDI',0     
gedc001 djnz    gedc002     
        call    out_str
        defb    'LDD',0     
gedc002 djnz    gedc003
        call    out_str
        defb    'LDIR',0     
gedc003 call    out_str
        defb    'LDDR',0     
             
gedc01  djnz    gedc02
        ld      b,a
        djnz    gedc011
gedc010
        call    out_str
        defb    'CPI',0     
gedc011 djnz    gedc012     
        call    out_str
        defb    'CPD',0     
gedc012 djnz    gedc013
        call    out_str
        defb    'CPIR',0     
gedc013 call    out_str
        defb    'CPDR',0     

gedc02  djnz    gedc03
        ld      b,a
        djnz    gedc021
gedc020
        call    out_str
        defb    'INI',0     
gedc021 djnz    gedc022     
        call    out_str
        defb    'IND',0     
gedc022 djnz    gedc023
        call    out_str
        defb    'INIR',0     
gedc023 call    out_str
        defb    'INDR',0
             
gedc03  djnz    gedc04
        ld      b,a
        djnz    gedc031
gedc030
        call    out_str
        defb    'OUTI',0     
gedc031 djnz    gedc032     
        call    out_str
        defb    'OUTD',0     
gedc032 djnz    gedc033
        call    out_str
        defb    'OTIR',0     
gedc033 call    out_str
        defb    'OTDR',0
             
gedc04
xitc0
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
        call    out_str
        db      'IN ',1
        pop     af
        call    out_reg_hi
        call    out_str
        db      ',(C)',0

ged401  djnz    ged402
isoutc
        call    out_str
        db      'OUT (C),',1
        pop     af
        jp      out_reg_hi

ged402  djnz    ged403
        pop     af
        rrca
        rrca
        rrca
        rrca
        jr      c,isadchl
issbchl
        call    adchlx
        defb    'SBC ',0
isadchl
        call    adchlx
        defb    'ADC ',0
adchlx  pop     bc
        push    af
        call    out_str+1
        call    out_hlixiy
        ld      a,','
        ld      (de),a
        inc     de
        pop     af
        jp      out_rp0

ged403  djnz    ged404
        pop     af
        rrca
        rrca
        rrca
        rrca
        push    af
        jr      c,isldrpatnn
isldatnnrp
        call    out_str
        defb    'LD (',1
        call    hexw_at_hl
        call    out_str
        defb    '),',1
        pop     af
        jp      out_rp0
isldrpatnn
        call    out_str
        defb    'LD ',1
        pop     af
        call    out_rp0
        call    out_str
        defb    ',(',1
        call    hexw_at_hl
        call    out_str
        defb    ')',0

ged404  djnz    ged405
        pop     af
        and     $38
        jp      nz,xited
isneg
        call    out_str
        defb    'NEG',0

ged405  djnz    ged406
        pop     af
        and     $38
        jr      nz,ged4051
isretn
        call    out_str
        defb    'RETN',0
ged4051 sub     8
        jr      nz,xited
isreti
        call    out_str
        defb    'RETI',0

ged406  djnz    ged407
        pop     af
        and     $38
        jr      nz,ged4061
        call    out_str
        defb    'IM 0',0
ged4061 sub     16
        jr      nz,ged4063
        call    out_str
        defb    'IM 1',0
        sub     8
ged4063 jr      z,xited
        call    out_str
        defb    'IM 2',0

ged407  pop     af
        rrca
        rrca
        rrca
        and     7
        ld      b,a
        jr      nz,ged4071
ged4070
        call    out_str
        defb    'LD I,A',0
ged4071 djnz    ged4072
        call    out_str
        defb    'LD R,A',0
ged4072 djnz    ged4073
        call    out_str
        defb    'LD A,I',0
ged4073 djnz    ged4074
        call    out_str
        defb    'LD A,R',0
ged4074 djnz    ged4075
        call    out_str
        defb    'RRD',0
ged4075 djnz    ged4076
        call    out_str
        defb    'RLD',0
ged4076 jr      xited

grp_ed00
xited
        xor     a
        ld      (de),a
        ret

;===============================

out_hlixiy
        ld      a,(isixiy)
        ld      b,a
        djnz    notixrg
        call    out_str
        defb    'IX',0
notixrg djnz    notiyrg
        call    out_str
        defb    'IY',0
notiyrg call    out_str
        defb    'HL',0

out_rp0
        and     3
        cp      3
        jr      nz,out_rp
        call    rpx
        defb    'SP',0
out_rp
        and     3
        ld      b,a
        jr      nz,rp1
rp0     call    rpx
        defb    'BC',0
rp1     djnz    rp2
        call    rpx
        defb    'DE',0
rp2     djnz    rp3
        ld      a,(isixiy)
        ld      b,a
        djnz    notixrp
        call    rpx
        defb    'IX',0
notixrp djnz    notiyrp
        call    rpx
        defb    'IY',0
notiyrp call    rpx
        defb    'HL',0
rp3     call    rpx
        defb    'AF',0
rpx     pop     bc
        jp      out_str+1
        
out_cond_hi
        rrca
        rrca
        rrca
out_cond
        and     7
        ld      b,a
        jr      nz,oc1
oc0     call    ocx
        defb    'NZ',0
oc1     djnz    oc2
        call    ocx
        defb    'Z',0
oc2     djnz    oc3
        call    ocx
        defb    'NC',0
oc3     djnz    oc4
        call    ocx
        defb    'C',0
oc4     djnz    oc5
        call    ocx
        defb    'NV',0
oc5     djnz    oc6
        call    ocx
        defb    'V',0
oc6     djnz    oc7
        call    ocx
        defb    'P',0
oc7     call    ocx
        defb    'M',0
ocx     pop     bc
        jp      out_str+1

out_reg_hi
        rrca
        rrca
        rrca
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
        ld      (rg0),a
        call    out_str
rg0     defb    'A',0
isixiy  equ     ishl+1
isprefixed equ  iyofs+1
ishl    ld      b,0
        djnz    notix
        call    out_str
        defb    '(IX',1
        jr      iyofs
notix   djnz    notiy    
        call    out_str
        defb    '(IY',1
iyofs   ld      a,0
        or      a
        ld      a,(hl)
        jr      z,notpfx
        dec     hl
        dec     hl
        ld      a,(hl)
        inc     hl
notpfx  inc     hl
        cp      $80
        jr      c,ofsplus
        neg
        ld      b,a
        ld      a,'-'
        jr      ofsmrg
ofsplus ld      b,a
        ld      a,'+'
ofsmrg  ld      (de),a
        inc     de              
        call    hex_b
        call    out_str
        defb    ')',0
notiy   call    out_str
        defb    '(HL)',0

hex_rel
        ld      c,(hl)
        inc     hl
        ld      b,0
        bit     7,c
        jr      z,djnz0
        dec     b
djnz0   push    hl
        add     hl,bc
        ld      b,h
        ld      c,l
        pop     hl
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

out_str
        pop     bc
        dec     de
pts0    ld      a,(bc)
        inc     bc
        inc     de
        ld      (de),a
        or      a
        ret     z
        dec     a
        jr      nz,pts0
        push    bc
        ret
