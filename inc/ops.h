#ifndef OP_H
#define OP_H

#include <stdint.h>
#include "cpu.h"

int brk(cpu_registers *r);
int opa_imm(cpu_registers *r, uint8_t operand);
int ora_zp(cpu_registers *r, uint8_t operand);
int ora_zpx(cpu_registers *r, uint8_t operand);
int ora_abs(cpu_registers *r, uint8_t operand);
int ora_absx(cpu_registers *r, uint8_t operand);
int ora_absy(cpu_registers *r, uint8_t operand);
int ora_indx(cpu_registers *r, uint8_t operand);
int ora_indy(cpu_registers *r, uint8_t operand);

#endif
