#include <stdlib.h>

#include "debug.h"
#include "bit_field.h"
#include "cpu.h"

cpu_registers *cpu_registers_init(void)
{
	cpu_registers *r = calloc(1, sizeof(cpu_registers));
	
	/*set inital states of registers*/
	set_program_counter(r, 0x34);
	set_accumulator(r, 0x00);
	set_x_index(r, 0x00);
	set_y_index(r, 0x00);
	set_stack_pointer(r, 0xFD);

	set_carry(r, false);
	set_zero(r, false);
	set_interrupt(r, true);
	set_overflow(r, false);
	set_negative(r, false);

	set_ticks(r, 0);
	
	return r;
}

void cpu_reset(cpu_registers *r)
{
	/* default values */ 
	set_stack_pointer(r, get_stack_pointer(r) - 0x03);
	set_interrupt(r, true);
}

uint8_t get_accumulator(cpu_registers *r)
{
	return r->accumulator;
}
void set_accumulator(cpu_registers *r, uint8_t i)
{
	r->accumulator = i;
	log_info("set accumulator to %i", i);
}

uint8_t get_x_index(cpu_registers *r)
{
	return r->x_index;
}

void set_x_index(cpu_registers *r, uint8_t i)
{
	r->x_index = i;
	log_info("set x_index to %i",  i);
}

uint8_t get_y_index(cpu_registers *r)
{
	return r->y_index;
}

void set_y_index(cpu_registers *r, uint8_t i)
{
	r->y_index = i;
	log_info("set y_index to %i", i);
}

uint8_t get_program_counter(cpu_registers *r)
{
	return r->program_counter;
}

void set_program_counter(cpu_registers *r, uint8_t i)
{
	r->program_counter = i;
	log_info("set program counter to %i", i);
}

uint8_t get_stack_pointer(cpu_registers *r)
{
	return r->stack_pointer;
}

void set_stack_pointer(cpu_registers *r, uint8_t i)
{
	r->stack_pointer = i;
	log_info("set stack pointer to %i", i);
}

bool get_carry(cpu_registers *r)
{
	return get_field_bit(r->status, 0);
}

void set_carry(cpu_registers *r, bool b)
{
	set_field_bit(r->status, 0, b);
	log_info("set carry status flag to %i", b);
}

bool get_zero(cpu_registers *r)
{
	return get_field_bit(r->status, 1);
}

void set_zero(cpu_registers *r, bool b)
{
	set_field_bit(r->status, 1, b);
	log_info("set zero status flag to %i", b);
}

bool get_interrupt(cpu_registers *r)
{
	return get_field_bit(r->status, 2);
}

void set_interrupt(cpu_registers *r, bool b)
{
	set_field_bit(r->status, 2, b);
	log_info("set zero status flag to %i", b);
}

bool get_overflow(cpu_registers *r)
{
	return get_field_bit(r->status, 6);
}

void set_overflow(cpu_registers *r, bool b)
{
	set_field_bit(r->status, 6, b);
	log_info("set overflow status flag to %i", b);
}

bool get_negative(cpu_registers *r)
{
	return get_field_bit(r->status, 7);
}

void set_negative(cpu_registers *r, bool b)
{
	set_field_bit(r->status, 7, b);
	log_info("set negative status flag to %i", b);
}

uint64_t get_ticks(cpu_registers *r)
{
	return r->ticks;
}

void set_ticks(cpu_registers *r, uint8_t i)
{
	r->ticks += i;
}
