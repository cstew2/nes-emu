#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#include "cpu_memory.h"

static const double ntsc_cpu_clock = 1.7897773f;
static const double pal_cpu_clock = 1.662607f;

/* registers */
typedef struct {
	uint8_t accumulator; /* arithmatic and logic operations results stored */
	uint8_t x_index; /* counter or offset can be used to get the stack pointer */
	uint8_t y_index; /* counter or offset cannot be used to get the stack pointer */
	uint16_t program_counter;
	uint8_t stack_pointer;
	
	uint8_t condition_codes; /* 0-carry, 1-zero, 2-interrupt, 3-decimal, 4-unused, 5-unused, 6-overflow, 7-negative */

	uint64_t ticks;
	uint8_t instruction;
	uint16_t memory_address_buffer;
	uint16_t memory_buffer;
}cpu_registers;


/* function prototypes */
cpu_registers *cpu_registers_init(void);

void set_carry(cpu_registers *r, bool flag);
void set_zero(cpu_registers *r, bool flag);
void set_interrupt(cpu_registers *r, bool flag);
void set_break(cpu_registers *r, bool flag);
void set_overflow(cpu_registers *r, bool flag);
void set_negative(cpu_registers *r, bool flag);

void cpu_reset(cpu_registers *r);
int fetch(cpu_registers *r, cpu_memory_map *cm);
int execute(cpu_registers *r, cpu_memory_map *cm);

#endif
