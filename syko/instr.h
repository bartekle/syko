#ifndef __INSTR_H__
#define __INSTR_H__

void F_CALL(void);
void F_RETI(void);
void F_OUT(void);
void F_SBI(void);
void F_CBI(void);
void F_NOP(void);
void F_JMP_MEMC(void);
void F_JMP_K(void);
void F_CLI(void);
void F_SEI(void);

#endif //__INSTR_H__
