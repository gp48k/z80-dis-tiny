z80dis:
        xor     a
        ld      (isixiy),a
        ld      a,(hl)
        inc     hl
        jr      disv

rst8:
rrca3
        ld      a,c
        rrca
        rrca
        rrca
        and     7
        ret
        nop

rst10:
rrca3rra
        rst     rrca3
        rra
        ret

disv    ld      c,a
        cp      $40
        jr      disw

rst18:
out_str_ind_hi
        rst     rrca3
        jr      out_str_ind

disw    jp      c,grp_00
        jr      disx

rst20:
out_str_ind
        jr      out_str_ind_p1-1

disx    cp      $80
        jr      disy
        nop

        pop     bc
rst28:
out_str_ind_p1
        inc     a
        jr      osi2
osi0    push    af
osi1    ld      a,(bc)
        inc     bc
        jr      osiz

rst30:
out_str_arg_hi
        rst     rrca3
        jr      out_str_arg

disy    jp      c,grp_40
        jr      disZ

rst38:
out_str
out_str_arg
        ld      (otsarg),a
ots0    pop     bc
        ld      a,(bc)
        inc     bc
        push    bc
ots1    push    af
        and     $3f
        add     a,31
        ld      bc,ots2
        push    bc
        ld      (de),a
        sub     a,'3'
        ld      b,a
otsarg  equ     $+1
        ld      a,0
        jp      z,out_reg       ; 3
        dec     b
        jp      z,hexb_at_hl    ; 4
        dec     b
        jp      z,hexw_at_hl    ; 5
        dec     b
        jp      z,out_hlixiy    ; 6
        dec     b
        jp      z,out_rp0       ; 7
        dec     b
        jp      z,out_rp        ; 8
        dec     b
        jp      z,out_cond      ; 9
        dec     b
        jp      z,hexrel_at_hl  ; :
        dec     b
        jp      z,hex_a         ; ;
        pop     bc
        inc     de
ots2    pop     af
        rlca
        jr      c,ots3
        rlca
        jr      nc,ots0
        ld      a,' '-31
        jr      ots1
ots3    rlca
        ret     c
ots4    pop     bc
        xor     a
        ld      (de),a
        ret

osiz    cp      128 ; done if list terminator
        jr      z,ots4
        jr      c,osi1
        pop     af
osi2    dec     a
        jr      nz,osi0

        ld      a,(bc)
        cp      128 ; done if list terminator
        jr      z,ots4+1

        jr      ots0+1

disz    cp      $c0
        jp      c,grp_80

grp_c0
        and     7
        ld      b,a
gc00    jr      nz,gc01
isretc
        rst     out_str_arg_hi
        defb    'R'-31,'E'-31,'T'-31+64,'9'-31+128

gc01    djnz    gc02
        rst     rrca3rra
        jr      c,gc010
ispop
        rst     out_str_arg
        defb    'P'-31,'O'-31,'P'-31+64,'8'-31+128

gc010   rst     out_str_ind
        defb    'R'-31,'E'-31,'T'-31+128
        defb    'E'-31,'X'-31,'X'-31+128
        defb    'J'-31,'P'-31+64,'('-31,'6'-31,')'-31+128
        defb    'L'-31,'D'-31+64,'S'-31,'P'-31,','-31,'6'-31+128

gc02    djnz    gc03
isjpc
        rst     out_str_arg_hi
        defb    'J'-31,'P'-31+64,'9'-31,','-31,'5'-31+128

gc03    djnz    gc04
        rst     rrca3
        cp      1
        jp      z,grp_cb        ;CB
        rst     out_str_ind
        defb    'J'-31,'P'-31+64,'5'-31+128
        defb    128+1
        defb    'O'-31,'U'-31,'T'-31+64,'('-31,'4'-31,')'-31,','-31,'A'-31+128
        defb    'I'-31,'N'-31+64,'A'-31,','-31,'('-31,'4'-31,')'-31+128
        defb    'E'-31,'X'-31+64,'('-31,'S'-31,'P'-31,')'-31,','-31,'6'-31+128
        defb    'E'-31,'X'-31+64,'D'-31,'E'-31,','-31,'H'-31,'L'-31+128
        defb    'D'-31,'I'-31+128
        defb    'E'-31,'I'-31+128

gc04    djnz    gc05
iscallc
        rst     out_str_arg_hi
        defb    'C'-31,'A'-31,'L'-31,'L'-31+64,'9'-31,','-31,'5'-31+128

