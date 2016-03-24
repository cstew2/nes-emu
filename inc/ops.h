#ifndef OPS_H
#define OPS_H

#include <stdint.h>
#include <stdbool.h>

#include "cpu.h"
#include "cpu_memory.h"
#include "bit_field.h"

/* system */
void op_brk(cpu_registers *r, cpu_memory_map *cm);

/* storage */
uint8_t op_ld(cpu_registers *r, uint16_t operand);
uint8_t op_st(cpu_registers *r, uint16_t operand);
uint8_t op_t(cpu_registers *r, uint16_t operand);

/* registers */
void op_cl();
void op_cp();
void op_se();

/* bitwise */
void op_and();
void op_asl();
void op_bit();
void op_eor();
void op_lsa();
void op_ora();
void op_rol();
void op_ror();

/* branch */
void op_b();

/* math */
void op_sbc();
void op_adc();
void op_de();
void op_in();

/* jump */
void op_jmp();
void op_jsr();
void op_rti();
void op_rts();

/* stack */
uint16_t op_pl(cpu_registers *r, cpu_memory_map *m);
uint16_t op_ph(cpu_registers *r, cpu_memory_map *m, uint8_t data);

#endif
