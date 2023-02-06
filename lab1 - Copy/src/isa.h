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
  cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;

}
int SLT (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;

}
int SLTU (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = ZEROEXT(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;

}
int XOR (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;

}
int SRL (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;

}
int SRA (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = SIGNEXT(CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2], 5);
  NEXT_STATE.REGS[Rd] = cur;

}
int OR (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;

}
int AND (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;

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
  cur = SIGNEXT(mem_read_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12)),8);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LH (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = SIGNEXT(mem_read_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12)), 16);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LW (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = mem_read_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12));
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LBU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = mem_read_32(ZEROEXT(CURRENT_STATE.REGS[Rs1] + ZEROEXT(Imm)),8);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LHU (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0;
  cur = mem_read_32(ZEROEXT(CURRENT_STATE.REGS[Rs1] + ZEROEXT(Imm)), 16);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
/* Fix */
int SLLI (int Rd, int Rs1, int Imm, int Funct3, int Funct7) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] << Imm;
  NEXT_STATE.REGS[Rd] = cur;

}
int SLTI (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;

}
int SLTIU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0; 
  cur = CURRENT_STATE.REGS[Rs1] < ZEROEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;

}
int XORI (int Rd, int Rs1, int Imm, int Funct3) { 

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
/* Fix */
int SRLI (int Rd, int Rs1, int Imm, int Funct3, int Funct7) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> Imm;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
/* Fix */
int SRAI (int Rd, int Rs1, int Imm, int Funct3, int Funct7) {

  int cur = 0;
  cur = SIGNEXT(CURRENT_STATE.REGS[Rs1] >> Imm, 5);
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
/* Fix */
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
/* Fix */
int SB (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  cur = mem_write_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12), CURRENT_STATE.REGS[Rs2]);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;


}
/* Fix */
int SH (int Rs1, int Rs2, int Imm, int Funct3) { 

int cur = 0; 
cur = mem_write_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12), CURRENT_STATE.REGS[Rs2])
NEXT_STATE.REGS[Rd] = cur;

}
/* Fix */
int SW (int Rs1, int Rs2, int Imm, int Funct3) {

int cur = 0; 
cur = mem_write_32(CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12), CURRENT_STATE.REGS[Rs2])
NEXT_STATE.REGS[Rd] = cur;

}





// I instruction
int JALR (int Rd, int Rs1, int Imm) { 



}

// J instruction
int JAL (char* i_);

int ECALL (char* i_){return 0;}

#endif
