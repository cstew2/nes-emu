#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

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

void set_carry(cpu_registers *r, bool flag)
{
	set_bit_field(r->condition_codes, 0, flag);
}
void set_zero(cpu_registers *r, bool flag)
{
	set_bit_field(r->condition_codes, 1, flag);
}
void set_interrupt(cpu_registers *r, bool flag)
{
	set_bit_field(r->condition_codes, 2, flag);
}
void set_break(cpu_registers *r, bool flag)
{
	set_bit_field(r->condition_codes, 4, flag);
}
void set_overflow(cpu_registers *r, bool flag)
{
	set_bit_field(r->condition_codes, 6, flag);
}
void set_negative(cpu_registers *r, bool flag)
{
	set_bit_field(r->condition_codes, 7, flag);
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
	bool boundry = false;
	
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
		r->accumulator = op_ld(r, op_immediate(r, cm));
		counter -= 2;
		break;

	case 0xA5://LDA zero page
		r->accumulator = op_ld(r, op_zero_page(r, cm));
		counter -= 3;
		break;
		
	case 0xB5://LDA zero page x
		r->accumulator = op_ld(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;
		
	case 0xAD://LDA absolute
		r->accumulator = op_ld(r, op_absolute(r, cm));
		counter -= 4;
		break;
		
	case 0xBD://LDA absolute x
	        r->accumulator = op_ld(r, op_absolute_x(r, cm, boundary));
		counter -= boundary ? 5 : 4;
		break;
		
	case 0xB9://LDA absolute y
		r->accumulator = op_ld(r, op_absolute_y(r, cm, boundary));
		counter -= boundary ? 5 : 4;	
		break;
		
	case 0xA1://LDA indirect x
	        r->accumulator = op_ld(r, op_indirect_y(r, cm, boundary));
		counter -= 6;
		break;
	
	case 0xB1://LDA indirect y
	        r->accumulator = op_ld(r, op_indirect_y(r, cm, boundary));
		counter -= boundary ? 6 : 5;
		break;

	case 0xA2://LDX immediate
		r->x_index = op_ld(r, op(r, cm));
		counter -= 2;
		break;

	case 0xA6://LDX zero page
		r->x_index = op_ld(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0xB6://LDX zero page x
		r->x_index = op_ld(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0xAE://LDX absolute
		r->x_index = op_ld(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0xBE://LDX absolute, x
		r->x_index = op_ld(r, op__absolute_x(r, cm));
		counter -= boundary ? 4 : 5;
		break;

	case 0xA0://LDY immediate
		r->y_index = op_ld(r, op_immediate(r, cm));
		counter -= 2;
		break;
			
	case 0xA0://LDY zero page
		r->y_index = op_ld(r, op_zero_page(r, cm));
		counter -= 3;
		break;
			
	case 0xA0://LDY zero page x
		r->y_index = op_ld(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0xA0://LDY absolute
		r->y_index = op_ld(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0xA0://LDY absolute x
		r->y_index = op_ld(r, op_absolute_x(r, cm));
		counter -= boundry ? 4 : 5;
		break;
		
	case 0x85://STA zero page
		r->accumulator = op_zero_page(r, cm);
		counter -= 3;
		break;

	case 0x95://STA zero page x
		r->accumulator = op_zero_page_x(r, cm);
		counter -= 4;
		break;
		
	case 0x8D://STA absolute
		r->accumulator = op_absolute(r, cm);
		counter -= 4;
		break;
		
	case 0x9D://STA absolute x
		r->accumulator = op_absolute_x(r, cm);
		counter -= boundry ? 4 : 5;
		break;
			
	case 0x99://STA absolute y
		r->accumulator = op_absolute_y(r, cm);
		counter -= boundry ? 4 : 5;
		break;

	case 0x81://STA indirect x
		r->accumulator = op_indirect_x(r, cm);
		counter -= 6;
		break;

	case 0x81://STA indirect y
		r->accumulator = op_indirect_y(r, cm);
		counter -= boundry ? 5 : 6;
		break;

	case 0x://
		
		break;
		
	default://illegal opcode
		log_warn("Illegal opcode at %X", r->instruction);
		break;
	}
	return counter;
}
