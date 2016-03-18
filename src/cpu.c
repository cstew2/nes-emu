#include <stdlib.h>

#include "debug.h"
#include "bit_field.h"
#include "cpu.h"

cpu_registers *cpu_registers_init(void)
{
	cpu_registers *r = calloc(1, sizeof(cpu_registers));
	
	/*set inital states of registers*/
	r->program_counter = 0x34;
	r->stack_pointer = 0xFD;
	
	r->condition_codes = 0;
	set_field_bit(r->condition_codes, 2, true);

	r->ticks = 0;
	
	return r;
}

void cpu_reset(cpu_registers *r)
{
	/* default values */ 
	r->stack_pointer -= 0x03;
	set_field_bit(r->condition_codes, 2, true);
}

int fetch(cpu_registers *r, cpu_memory_map *cm)
{
	r->instruction = get_cpu_memory(cm, r->program_counter);
	
}

int execute(cpu_registers *r)
{
	
}
