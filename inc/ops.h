#ifndef OPS_H
#define OPS_H

#include <stdint.h>
#include <stdbool.h>

#include "cpu.h"
#include "cpu_memory.h"
#include "bit_field.h"

/* addressing modes */
uint8_t op_zero_page(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_zero_page_x(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_zero_page_y(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_absolute(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_absolute_x(cpu_registers *r, cpu_memory_map *cm, bool boundary);
uint8_t op_absolute_y(cpu_registers *r, cpu_memory_map *cm, bool boundary);
uint8_t op_indirect(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_immediate(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_indirect_x(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_indirect_y(cpu_registers *r, cpu_memory_map *cm, bool boundary);

/* system */
uint8_t op_brk(cpu_registers *r, cpu_memory_map *cm);

/* storage */
uint8_t op_ld(cpu_registers *r, uint16_t operand);
uint8_t op_st(cpu_registers *r, uint16_t operand);
uint8_t op_t(cpu_registers *r, uint16_t operand);

/* registers */
uint8_t op_cl(cpu_registers *r, uint16_t operand);
uint8_t op_cp(cpu_registers *r, uint16_t operand);
uint8_t op_se(cpu_registers *r, uint16_t operand);

/* bitwise */
uint8_t op_and(cpu_registers *r, uint16_t operand);
uint8_t op_asl(cpu_registers *r);
uint8_t op_bit(cpu_registers *r, uint16_t operand);
uint8_t op_eor(cpu_registers *r, uint16_t operand);
uint8_t op_lsr(cpu_registers *r, uint16_t operand);
uint8_t op_ora(cpu_registers *r, uint16_t operand);
uint8_t op_rol(cpu_registers *r, uint16_t operand);
uint8_t op_ror(cpu_registers *r, uint16_t operand);

/* branch */
uint8_t op_b(cpu_registers *r, uint16_t operand);

/* math */
uint8_t op_sbc(cpu_registers *r, uint16_t operand);
uint8_t op_adc(cpu_registers *r, uint16_t operand);
uint8_t op_de(cpu_registers *r, uint16_t operand);
uint8_t op_in(cpu_registers *r, uint16_t operand);

/* jump */
uint8_t op_jmp(cpu_registers *r, uint16_t operand);
uint8_t op_jsr(cpu_registers *r, uint16_t operand);
uint8_t op_rti(cpu_registers *r, uint16_t operand);
uint8_t op_rts(cpu_registers *r, uint16_t operand);

/* stack */
uint16_t op_pl(cpu_registers *r, cpu_memory_map *m);
uint16_t op_ph(cpu_registers *r, cpu_memory_map *m, uint8_t data);

#endif
