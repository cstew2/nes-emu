#ifndef OPS_H
#define OPS_H

#include <stdint.h>
#include <stdbool.h>

#include "nes/cpu.h"
#include "nes/cpu_memory.h"
#include "util/bit_field.h"

/* memory for addressing modes 
also needed for instructions that work on memory*/
uint8_t mem_zero_page(cpu_registers *r, cpu_memory_map *cm);
uint8_t mem_zero_page_x(cpu_registers *r, cpu_memory_map *cm);
uint16_t mem_absolute(cpu_registers *r, cpu_memory_map *cm);
uint16_t mem_absolute_x(cpu_registers *r, cpu_memory_map *cm);
uint16_t mem_relative(cpu_registers *r, cpu_memory_map *cm, bool boundary);
uint16_t mem_indirect(cpu_registers *r, cpu_memory_map *cm);

/* addressing modes */
uint8_t op_zero_page(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_zero_page_x(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_zero_page_y(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_absolute(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_absolute_x(cpu_registers *r, cpu_memory_map *cm, bool boundary);
uint8_t op_absolute_y(cpu_registers *r, cpu_memory_map *cm, bool boundary);
uint16_t op_indirect(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_immediate(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_indirect_x(cpu_registers *r, cpu_memory_map *cm);
uint8_t op_indirect_y(cpu_registers *r, cpu_memory_map *cm, bool boundary);

/* system */
void op_brk(cpu_registers *r, cpu_memory_map *cm);

/* storage */
uint8_t op_ld(cpu_registers *r, uint8_t operand);
uint8_t op_t(cpu_registers *r, uint8_t operand);

/* registers */
uint8_t op_cmp(cpu_registers *r, uint8_t operand);
uint8_t op_cpx(cpu_registers *r, uint8_t operand);
uint8_t op_cpy(cpu_registers *r, uint8_t operand);

/* bitwise */
uint8_t op_and(cpu_registers *r, uint8_t operand);
uint8_t op_asl(cpu_registers *r, uint8_t operand);
void op_bit(cpu_registers *r, uint8_t operand);
uint8_t op_eor(cpu_registers *r, uint8_t operand);
uint8_t op_lsr(cpu_registers *r, uint8_t operand);
uint8_t op_ora(cpu_registers *r, uint8_t operand);
uint8_t op_rol(cpu_registers *r, uint8_t operand);
uint8_t op_ror(cpu_registers *r, uint8_t operand);

/* math */
uint8_t op_sbc(cpu_registers *r, uint8_t operand);
uint8_t op_adc(cpu_registers *r, uint8_t operand);
uint8_t op_de(cpu_registers *r, uint8_t operand);
uint8_t op_in(cpu_registers *r, uint8_t operand);

/* stack */
uint8_t op_pl(cpu_registers *r, cpu_memory_map *m);
void op_ph(cpu_registers *r, cpu_memory_map *m, uint8_t operand);

/* branch */
uint8_t op_b(cpu_registers *r, cpu_memory_map *cm, bool condition);
#endif
