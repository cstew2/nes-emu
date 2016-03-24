#include <stdlib.h>

#include "error.h"
#include "debug.h"
#include "bit_field.h"
#include "cpu.h"
#include "ops.h"

cpu_registers *cpu_registers_init(void)
{
	cpu_registers *r = calloc(1, sizeof(cpu_registers));
	
	/*set inital states of registers*/
	r->program_counter = 0x34;
	r->accumulator = 0;
	r->x_index = 0;
	r->y_index = 0;
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
	return;
}

int fetch(cpu_registers *r, cpu_memory_map *cm)
{
	r->instruction = get_cpu_memory(cm, r->program_counter);
	set_field_bit(r->condition_codes, 0, false);

	r->program_counter++;
	return 0;
}

int execute(cpu_registers *r, cpu_memory_map *cm)
{
        uint8_t counter = 0;
	uint16_t operand = 0;
	
	switch(r->instruction) {
		//system
	case 0x00://BRK
		op_brk(r, cm);
		counter -= 7;
		break;

	case 0xEA://NOP
		counter -= 2;
		break;

		//storage
	case 0xA9://LDA immediate
		r->accumulator = op_ld(r, get_cpu_memory(cm, ++r->program_counter));
		counter -= 2;
		break;

	case 0xA5://LDA zero page
		r->accumulator = op_ld(r, get_cpu_memory(cm, get_cpu_memory(cm ,++r->program_counter)));
		counter -= 3;
		break;

	case 0xB5://LDA zero page x
		r->accumulator = op_ld(r, get_cpu_memory(cm,
				       get_cpu_memory(cm, ++(r->program_counter) + r->x_index)));
		counter -= 4;
		break;
		
	case 0xAD://LDA absolute
		operand = combine(get_cpu_memory(cm, get_cpu_memory(cm,++(r->program_counter))),
				  get_cpu_memory(cm, get_cpu_memory(cm,++(r->program_counter))));
		r->accumulator = op_ld(r, operand);
		counter -= 4;
		break;
		
	case 0xBD://LDA absolute x
		operand = combine(get_cpu_memory(cm, ++(r->program_counter)),
				  get_cpu_memory(cm, ++(r->program_counter)));
		r->accumulator = op_ld(r, operand + r->x_index);
		counter -= ((operand + r->x_index - operand) > 0xFF) ? 4 : 5;
		break;
		
	case 0xB9://LDA absolute y
		operand = combine(get_cpu_memory(cm, ++(r->program_counter)),
				  get_cpu_memory(cm, ++(r->program_counter)));
		r->accumulator = op_ld(r, operand + r->y_index);
		counter -= ((operand + r->y_index - operand) > 0xFF) ? 4 : 5;	
		break;
		
	case 0xA1://LDA indirect x
		operand = get_cpu_memory(cm, ++r->program_counter) + r->x_index;
		r->accumulator = op_ld(r, get_cpu_memory(cm, get_cpu_memory(cm, operand)));
		counter -= 6;
		break;
	
	case 0xB1://LDA indirect y
		operand = get_cpu_memory(cm, ++r->program_counter);
		r->accumulator = op_ld(r, get_cpu_memory(cm, get_cpu_memory(cm, operand)) + r->y_index);
		counter -= ((operand + r->x_index - operand) > 0xFF) ? 4 : 5;
		break;

	case 0xA2://LDX immediate

		break;

	case 0xA6://LDX zero page

		break;

	case 0xB6://LDX zero page x

		break;

	case 0xAE://absolute

		break;

	case 0xBE://absolute, x

		break;
		
		
	default://illegal opcode
		log_warn("Illegal opcode at %X", r->instruction);
		break;
	
	}
	return counter;
}
