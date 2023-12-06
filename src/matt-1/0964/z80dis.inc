z80dis:
        xor     a
        ld      (isixiy),a
        ld      a,(hl)
        inc     hl
        ld      c,a
        sub     $40
        jp      c,grp_00
        sub     $40
        jr      disx

rst10:
rrca3
        ld      a,c
        rrca
        rrca
        rrca
        and     7
        ret
        nop

rst18:
rrca3rra
        rst     rrca3
        rra
        ret

disx    jp      c,grp_40
        jr      disy

rst20:
out_str_ind_hi
        rst     rrca3
        jr      out_str_ind

disy
        sub     $40
        jp      disz

rst28:
out_str_ind
        pop     bc
        inc     a
        jr      osi2
osi0    push    af
osi1    ld      a,(bc)
        jr      osiy

rst30:
out_str_arg_hi
        rst     rrca3
        jr      out_str_arg
osiy    inc     bc
        cp      '@'-32+128 ; done if list terminator
        jr      osiz

rst38:
out_str
out_str_arg
        ld      (otsarg),a
ots0    pop     bc
ots0_p1 ld      a,(bc)
        inc     bc
        push    bc
        push    af
        and     $3f
        add     a,32
        ld      bc,ots1
        push    bc
        ld      (de),a
        sub     a,'3'
        ld      b,a
otsarg  equ     $+1
        ld      a,0
        jp      z,out_reg       ; 3
        dec     b
        jr      z,hexb_at_hl    ; 4
        dec     b
        jr      z,hexw_at_hl    ; 5
        dec     b
        jr      z,out_hlixiy    ; 6
        dec     b
        jr      z,out_rp0       ; 7
        dec     b
        jr      z,out_rp        ; 8
        dec     b
        jr      z,hexrel_at_hl  ; 9
        dec     b
        jr      z,hex_a         ; :
        djnz    otsx
out_cond                        ; ;
        rst     out_str_ind
        defb    'N'-32,'Z'-32+128
        defb    'Z'-32+128
        defb    'N'-32,'C'-32+128
        defb    'C'-32+128
        defb    'N'-32,'V'-32+128
        defb    'V'-32+128
        defb    'P'-32+128
        defb    'M'-32+128
otsx
        pop     bc
        inc     de
ots1    pop     af
        bit     6,a
        rlca
        jr      z,ots2
        ld      a,' '
        ld      (de),a
        inc     de
ots2    jr      nc,ots0
ots3    pop     bc
        jr      ld_de_0

osiz    jr      z,ots3
        rlca
        jr      nc,osi1
        pop     af
osi2    dec     a
        jr      nz,osi0
        jr      ots0_p1

out_rp
        inc     a
rp0     inc     a
        and     3
        jr      nz,nothlixiy
out_hlixiy
isixiy  equ     $+1
        ld      a,0
        rst     out_str_ind
        defb    'H'-32,'L'-32+128
        defb    'I'-32,'X'-32+128
        defb    'I'-32,'Y'-32+128

out_rp0
        inc     a
        and     3
        jr      nz,rp0
nothlixiy
        rst     out_str_ind
        defb    'S'-32,'P'-32+128
        defb    'A'-32,'F'-32+128
        defb    'B'-32,'C'-32+128
        defb    'D'-32,'E'-32+128

hexrel_at_hl
        ld      a,(hl)
        inc     hl
        ld      b,a
        add     a,l
        ld      c,a
        sbc     a,a
        rlc     b
        ccf
        sbc     a,h
        cpl
        jr      hex_ac

hexw_at_hl
        ld      c,(hl)
        inc     hl
        ld      a,(hl)
        inc     hl
hex_ac
        call    hex_a
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
ld_de_0 xor     a
        ld      (de),a
        ret

iscbalux
isalux
        rst     rrca3
        pop     bc
        call    out_str_ind+1
        pop     af
        jr      nc,hexb_at_hl
out_reg
        add     a,2
        and     7
        jr      z,ishl
        dec     a
        rst     out_str_ind
        defb    'A'-32+128,'B'-32+128,'C'-32+128,'D'-32+128,'E'-32+128,'H'-32+128,'L'-32+128
ishl    ld      a,(isixiy)
        push    af
        call    rgx
        pop     af
        or      a
        ret     z
        ld      a,(hl)
        inc     hl
        cp      $80
        jr      nc,ofsminus
        rst     out_str_arg
        defb    '+'-32,':'-32,')'-32+128