gc05    djnz    gc06
        rst     rrca3rra
        jr      c,gc05x
ispush
        rst     out_str_arg
        defb    'P'-31,'U'-31,'S'-31,'H'-31+64,'8'-31+128

gc05x   or      a
        ld      b,a
        jr      nz,gc051
gc050
iscall
        rst     out_str_arg
        defb    'C'-31,'A'-31,'L'-31,'L'-31+64,'5'-31+128

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

gc06
        dec     b
isalun
        jr      z,grp_80
gc07
isrst
        ld      a,c
        and     $38
        rst     out_str_arg
        defb    'R'-31,'S'-31,'T'-31+64,';'-31+128

grp_80        
        push    af
        rst     rrca3
        call    isalux
        defb    'A'-31,'D'-31,'D'-31+64,'A'-31,','-31+128
        defb    'A'-31,'D'-31,'C'-31+64,'A'-31,','-31+128
        defb    'S'-31,'U'-31,'B'-31,' '-31+128
        defb    'S'-31,'B'-31,'C'-31+64,'A'-31,','-31+128
        defb    'A'-31,'N'-31,'D'-31,' '-31+128
        defb    'X'-31,'O'-31,'R'-31,' '-31+128
        defb    'O'-31,'R'-31,' '-31+128
        defb    'C'-31,'P'-31,' '-31+128

grp_40
        cp      $76
        jr      nz,isld
ishalt
        rst     out_str
        defb    'H'-31,'A'-31,'L'-31,'T'-31+128
isld
        push    af
        rst     out_str_arg_hi
        defb    'L'-31,'D'-31+64,'3'-31,','-31+64+128
        pop     af
        rst     out_str_arg
        defb    '3'-31+128
        
grp_00
        and     7
        ld      b,a
