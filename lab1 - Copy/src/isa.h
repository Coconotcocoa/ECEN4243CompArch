/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))

//
// MACRO: Zero extend (e.g., 0x80_0000 -> 0x0080_0000)
//
#define ZEROEXT(v)  ((0x00000000) | (v))



/* R Instructions */
int ADD (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SUB (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) { 
  
  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLL (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] << (CURRENT_STATE.REGS[Rs2] >> 27);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}
int SLT (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTU (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = ZEROEXT(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}
int XOR (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRL (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] >> (CURRENT_STATE.REGS[Rs2] >> 27);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}
int SRA (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = SIGNEXT(CURRENT_STATE.REGS[Rs1] >> (CURRENT_STATE.REGS[Rs2] >> 27), 27);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}
int OR (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}
int AND (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}


/* I Instructions */
int ADDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LB (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = SIGNEXT(mem_read_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT((Imm % 4096),12)) >> 24, 8);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LH (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = SIGNEXT(mem_read_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT((Imm % 4096),12)) >> 16, 16);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LW (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = mem_read_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT((Imm % 4096),12));
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int LBU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = ZEROEXT(mem_read_32(CURRENT_STATE.REGS[Rs1] + ZEROEXT((Imm % 4096))) >> 24);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int LHU (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0;
  cur = ZEROEXT(mem_read_32((CURRENT_STATE.REGS[Rs1] + ZEROEXT((Imm % 4096))))>> 16);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SLLI (int Rd, int Rs1, int ZImm, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] << ZImm;
  NEXT_STATE.REGS[Rd] = cur;

}

int SLTI (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;

}

int SLTIU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] < ZEROEXT(Imm);
  NEXT_STATE.REGS[Rd] = cur;

}

int XORI (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SRLI (int Rd, int Rs1, int ZImm, int Funct3, int Funct7) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> ZImm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SRAI (int Rd, int Rs1, int ZImm, int Funct3, int Funct7) {

  int cur = 0;
  cur = SIGNEXT(CURRENT_STATE.REGS[Rs1] >> ZImm, 27);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int ORI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | Imm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int ANDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] & Imm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}


/* B Instructions */
int BNE (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}

int BEQ (int Rs1, int Rs2, int Imm, int Funct3) {
  
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] == CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}

int BLT (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}

int BGE (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}

int BLTU (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < ZEROEXT(CURRENT_STATE.REGS[Rs2]))
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}

int BGEU (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= ZEROEXT(CURRENT_STATE.REGS[Rs2]))
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}


// U Instruction
int AUIPC (int Rd, int Imm) {

  int cur = 0;
  cur = (CURRENT_STATE.PC) + (Imm << 12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LUI (int Rd, int Imm) {

  int cur = 0;
  cur = Imm << 12;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
  
}

// S Instruction
int SB (int Rs1, int Rs2, int Imm, int Funct3) {

  mem_write_32((CURRENT_STATE.REGS[Rs1] + SIGNEXT((Imm % 4096), 12)), (CURRENT_STATE.REGS[Rs2] >> 24));
  return 0;


}
int SH (int Rs1, int Rs2, int Imm, int Funct3) { 

  mem_write_32((CURRENT_STATE.REGS[Rs1] + SIGNEXT((Imm % 4096), 12)), (CURRENT_STATE.REGS[Rs2] >> 16));
  return 0;

}
int SW (int Rs1, int Rs2, int Imm, int Funct3) {

  mem_write_32((CURRENT_STATE.REGS[Rs1] + SIGNEXT((Imm % 4096), 12)), CURRENT_STATE.REGS[Rs2]);
  return 0;

}

// I instruction
int JALR (int Rd, int Rs1, int Imm, int Funct3) { 

int cur = 0; 
cur = (CURRENT_STATE.PC + 4);
NEXT_STATE.REGS[Rd] = cur;
NEXT_STATE.PC = CURRENT_STATE.REGS[Rs1] + Imm; 
return 0;

}

// J instruction
int JAL (int Rd, int Imm) { 

int cur = 0; 
cur = (CURRENT_STATE.PC + 4);
NEXT_STATE.PC = CURRENT_STATE.PC + Imm; 
return 0;

}



int ECALL (char* i_)
{
  return 0;
}

#endif
