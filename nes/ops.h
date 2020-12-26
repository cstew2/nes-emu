#ifndef OPS_H
#define OPS_H

#include <stdint.h>
#include <stdbool.h>

#include "nes/cpu.h"
#include "nes/cpu_memory.h"
#include "util/bit_field.h"

/* addressing modes */
uint16_t mem_zero_page(const cpu_registers *r, const cpu_memory_map *cm);
uint16_t mem_zero_page_x(const cpu_registers *r, const cpu_memory_map *cm);
uint16_t mem_zero_page_y(const cpu_registers *r, const cpu_memory_map *cm);
uint16_t mem_absolute(const cpu_registers *r, const cpu_memory_map *cm);
uint16_t mem_absolute_x(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary);
uint16_t mem_absolute_y(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary);
uint16_t mem_indirect(const cpu_registers *r, const cpu_memory_map *cm);
uint16_t mem_indirect_x(const cpu_registers *r, const cpu_memory_map *cm);
uint16_t mem_indirect_y(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary);
uint16_t mem_relative(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary);

/* system */
void op_brk(cpu_registers *r, cpu_memory_map *cm);

/* storage */
void op_ld(cpu_registers *r);
void op_t(cpu_registers *r);

/* registers */
void op_cmp(cpu_registers *r);
void op_cpx(cpu_registers *r);
void op_cpy(cpu_registers *r);

/* bitwise */
void op_and(cpu_registers *r);
void op_asl(cpu_registers *r);
void op_bit(cpu_registers *r);
void op_eor(cpu_registers *r);
void op_lsr(cpu_registers *r);
void op_ora(cpu_registers *r);
void op_rol(cpu_registers *r);
void op_ror(cpu_registers *r);

/* math */
void op_sbc(cpu_registers *r);
void op_adc(cpu_registers *r);
void op_de(cpu_registers *r);
void op_in(cpu_registers *r);

/* stack */
uint8_t op_pl(cpu_registers *r, cpu_memory_map *cm);
void op_ph(cpu_registers *r, cpu_memory_map *cm);
	
/* branch */
void op_b(cpu_registers *r, bool condition);

/* jump */
void op_j(cpu_registers *r, bool condition);

#endif