g000    jr      nz,g001
        rst     rrca3
        cp      4
        jr      nc,g0004
        rst     out_str_ind
        defb    'N'-31,'O'-31,'P'-31+128
        defb    'E'-31,'X'-31+64,'A'-31,'F'-31,','-31,'A'-31,'F'-31,''''-31+128
        defb    'D'-31,'J'-31,'N'-31,'Z'-31+64,':'-31+128
        defb    'J'-31,'R'-31+64,':'-31+128

g0004
isjrc
        and     3
        rst     out_str_arg
        defb    'J'-31,'R'-31+64,'9'-31,','-31,':'-31+128

g001    djnz    g002
        rst     rrca3rra
        jr      c,isaddw
isldw
        rst     out_str_arg
        defb    'L'-31,'D'-31+64,'7'-31,','-31,'5'-31+128
isaddw
        rst     out_str_arg
        defb    'A'-31,'D'-31,'D'-31+64,'6'-31,','-31,'7'-31+128

g002    djnz    g003
        rst     rrca3
        cp      4
        jr      nc,g0022
        rrca
        jr      c,g0021
        rst     out_str_arg
        defb    'L'-31,'D'-31+64,'('-31,'7'-31,')'-31,','-31,'A'-31+128
g0021   rst     out_str_arg
        defb    'L'-31,'D'-31+64,'A'-31,','-31,'('-31,'7'-31,')'-31+128
g0022   and     3
        rst     out_str_ind
        defb    'L'-31,'D'-31+64,'('-31,'5'-31,')'-31,','-31,'6'-31+128
        defb    'L'-31,'D'-31+64,'6'-31,','-31,'('-31,'5'-31,')'-31+128
        defb    'L'-31,'D'-31+64,'('-31,'5'-31,')'-31,','-31,'A'-31+128
        defb    'L'-31,'D'-31+64,'A'-31,','-31,'('-31,'5'-31,')'-31+128

g003    djnz    g004
isincdecw
        rst     rrca3rra
        jr      c,isdecw
isincw
        rst     out_str_arg
        defb    'I'-31,'N'-31,'C'-31+64,'7'-31+128
isdecw
        rst     out_str_arg
        defb    'D'-31,'E'-31,'C'-31+64,'7'-31+128

g004    djnz    g005
isinc
        rst     out_str_arg_hi
        defb    'I'-31,'N'-31,'C'-31+64,'3'-31+128

g005    djnz    g006
isdec
        rst     out_str_arg_hi
        defb    'D'-31,'E'-31,'C'-31+64,'3'-31+128

g006    djnz    g007
isldn
        rst     out_str_arg_hi
        defb    'L'-31,'D'-31+64,'3'-31,','-31,'4'-31+128

g007    rst     out_str_ind_hi
        defb    'R'-31,'L'-31,'C'-31,'A'-31+128
        defb    'R'-31,'R'-31,'C'-31,'A'-31+128
        defb    'R'-31,'L'-31,'A'-31+128
        defb    'R'-31,'R'-31,'A'-31+128
        defb    'D'-31,'A'-31,'A'-31+128
        defb    'C'-31,'P'-31,'L'-31+128
        defb    'S'-31,'C'-31,'F'-31+128
        defb    'C'-31,'C'-31,'F'-31+128

;===============================

grp_cb
        ld      a,(isixiy)
        or      a
        jr      z,grp_cbx
        inc     hl
        ld      a,(hl)
        push    hl
        dec     hl
        call    grp_cbx+2
        pop     hl
        inc     hl
        ret

grp_cbx
        ld      a,(hl)
        inc     hl
        ld      c,a
        cp      $40
        push    af
        jr      c,grp_cb00
grp_cbc0
grp_cb80
grp_cb40
        rlca
        rlca
        and     3
        dec     a
        call    bitx
        defb    'B'-31,'I'-31,'T'-31,' '-31+128
        defb    'R'-31,'E'-31,'S'-31,' '-31+128
        defb    'S'-31,'E'-31,'T'-31,' '-31+128
bitx    pop     bc
        rst     out_str_ind_p1
        pop     af
        push    af
        ld      c,a
        rst     rrca3
        call    hb2
        pop     af
        rst     out_str_arg
        defb    ','-31,'3'-31+128

grp_cb00
        rst     rrca3
        call    iscbalu
        defb    'R'-31,'L'-31,'C'-31,' '-31+128
        defb    'R'-31,'R'-31,'C'-31,' '-31+128
        defb    'R'-31,'L'-31,' '-31+128
        defb    'R'-31,'R'-31,' '-31+128
        defb    'S'-31,'L'-31,'A'-31,' '-31+128
        defb    'S'-31,'R'-31,'A'-31,' '-31+128
        defb    128+1
        defb    'S'-31,'R'-31,'L'-31,' '-31+128
iscbalu
isalux
        pop     bc
        rst     out_str_ind_p1
        pop     af
        jp      c,out_reg
        rst     out_str
        defb    '4'-31+128

grp_ed
        ld      a,(hl)
        inc     hl
        ld      c,a
        cp      $40
        jr      c,grp_ed00
        cp      $80
        jr      c,grp_ed40
        cp      $c0
        jr      nc,grp_edc0
grp_ed80
        xor     $a0             ;10x..y.. xit if x=0 or y=1
        ld      c,a
        and     $24
        jr      nz,xit80
        ld      a,c
        and     $03
        add     a,c
        rrca
        rst     out_str_ind
        defb    'L'-31,'D'-31,'I'-31+128     
        defb    'C'-31,'P'-31,'I'-31+128     
        defb    'I'-31,'N'-31,'I'-31+128     
        defb    'O'-31,'U'-31,'T'-31,'I'-31+128     
        defb    'L'-31,'D'-31,'D'-31+128     
        defb    'C'-31,'P'-31,'D'-31+128     
        defb    'I'-31,'N'-31,'D'-31+128     
        defb    'O'-31,'U'-31,'T'-31,'D'-31+128     
        defb    'L'-31,'D'-31,'I'-31,'R'-31+128     
        defb    'C'-31,'P'-31,'I'-31,'R'-31+128     
        defb    'I'-31,'N'-31,'I'-31,'R'-31+128     
        defb    'O'-31,'T'-31,'I'-31,'R'-31+128
        defb    'L'-31,'D'-31,'D'-31,'R'-31+128     
        defb    'C'-31,'P'-31,'D'-31,'R'-31+128     
        defb    'I'-31,'N'-31,'D'-31,'R'-31+128
        defb    'O'-31,'T'-31,'D'-31,'R'-31+128     

grp_edc0
xit80
grp_ed00
        xor     a
        ld      (de),a
        ret

grp_ed40
        and     7
        ld      b,a
        jr      nz,ged401
ged400
isinpc
        rst     out_str_arg_hi
        defb    'I'-31,'N'-31+64,'3'-31,','-31,'('-31,'C'-31,')'-31+128

ged401  djnz    ged402
isoutc
        rst     out_str_arg_hi
        defb    'O'-31,'U'-31,'T'-31+64,'('-31,'C'-31,')'-31,','-31,'3'-31+128

ged402  djnz    ged403
        rst     rrca3rra
        jr      c,isadcw
issbcw
        rst     out_str_arg
        defb    'S'-31,'B'-31,'C'-31+64,'6'-31,','-31,'7'-31+128
isadcw
        rst     out_str_arg
        defb    'A'-31,'D'-31,'C'-31+64,'6'-31,','-31,'7'-31+128

ged403  djnz    ged404
        rst     rrca3rra
        jr      c,isldrpatnn
isldatnnrp
        rst     out_str_arg
        defb    'L'-31,'D'-31+64,'('-31,'5'-31,')'-31,','-31,'7'-31+128
isldrpatnn
        rst     out_str_arg
        defb    'L'-31,'D'-31+64,'7'-31,','-31,'('-31,'5'-31,')'-31+128

ged404  djnz    ged405
        ld      a,c
        and     $38
;        jr      nz,xited
isneg
        rst     out_str_ind
        defb    'N'-31,'E'-31,'G'-31+128
        defb    128 ; list terminator

ged405  djnz    ged406
        rst     out_str_ind_hi
        defb    'R'-31,'E'-31,'T'-31,'N'-31+128
        defb    'R'-31,'E'-31,'T'-31,'I'-31+128
        defb    128 ; list terminator

ged406  djnz    ged407
        rst     out_str_ind_hi
        defb    'I'-31,'M'-31+64,'0'-31+128
        defb    128+1
        defb    'I'-31,'M'-31+64,'1'-31+128
        defb    'I'-31,'M'-31+64,'2'-31+128
        defb    128 ; list terminator

ged407  rst     out_str_ind_hi
        defb    'L'-31,'D'-31+64,'I'-31,','-31,'A'-31+128
        defb    'L'-31,'D'-31+64,'R'-31,','-31,'A'-31+128
        defb    'L'-31,'D'-31+64,'A'-31,','-31,'I'-31+128
        defb    'L'-31,'D'-31+64,'A'-31,','-31,'R'-31+128
        defb    'R'-31,'R'-31,'D'-31+128
        defb    'R'-31,'L'-31,'D'-31+128
        defb    128 ; list terminator

;===============================

out_hlixiy
        ld      a,(isixiy)
        rst     out_str_ind
        defb    'H'-31,'L'-31+128
        defb    'I'-31,'X'-31+128
        defb    'I'-31,'Y'-31+128

out_rp0
        inc     a
        and     3
        jr      nz,rp0
        rst     out_str
        defb    'S'-31,'P'-31+128

out_rp
        inc     a
        and     3
rp0     cp      3
        jr      nz,nothlixiy
isixiy  equ     $+1
        add     a,0
nothlixiy
        rst     out_str_ind
        defb    'A'-31,'F'-31+128
        defb    'B'-31,'C'-31+128
        defb    'D'-31,'E'-31+128
        defb    'H'-31,'L'-31+128
        defb    'I'-31,'X'-31+128
        defb    'I'-31,'Y'-31+128
        
out_cond
        rst     out_str_ind
        defb    'N'-31,'Z'-31+128
        defb    'Z'-31+128
        defb    'N'-31,'C'-31+128
        defb    'C'-31+128
        defb    'N'-31,'V'-31+128
        defb    'V'-31+128
        defb    'P'-31+128
        defb    'M'-31+128

out_reg
        add     a,2
        and     7
        jr      z,ishl
        dec     a
        rst     out_str_ind
        defb    'A'-31+128,'B'-31+128,'C'-31+128,'D'-31+128,'E'-31+128,'H'-31+128,'L'-31+128
ishl    ld      a,(isixiy)
        call    rgx
        defb    '('-31,'H'-31,'L'-31,')'-31+128
        defb    '('-31,'I'-31,'X'-31+128
        defb    '('-31,'I'-31,'Y'-31+128
rgx     pop     bc
        push    af
        rst     out_str_ind_p1
        pop     af
        or      a
        ret     z
        ld      a,(hl)
        inc     hl
        cp      $80
        jr      nc,ofsminus
        rst     out_str_arg
        defb    '+'-31,';'-31,')'-31+128
ofsminus
        neg
        rst     out_str_arg
        defb    '-'-31,';'-31,')'-31+128

hexrel_at_hl
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
        ld      a,(hl)
        inc     hl
hex_a
        ld      b,a
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