ofsminus
        neg
        rst     out_str_arg
        defb    '-'-32,':'-32,')'-32+128

rgx     rst     out_str_ind
        defb    '('-32,'H'-32,'L'-32,')'-32+128
        defb    '('-32,'I'-32,'X'-32+128
        defb    '('-32,'I'-32,'Y'-32+128

disz    jp      c,grp_80

grp_c0
        and     7
        ld      b,a
gc00    jr      nz,gc01
isretc
        rst     out_str_arg_hi
        defb    'R'-32,'E'-32,'T'-32+64,';'-32+128

gc01    djnz    gc02
        rst     rrca3rra
        jr      c,gc010
ispop
        rst     out_str_arg
        defb    'P'-32,'O'-32,'P'-32+64,'8'-32+128

gc010   rst     out_str_ind
        defb    'R'-32,'E'-32,'T'-32+128
        defb    'E'-32,'X'-32,'X'-32+128
        defb    'J'-32,'P'-32+64,'('-32,'6'-32,')'-32+128
        defb    'L'-32,'D'-32+64,'S'-32,'P'-32,','-32,'6'-32+128

gc02    djnz    gc03
isjpc
        rst     out_str_arg_hi
        defb    'J'-32,'P'-32+64,';'-32,','-32,'5'-32+128

gc03    djnz    gc04
        rst     rrca3
        cp      1
        jr      nz,not_cb
grp_cb                          ;CB
        ld      a,(isixiy)
        or      a
        jr      z,grp_cbx
        inc     hl
        ld      a,(hl)
        push    hl
        dec     hl
        call    grp_cbx_p2
        pop     hl
        inc     hl
        ret

grp_cbx
        ld      a,(hl)
        inc     hl
grp_cbx_p2
        ld      c,a
        sub     $40
        push    af
        jr      c,grp_cb00
grp_cbc0
grp_cb80
grp_cb40
        rlca
        rlca
        and     3
        call    bitx
        pop     af
        ld      c,a
        rst     rrca3
        call    hb2
        ld      a,c
        rst     out_str_arg
        defb    ','-32,'3'-32+128

bitx    rst     out_str_ind
        defb    'B'-32,'I'-32,'T'-32+64+128
        defb    'R'-32,'E'-32,'S'-32+64+128
        defb    'S'-32,'E'-32,'T'-32+64+128

grp_cb00
        call    iscbalux
        defb    'R'-32,'L'-32,'C'-32+64+128
        defb    'R'-32,'R'-32,'C'-32+64+128
        defb    'R'-32,'L'-32,' '-32+128
        defb    'R'-32,'R'-32,' '-32+128
        defb    'S'-32,'L'-32,'A'-32+64+128
        defb    'S'-32,'R'-32,'A'-32+64+128
        defb    128
        defb    'S'-32,'R'-32,'L'-32+64+128

not_cb
        rst     out_str_ind
        defb    'J'-32,'P'-32+64,'5'-32+128
        defb    128
        defb    'O'-32,'U'-32,'T'-32+64,'('-32,'4'-32,')'-32,','-32,'A'-32+128
        defb    'I'-32,'N'-32+64,'A'-32,','-32,'('-32,'4'-32,')'-32+128
        defb    'E'-32,'X'-32+64,'('-32,'S'-32,'P'-32,')'-32,','-32,'6'-32+128
        defb    'E'-32,'X'-32+64,'D'-32,'E'-32,','-32,'H'-32,'L'-32+128
        defb    'D'-32,'I'-32+128
        defb    'E'-32,'I'-32+128

gc04    djnz    gc05
iscallc
        rst     out_str_arg_hi
        defb    'C'-32,'A'-32,'L'-32,'L'-32+64,';'-32,','-32,'5'-32+128

gc05    djnz    gc06
        rst     rrca3rra
        jr      c,gc05x
ispush
        rst     out_str_arg
        defb    'P'-32,'U'-32,'S'-32,'H'-32+64,'8'-32+128

gc05x   or      a
        ld      b,a
        jr      nz,gc051
gc050
iscall
        rst     out_str_arg
        defb    'C'-32,'A'-32,'L'-32,'L'-32+64,'5'-32+128

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
        defb    'R'-32,'S'-32,'T'-32+64,':'-32+128

