#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#include "6502.h"
#include "nes/cpu_memory.h"


static const double ntsc_cpu_clock = 1.7897773f;
static const double pal_cpu_clock = 1.662607f;

/* registers */
typedef struct {
	uint8_t accumulator; /* arithmatic and logic operations results stored */
	uint8_t x_index; /* counter or offset can be used to get the stack pointer */
	uint8_t y_index; /* counter or offset cannot be used to get the stack pointer */
	uint16_t program_counter;
	uint8_t stack_pointer;
	/* 0-carry, 1-zero, 2-interrupt, 3-decimal, 4-unused, 5-unused, 6-overflow, 7-negative */
	uint8_t condition_codes; 
	
	uint64_t ticks;

	/* current instruction state */
	enum mnemonic_enum mnemonic;
	enum addressing_mode mode;
	uint8_t instruction;
	uint16_t operand;
	uint8_t cycles;
}cpu_registers;


/* function prototypes */
cpu_registers *cpu_registers_init(void);
void cpu_registers_term(cpu_registers *cr);

void set_carry(cpu_registers *r, const bool flag);
void set_zero(cpu_registers *r, const bool flag);
void set_interrupt(cpu_registers *r, const bool flag);
void set_break(cpu_registers *r, const bool flag);
void set_overflow(cpu_registers *r, const bool flag);
void set_negative(cpu_registers *r, const bool flag);

bool get_carry(const cpu_registers *r);
bool get_zero(const cpu_registers *r);
bool get_interrupt(const cpu_registers *r);
bool get_break(const cpu_registers *r);
bool get_overflow(const cpu_registers *r);
bool get_negative(const cpu_registers *r);

void cpu_reset(cpu_registers *r);
int fetch(cpu_registers *r, const cpu_memory_map *cm);
int decode(cpu_registers *r, const cpu_memory_map *cm);
int execute(cpu_registers *r, cpu_memory_map *cm); 

#endif
