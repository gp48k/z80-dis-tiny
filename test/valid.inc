 NOP
 LD BC,$1234
 LD (BC),A
 INC BC
 INC B
 DEC B
 LD B,$AA
 RLCA
 EX AF,AF'
 ADD HL,BC
 LD A,(BC)
 DEC BC
 INC C
 DEC C
 LD C,$AA
 RRCA
 DJNZ $8014
 LD DE,$1234
 LD (DE),A
 INC DE
 INC D
 DEC D
 LD D,$AA
 RLA
 JR $8020
 ADD HL,DE
 LD A,(DE)
 DEC DE
 INC E
 DEC E
 LD E,$AA
 RRA
 JR NZ,$802A
 LD HL,$1234
 LD ($1234),HL
 INC HL
 INC H
 DEC H
 LD H,$AA
 DAA
 JR Z,$8038
 ADD HL,HL
 LD HL,($1234)
 DEC HL
 INC L
 DEC L
 LD L,$AA
 CPL
 JR NC,$8044
 LD SP,$1234
 LD ($1234),A
 INC SP
 INC (HL)
 DEC (HL)
 LD (HL),$AA
 SCF
 JR C,$8052
 ADD HL,SP
 LD A,($1234)
 DEC SP
 INC A
 DEC A
 LD A,$AA
 CCF
 LD B,B
 LD B,C
 LD B,D
 LD B,E
 LD B,H
 LD B,L
 LD B,(HL)
 LD B,A
 LD C,B
 LD C,C
 LD C,D
 LD C,E
 LD C,H
 LD C,L
 LD C,(HL)
 LD C,A
 LD D,B
 LD D,C
 LD D,D
 LD D,E
 LD D,H
 LD D,L
 LD D,(HL)
 LD D,A
 LD E,B
 LD E,C
 LD E,D
 LD E,E
 LD E,H
 LD E,L
 LD E,(HL)
 LD E,A
 LD H,B
 LD H,C
 LD H,D
 LD H,E
 LD H,H
 LD H,L
 LD H,(HL)
 LD H,A
 LD L,B
 LD L,C
 LD L,D
 LD L,E
 LD L,H
 LD L,L
 LD L,(HL)
 LD L,A
 LD (HL),B
 LD (HL),C
 LD (HL),D
 LD (HL),E
 LD (HL),H
 LD (HL),L
 HALT
 LD (HL),A
 LD A,B
 LD A,C
 LD A,D
 LD A,E
 LD A,H
 LD A,L
 LD A,(HL)
 LD A,A
 ADD A,B
 ADD A,C
 ADD A,D
 ADD A,E
 ADD A,H
 ADD A,L
 ADD A,(HL)
 ADD A,A
 ADC A,B
 ADC A,C
 ADC A,D
 ADC A,E
 ADC A,H
 ADC A,L
 ADC A,(HL)
 ADC A,A
 SUB B
 SUB C
 SUB D
 SUB E
 SUB H
 SUB L
 SUB (HL)
 SUB A
 SBC A,B
 SBC A,C
 SBC A,D
 SBC A,E
 SBC A,H
 SBC A,L
 SBC A,(HL)
 SBC A,A
 AND B
 AND C
 AND D
 AND E
 AND H
 AND L
 AND (HL)
 AND A
 XOR B
 XOR C
 XOR D
 XOR E
 XOR H
 XOR L
 XOR (HL)
 XOR A
 OR B
 OR C
 OR D
 OR E
 OR H
 OR L
 OR (HL)
 OR A
 CP B
 CP C
 CP D
 CP E
 CP H
 CP L
 CP (HL)
 CP A
 RET NZ
 POP BC
 JP NZ,$80E0
 JP $80E3
 CALL NZ,$80E6
 PUSH BC
 ADD A,$AA
 RST $00
 RET Z
 RET
 JP Z,$80EF
 SET 1,E
 CALL Z,$80F4
 CALL $80F7
 ADC A,$AA
 RST $08
 RET NC
 POP DE
 JP NC,$80FF
 OUT ($10),A
 CALL NC,$8104
 PUSH DE
 SUB $AA
 RST $10
 RET C
 EXX
 JP C,$810D
 IN A,($10)
 CALL C,$8112
 INC IX
 SBC A,$AA
 RST $18
 RET NV
 POP HL
 JP NV,$811C
 EX (SP),HL
 CALL NV,$8120
 PUSH HL
 AND $AA
 RST $20
 RET V
 JP (HL)
 JP V,$8129
 EX DE,HL
 CALL V,$812D
 LDIR
 XOR $AA
 RST $28
 RET P
 POP AF
 JP P,$8137
 DI
 CALL P,$813B
 PUSH AF
 OR $AA
 RST $30
 RET M
 LD SP,HL
 JP M,$8144
 EI
 CALL M,$8148
 DEC IY
 CP $AA
 RST $38
 RLC B
 RLC C
 RLC D
 RLC E
 RLC H
 RLC L
 RLC (HL)
 RLC A
 RRC B
 RRC C
 RRC D
 RRC E
 RRC H
 RRC L
 RRC (HL)
 RRC A
 RL B
 RL C
 RL D
 RL E
 RL H
 RL L
 RL (HL)
 RL A
 RR B
 RR C
 RR D
 RR E
 RR H
 RR L
 RR (HL)
 RR A
 SLA B
 SLA C
 SLA D
 SLA E
 SLA H
 SLA L
 SLA (HL)
 SLA A
 SRA B
 SRA C
 SRA D
 SRA E
 SRA H
 SRA L
 SRA (HL)
 SRA A
 SRL B
 SRL C
 SRL D
 SRL E
 SRL H
 SRL L
 SRL (HL)
 SRL A
 BIT 0,B
 BIT 0,C
 BIT 0,D
 BIT 0,E
 BIT 0,H
 BIT 0,L
 BIT 0,(HL)
 BIT 0,A
 BIT 1,B
 BIT 1,C
 BIT 1,D
 BIT 1,E
 BIT 1,H
 BIT 1,L
 BIT 1,(HL)
 BIT 1,A
 BIT 2,B
 BIT 2,C
 BIT 2,D
 BIT 2,E
 BIT 2,H
 BIT 2,L
 BIT 2,(HL)
 BIT 2,A
 BIT 3,B
 BIT 3,C
 BIT 3,D
 BIT 3,E
 BIT 3,H
 BIT 3,L
 BIT 3,(HL)
 BIT 3,A
 BIT 4,B
 BIT 4,C
 BIT 4,D
 BIT 4,E
 BIT 4,H
 BIT 4,L
 BIT 4,(HL)
 BIT 4,A
 BIT 5,B
 BIT 5,C
 BIT 5,D
 BIT 5,E
 BIT 5,H
 BIT 5,L
 BIT 5,(HL)
 BIT 5,A
 BIT 6,B
 BIT 6,C
 BIT 6,D
 BIT 6,E
 BIT 6,H
 BIT 6,L
 BIT 6,(HL)
 BIT 6,A
 BIT 7,B
 BIT 7,C
 BIT 7,D
 BIT 7,E
 BIT 7,H
 BIT 7,L
 BIT 7,(HL)
 BIT 7,A
 RES 0,B
 RES 0,C
 RES 0,D
 RES 0,E
 RES 0,H
 RES 0,L
 RES 0,(HL)
 RES 0,A
 RES 1,B
 RES 1,C
 RES 1,D
 RES 1,E
 RES 1,H
 RES 1,L
 RES 1,(HL)
 RES 1,A
 RES 2,B
 RES 2,C
 RES 2,D
 RES 2,E
 RES 2,H
 RES 2,L
 RES 2,(HL)
 RES 2,A
 RES 3,B
 RES 3,C
 RES 3,D
 RES 3,E
 RES 3,H
 RES 3,L
 RES 3,(HL)
 RES 3,A
 RES 4,B
 RES 4,C
 RES 4,D
 RES 4,E
 RES 4,H
 RES 4,L
 RES 4,(HL)
 RES 4,A
 RES 5,B
 RES 5,C
 RES 5,D
 RES 5,E
 RES 5,H
 RES 5,L
 RES 5,(HL)
 RES 5,A
 RES 6,B
 RES 6,C
 RES 6,D
 RES 6,E
 RES 6,H
 RES 6,L
 RES 6,(HL)
 RES 6,A
 RES 7,B
 RES 7,C
 RES 7,D
 RES 7,E
 RES 7,H
 RES 7,L
 RES 7,(HL)
 RES 7,A
 SET 0,B
 SET 0,C
 SET 0,D
 SET 0,E
 SET 0,H
 SET 0,L
 SET 0,(HL)
 SET 0,A
 SET 1,B
 SET 1,C
 SET 1,D
 SET 1,E
 SET 1,H
 SET 1,L
 SET 1,(HL)
 SET 1,A
 SET 2,B
 SET 2,C
 SET 2,D
 SET 2,E
 SET 2,H
 SET 2,L
 SET 2,(HL)
 SET 2,A
 SET 3,B
 SET 3,C
 SET 3,D
 SET 3,E
 SET 3,H
 SET 3,L
 SET 3,(HL)
 SET 3,A
 SET 4,B
 SET 4,C
 SET 4,D
 SET 4,E
 SET 4,H
 SET 4,L
 SET 4,(HL)
 SET 4,A
 SET 5,B
 SET 5,C
 SET 5,D
 SET 5,E
 SET 5,H
 SET 5,L
 SET 5,(HL)
 SET 5,A
 SET 6,B
 SET 6,C
 SET 6,D
 SET 6,E
 SET 6,H
 SET 6,L
 SET 6,(HL)
 SET 6,A
 SET 7,B
 SET 7,C
 SET 7,D
 SET 7,E
 SET 7,H
 SET 7,L
 SET 7,(HL)
 SET 7,A
 IN B,(C)
 OUT (C),B
 SBC HL,BC
 LD ($1234),BC
 NEG
 RETN
 IM 0
 LD I,A
 IN C,(C)
 OUT (C),C
 ADC HL,BC
 LD BC,($1234)
 RETI
 LD R,A
 IN D,(C)
 OUT (C),D
 SBC HL,DE
 LD ($1234),DE
 IM 1
 LD A,I
 IN E,(C)
 OUT (C),E
 ADC HL,DE
 LD DE,($1234)
 IM 2
 LD A,R
 IN H,(C)
 OUT (C),H
 SBC HL,HL
 LD ($1234),HL
 RRD
 IN L,(C)
 OUT (C),L
 ADC HL,HL
 LD HL,($1234)
 RLD
 SBC HL,SP
 LD ($1234),SP
 IN A,(C)
 OUT (C),A
 ADC HL,SP
 LD SP,($1234)
 LDI
 CPI
 INI
 OUTI
 LDD
 CPD
 IND
 OUTD
 LDIR
 CPIR
 INIR
 OTIR
 LDDR
 CPDR
 INDR
 OTDR
 ADD IX,BC
 ADD IY,BC
 ADD IX,DE
 ADD IY,DE
 ADD IX,IX
 ADD IY,IY
 ADD IX,SP
 ADD IY,SP
 LD IX,$1234
 LD IY,$1234
 LD IX,($1234)
 LD IY,($1234)
 LD ($1234),IX
 LD ($1234),IY
 DEC IX
 DEC IY
 INC (IX+$10)
 INC (IY-$10)
 DEC (IX+$10)
 DEC (IY-$10)
 LD (IX+$01),$AA
 LD (IY+$02),$AA
 LD B,(IX+$01)
 LD (IX-$01),B
 LD B,(IY+$7F)
 LD (IY-$80),B
 LD C,(IX+$01)
 LD (IX-$01),C
 LD C,(IY+$7F)
 LD (IY-$80),C
 LD D,(IX+$01)
 LD (IX-$01),D
 LD D,(IY+$7F)
 LD (IY-$80),D
 LD E,(IX+$01)
 LD (IX-$01),E
 LD E,(IY+$7F)
 LD (IY-$80),E
 LD H,(IX+$01)
 LD (IX-$01),H
 LD H,(IY+$7F)
 LD (IY-$80),H
 LD L,(IX+$01)
 LD (IX-$01),L
 LD L,(IY+$7F)
 LD (IY-$80),L
 LD A,(IX+$01)
 LD (IX-$01),A
 LD A,(IY+$7F)
 LD (IY-$80),A
 ADD A,(IX+$07)
 ADD A,(IY-$07)
 ADC A,(IX+$07)
 ADC A,(IY-$07)
 SUB (IX+$07)
 SUB (IY-$07)
 SBC A,(IX+$07)
 SBC A,(IY-$07)
 AND (IX+$07)
 AND (IY-$07)
 XOR (IX+$07)
 XOR (IY-$07)
 OR (IX+$07)
 OR (IY-$07)
 CP (IX+$07)
 CP (IY-$07)
 POP IX
 PUSH IX
 POP IY
 PUSH IY
 EX (SP),IX
 EX (SP),IY
 JP (IX)
 JP (IY)
 LD SP,IX
 LD SP,IY
 RLC (IX+$62)
 RLC (IY+$63)
 RRC (IX+$62)
 RRC (IY+$63)
 RL (IX+$62)
 RL (IY+$63)
 RR (IX+$62)
 RR (IY+$63)
 SLA (IX+$62)
 SLA (IY+$63)
 SRA (IX+$62)
 SRA (IY+$63)
 SRL (IX+$62)
 SRL (IY+$63)
 BIT 0,(IX+$07)
 BIT 0,(IY+$03)
 BIT 1,(IX+$07)
 BIT 1,(IY+$03)
 BIT 2,(IX+$07)
 BIT 2,(IY+$03)
 BIT 3,(IX+$07)
 BIT 3,(IY+$03)
 BIT 4,(IX+$07)
 BIT 4,(IY+$03)
 BIT 5,(IX+$07)
 BIT 5,(IY+$03)
 BIT 6,(IX+$07)
 BIT 6,(IY+$03)
 BIT 7,(IX+$07)
 BIT 7,(IY+$03)
 RES 0,(IX+$07)
 RES 0,(IY+$03)
 RES 1,(IX+$07)
 RES 1,(IY+$03)
 RES 2,(IX+$07)
 RES 2,(IY+$03)
 RES 3,(IX+$07)
 RES 3,(IY+$03)
 RES 4,(IX+$07)
 RES 4,(IY+$03)
 RES 5,(IX+$07)
 RES 5,(IY+$03)
 RES 6,(IX+$07)
 RES 6,(IY+$03)
 RES 7,(IX+$07)
 RES 7,(IY+$03)
 SET 0,(IX+$07)
 SET 0,(IY+$03)
 SET 1,(IX+$07)
 SET 1,(IY+$03)
 SET 2,(IX+$07)
 SET 2,(IY+$03)
 SET 3,(IX+$07)
 SET 3,(IY+$03)
 SET 4,(IX+$07)
 SET 4,(IY+$03)
 SET 5,(IX+$07)
 SET 5,(IY+$03)
 SET 6,(IX+$07)
 SET 6,(IY+$03)
 SET 7,(IX+$07)
 SET 7,(IY+$03)