grp_80        
        push    af
        call    isalux
        defb    'A'-32,'D'-32,'D'-32+64,'A'-32,','-32+128
        defb    'A'-32,'D'-32,'C'-32+64,'A'-32,','-32+128
        defb    'S'-32,'U'-32,'B'-32+64+128
        defb    'S'-32,'B'-32,'C'-32+64,'A'-32,','-32+128
        defb    'A'-32,'N'-32,'D'-32+64+128
        defb    'X'-32,'O'-32,'R'-32+64+128
        defb    'O'-32,'R'-32+64+128
        defb    'C'-32,'P'-32+64+128

grp_40
        cp      $76-$40-$40
        jr      nz,isld
ishalt
        rst     out_str
        defb    'H'-32,'A'-32,'L'-32,'T'-32+128
isld
        push    af
        call    isldx
        pop     af
        rst     out_str_arg
        defb    '3'-32+128
isldx   
        ld      c,a
        rst     out_str_arg_hi
        defb    'L'-32,'D'-32+64,'3'-32,','-32+128
        
grp_00
        and     7
        ld      b,a
g000    jr      nz,g001
        rst     rrca3
        cp      4
        jr      nc,g0004
        rst     out_str_ind
        defb    'N'-32,'O'-32,'P'-32+128
        defb    'E'-32,'X'-32+64,'A'-32,'F'-32,','-32,'A'-32,'F'-32,''''-32+128
        defb    'D'-32,'J'-32,'N'-32,'Z'-32+64,'9'-32+128
        defb    'J'-32,'R'-32+64,'9'-32+128

g0004
isjrc
        and     3
        rst     out_str_arg
        defb    'J'-32,'R'-32+64,';'-32,','-32,'9'-32+128

g001    djnz    g002
        rst     rrca3rra
        jr      c,isaddw
isldw
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'7'-32,','-32,'5'-32+128
isaddw
        rst     out_str_arg
        defb    'A'-32,'D'-32,'D'-32+64,'6'-32,','-32,'7'-32+128

g002    djnz    g003
        rst     rrca3
        cp      4
        jr      nc,g0022
        rrca
        jr      c,g0021
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'('-32,'7'-32,')'-32,','-32,'A'-32+128
g0021   rst     out_str_arg
        defb    'L'-32,'D'-32+64,'A'-32,','-32,'('-32,'7'-32,')'-32+128
g0022   and     3
        rst     out_str_ind
        defb    'L'-32,'D'-32+64,'('-32,'5'-32,')'-32,','-32,'6'-32+128
        defb    'L'-32,'D'-32+64,'6'-32,','-32,'('-32,'5'-32,')'-32+128
        defb    'L'-32,'D'-32+64,'('-32,'5'-32,')'-32,','-32,'A'-32+128
        defb    'L'-32,'D'-32+64,'A'-32,','-32,'('-32,'5'-32,')'-32+128

g003    djnz    g004
isincdecw
        rst     rrca3rra
        jr      c,isdecw
isincw
        rst     out_str_arg
        defb    'I'-32,'N'-32,'C'-32+64,'7'-32+128
isdecw
        rst     out_str_arg
        defb    'D'-32,'E'-32,'C'-32+64,'7'-32+128

g004    djnz    g005
isinc
        rst     out_str_arg_hi
        defb    'I'-32,'N'-32,'C'-32+64,'3'-32+128

g005    djnz    g006
isdec
        rst     out_str_arg_hi
        defb    'D'-32,'E'-32,'C'-32+64,'3'-32+128

g006    djnz    g007
isldn
        rst     out_str_arg_hi
        defb    'L'-32,'D'-32+64,'3'-32,','-32,'4'-32+128

g007    rst     out_str_ind_hi
        defb    'R'-32,'L'-32,'C'-32,'A'-32+128
        defb    'R'-32,'R'-32,'C'-32,'A'-32+128
        defb    'R'-32,'L'-32,'A'-32+128
        defb    'R'-32,'R'-32,'A'-32+128
        defb    'D'-32,'A'-32,'A'-32+128
        defb    'C'-32,'P'-32,'L'-32+128
        defb    'S'-32,'C'-32,'F'-32+128
        defb    'C'-32,'C'-32,'F'-32+128

;===============================

grp_ed
        ld      a,(hl)
        inc     hl
        ld      c,a
;        add     $40
        sub     $80
;        jp      c,ld_de_0       ;grp_ed00, grp_edc0
;        sub     $40
        jr      c,grp_ed40
grp_ed80
;        xor     $a0-$40-$40     ;10x..y.. xit if x=0 or y=1
        and     $1f             ;only needed if not only grp_ed80 case!
        ld      c,a
;        and     $24             ;bound to valid range 0-15
;        jr      nz,ld_de_0      ;xit80
;        ld      a,c
        and     $03
        add     a,c
        rrca
        rst     out_str_ind
        defb    'L'-32,'D'-32,'I'-32+128     
        defb    'C'-32,'P'-32,'I'-32+128     
        defb    'I'-32,'N'-32,'I'-32+128     
        defb    'O'-32,'U'-32,'T'-32,'I'-32+128     
        defb    'L'-32,'D'-32,'D'-32+128     
        defb    'C'-32,'P'-32,'D'-32+128     
        defb    'I'-32,'N'-32,'D'-32+128     
        defb    'O'-32,'U'-32,'T'-32,'D'-32+128     
        defb    'L'-32,'D'-32,'I'-32,'R'-32+128     
        defb    'C'-32,'P'-32,'I'-32,'R'-32+128     
        defb    'I'-32,'N'-32,'I'-32,'R'-32+128     
        defb    'O'-32,'T'-32,'I'-32,'R'-32+128
        defb    'L'-32,'D'-32,'D'-32,'R'-32+128     
        defb    'C'-32,'P'-32,'D'-32,'R'-32+128     
        defb    'I'-32,'N'-32,'D'-32,'R'-32+128
        defb    'O'-32,'T'-32,'D'-32,'R'-32+128
; terminator only needed if index is not bounded above!     
        defb    '@'-32+128 ; list terminator

grp_ed40
        and     7
        ld      b,a
        jr      nz,ged401
ged400
isinpc
        rst     out_str_arg_hi
        defb    'I'-32,'N'-32+64,'3'-32,','-32,'('-32,'C'-32,')'-32+128

ged401  djnz    ged402
isoutc
        rst     out_str_arg_hi
        defb    'O'-32,'U'-32,'T'-32+64,'('-32,'C'-32,')'-32,','-32,'3'-32+128

ged402  djnz    ged403
        rst     rrca3rra
        jr      c,isadcw
issbcw
        rst     out_str_arg
        defb    'S'-32,'B'-32,'C'-32+64,'6'-32,','-32,'7'-32+128
isadcw
        rst     out_str_arg
        defb    'A'-32,'D'-32,'C'-32+64,'6'-32,','-32,'7'-32+128

ged403  djnz    ged404
        rst     rrca3rra
        jr      c,isldrpatnn
isldatnnrp
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'('-32,'5'-32,')'-32,','-32,'7'-32+128
isldrpatnn
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'7'-32,','-32,'('-32,'5'-32,')'-32+128

ged404  djnz    ged405
        ld      a,c
        and     $38
;        jr      nz,xited
isneg
        rst     out_str_ind
        defb    'N'-32,'E'-32,'G'-32+128
        defb    '@'-32+128 ; list terminator

ged405  djnz    ged406
        rst     out_str_ind_hi
        defb    'R'-32,'E'-32,'T'-32,'N'-32+128
        defb    'R'-32,'E'-32,'T'-32,'I'-32+128
        defb    '@'-32+128 ; list terminator

ged406  djnz    ged407
        rst     out_str_ind_hi
        defb    'I'-32,'M'-32+64,'0'-32+128
        defb    128
        defb    'I'-32,'M'-32+64,'1'-32+128
        defb    'I'-32,'M'-32+64,'2'-32+128
        defb    '@'-32+128 ; list terminator

ged407  rst     out_str_ind_hi
        defb    'L'-32,'D'-32+64,'I'-32,','-32,'A'-32+128
        defb    'L'-32,'D'-32+64,'R'-32,','-32,'A'-32+128
        defb    'L'-32,'D'-32+64,'A'-32,','-32,'I'-32+128
        defb    'L'-32,'D'-32+64,'A'-32,','-32,'R'-32+128
        defb    'R'-32,'R'-32,'D'-32+128
        defb    'R'-32,'L'-32,'D'-32+128
        defb    '@'-32+128 ; list terminator
