z80dis:
        xor     a
        defb    $fd             ;IYL=isixiy
        ld      l,a             ;ld IYL,a
        ld      a,(hl)
        inc     hl
        cp      $40
        jp      c,grp_00
        cp      $80
        jr      disx
        nop
        nop

rst10:
rrca3
        rrca
        rrca
        rrca
        and     7
        ret
        nop
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

disy    cp      $c0
        jp      disz

rst28:
out_str_ind
        pop     bc
        inc     a
osi0    dec     a
        jr      z,ots0_p1
        push    af
        jr      osiy

rst30:
out_str_arg_hi
        rst     rrca3
        jr      out_str_arg
osiy
osi1    ld      a,(bc)
        inc     bc
        rlca
        jr      osiz

rst38:
out_str
out_str_arg
        defb    $fd             ;IYH=otsarg
        ld      h,a             ;ld IYH,a
ots0    pop     bc
ots0_p1 ld      a,(bc)
        inc     bc
        push    bc
        push    af
        and     $3f
        add     a,32
        ld      (de),a
        inc     de
        sub     a,'3'
        cp      ';'-'3'+1
        call    c,expand
        pop     af
        add     a,a
        jp      p,ots2
        ld      a,' '
        ld      (de),a
        inc     de
ots2    jr      nc,ots0
ots3    pop     bc
        jr      ld_de_0

osiz    jr      nc,osi1
        cp      (' '-32+64)*2+1 ; done if list terminator
        jr      z,ots3
        pop     af
        jr      osi0

expand  dec     de
        defb    $fd             ;IYH=otsarg
        ld      b,h             ;ld b,IYH
        call    jrtbl
        defb    out_reg-$       ; 3
        defb    hexb_at_hl-$    ; 4
        defb    hexw_at_hl-$    ; 5
        defb    out_hlixiy-$    ; 6
        defb    out_rp0-$       ; 7
        defb    out_rp-$        ; 8
        defb    hexrel_at_hl-$  ; 9
        defb    hex_a-$         ; :
        defb    out_cond-$      ; :

out_cond
        rst     out_str_ind
        defb    'N'-32,'Z'-32+128
        defb    'Z'-32+128
        defb    'N'-32,'C'-32+128
        defb    'C'-32+128
        defb    'N'-32,'V'-32+128
        defb    'V'-32+128
        defb    'P'-32+128
        defb    'M'-32+128

out_rp
        inc     a
rp0     inc     a
        and     3
        jr      nz,nothlixiy
out_hlixiy
        defb    $fd             ;IYL=isixiy
        ld      a,l             ;ld a,IYL
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
        ld      c,a
        rlca
        sbc     a,a
        ld      b,a
        push    hl
        add     hl,bc
        ex      (sp),hl
        pop     bc
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
ishl
        defb    $fd             ;IYL=isixiy
        ld      a,l             ;ld a,IYL
        call    regx
        defb    $fd             ;IYL=isixiy
        ld      a,l             ;ld a,IYL
        or      a
        ret     z
        ld      a,(hl)
        inc     hl
        cp      $80
        jr      nc,ofsminus
ofsplus
        rst     out_str_arg
        defb    '+'-32,':'-32,')'-32+128
ofsminus
        neg
        rst     out_str_arg
        defb    '-'-32,':'-32,')'-32+128

regx    rst     out_str_ind
        defb    '('-32,'H'-32,'L'-32,')'-32+128
        defb    '('-32,'I'-32,'X'-32+128
        defb    '('-32,'I'-32,'Y'-32+128

jrtbl8  ld      b,a
        and     7
jrtbl   ex      (sp),hl
        ld      c,a
        ld      a,b
        ld      b,0
        add     hl,bc
        ld      c,(hl)
        add     hl,bc
        ex      (sp),hl
        ret

disz    jp      c,grp_80
grp_c0
        call    jrtbl8
        defb    gc00-$
        defb    gc01-$
        defb    gc02-$
        defb    gc03-$
        defb    gc04-$
        defb    gc05-$
        defb    gc06-$
        defb    gc07-$
gc00
isretc
        rst     out_str_arg_hi
        defb    'R'-32,'E'-32,'T'-32+64,';'-32+128

gc01
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

gc02
isjpc
        rst     out_str_arg_hi
        defb    'J'-32,'P'-32+64,';'-32,','-32,'5'-32+128

gc03
        rst     rrca3
        cp      1
        jr      nz,not_cb
grp_cb                          ;CB
        defb    $fd             ;IYL=isixiy
        ld      a,l             ;ld a,IYL
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
        sub     $40
        push    af              ;save a and c
        jr      c,grp_cb00
grp_cbc0
grp_cb80
grp_cb40
        rlca
        rlca
        and     3               ;a=0,1,2 not 3
        call    bit_res_set
        pop     af
        ld      c,a
        rst     rrca3
        call    hb2
        ld      a,c
        rst     out_str_arg
        defb    ','-32,'3'-32+128

bit_res_set
        rst     out_str_ind
        defb    'B'-32,'I'-32,'T'-32+64+128
        defb    'R'-32,'E'-32,'S'-32+64+128
        defb    'S'-32,'E'-32,'T'-32+64+128

grp_cb00                        ;c is set in af on stack
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

gc04
iscallc
        rst     out_str_arg_hi
        defb    'C'-32,'A'-32,'L'-32,'L'-32+64,';'-32,','-32,'5'-32+128

gc05
        rst     rrca3rra
        jr      c,gc05x
