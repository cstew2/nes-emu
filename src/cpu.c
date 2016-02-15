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