ispush
        rst     out_str_arg
        defb    'P'-32,'U'-32,'S'-32,'H'-32+64,'8'-32+128

gc05x   or      a
        jr      nz,gc051
gc050
iscall
        rst     out_str_arg
        defb    'C'-32,'A'-32,'L'-32,'L'-32+64,'5'-32+128

gc051   dec     a
        jr      z,jpz80dis_p1   ;DD
gc052   dec     a
        jp      z,grp_ed        ;ED
gc053
                                ;FD
jpz80dis_p1
        inc     a               ;a=1,2
        jp      z80dis+1

;gc06
;isalun
;        jr      grp_80

gc07
isrst
        and     $38
        rst     out_str_arg
        defb    'R'-32,'S'-32,'T'-32+64,':'-32+128

gc06                            ;c is clr
grp_80                          ;c is set
        push    af              ;save c
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
        cp      $76
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
        rst     out_str_arg_hi
        defb    'L'-32,'D'-32+64,'3'-32,','-32+128
        
grp_00
        call    jrtbl8
        defb    g000-$
        defb    g001-$
        defb    g002-$
        defb    g003-$
        defb    g004-$
        defb    g005-$
        defb    g006-$
        defb    g007-$

g000
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

g001
        rst     rrca3rra
        jr      c,isaddw
isldw
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'7'-32,','-32,'5'-32+128
isaddw
        rst     out_str_arg
        defb    'A'-32,'D'-32,'D'-32+64,'6'-32,','-32,'7'-32+128

g002
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

g003
isincdecw
        rst     rrca3rra
        jr      c,isdecw
isincw
        rst     out_str_arg
        defb    'I'-32,'N'-32,'C'-32+64,'7'-32+128
isdecw
        rst     out_str_arg
        defb    'D'-32,'E'-32,'C'-32+64,'7'-32+128

g004
isinc
        rst     out_str_arg_hi
        defb    'I'-32,'N'-32,'C'-32+64,'3'-32+128

g005
isdec
        rst     out_str_arg_hi
        defb    'D'-32,'E'-32,'C'-32+64,'3'-32+128

g006
isldn
        rst     out_str_arg_hi
        defb    'L'-32,'D'-32+64,'3'-32,','-32,'4'-32+128

g007
        rst     out_str_ind_hi
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
;        add     $40
        sub     $40+$40
;        jp      c,ld_de_0       ;grp_ed00, grp_edc0
;        cp     $80+$40
        jr      c,grp_ed40
grp_ed80
;        xor     $a0+$40         ;10x..y.. xit if x=0 or y=1
        and     $1f             ;only needed if not only grp_ed80 case!
        ld      c,a
;        and     $24             ;bound to valid range 0-15
;        jp      nz,ld_de_0      ;xit80
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
        defb    ' '-32+64+128 ; list terminator

grp_ed40
        call    jrtbl8
        defb    ged400-$
        defb    ged401-$
        defb    ged402-$
        defb    ged403-$
        defb    ged404-$
        defb    ged405-$
        defb    ged406-$
        defb    ged407-$
ged400
isinpc
        rst     out_str_arg_hi
        defb    'I'-32,'N'-32+64,'3'-32,','-32,'('-32,'C'-32,')'-32+128

ged401
isoutc
        rst     out_str_arg_hi
        defb    'O'-32,'U'-32,'T'-32+64,'('-32,'C'-32,')'-32,','-32,'3'-32+128

ged402
        rst     rrca3rra
        jr      c,isadcw
issbcw
        rst     out_str_arg
        defb    'S'-32,'B'-32,'C'-32+64,'6'-32,','-32,'7'-32+128
isadcw
        rst     out_str_arg
        defb    'A'-32,'D'-32,'C'-32+64,'6'-32,','-32,'7'-32+128

ged403
        rst     rrca3rra
        jr      c,isldrpatnn
isldatnnrp
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'('-32,'5'-32,')'-32,','-32,'7'-32+128
isldrpatnn
        rst     out_str_arg
        defb    'L'-32,'D'-32+64,'7'-32,','-32,'('-32,'5'-32,')'-32+128

ged404
        and     $38
;        jr      nz,xited
isneg
        rst     out_str_ind
        defb    'N'-32,'E'-32,'G'-32+128
        defb    ' '-32+64+128 ; list terminator

ged405
        rst     out_str_ind_hi
        defb    'R'-32,'E'-32,'T'-32,'N'-32+128
        defb    'R'-32,'E'-32,'T'-32,'I'-32+128
        defb    ' '-32+64+128 ; list terminator

ged406
        rst     out_str_ind_hi
        defb    'I'-32,'M'-32+64,'0'-32+128
        defb    128
        defb    'I'-32,'M'-32+64,'1'-32+128
        defb    'I'-32,'M'-32+64,'2'-32+128
        defb    ' '-32+64+128 ; list terminator

ged407
        rst     out_str_ind_hi
        defb    'L'-32,'D'-32+64,'I'-32,','-32,'A'-32+128
        defb    'L'-32,'D'-32+64,'R'-32,','-32,'A'-32+128
        defb    'L'-32,'D'-32+64,'A'-32,','-32,'I'-32+128
        defb    'L'-32,'D'-32+64,'A'-32,','-32,'R'-32+128
        defb    'R'-32,'R'-32,'D'-32+128
        defb    'R'-32,'L'-32,'D'-32+128
        defb    ' '-32+64+128 ; list terminator
