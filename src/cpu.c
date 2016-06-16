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
	check_memory(r);
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
	set_field_bit(r->condition_codes, 0, flag);
}
void set_zero(cpu_registers *r, bool flag)
{
	set_field_bit(r->condition_codes, 1, flag);
}
void set_interrupt(cpu_registers *r, bool flag)
{
	set_field_bit(r->condition_codes, 2, flag);
}
void set_break(cpu_registers *r, bool flag)
{
	set_field_bit(r->condition_codes, 4, flag);
}
void set_overflow(cpu_registers *r, bool flag)
{
	set_field_bit(r->condition_codes, 6, flag);
}
void set_negative(cpu_registers *r, bool flag)
{
	set_field_bit(r->condition_codes, 7, flag);
}

bool get_carry(cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 0);
}
bool get_zero(cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 1);
}
bool get_interrupt(cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 2);
}
bool get_break(cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 4);
}
bool get_overflow(cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 6);
}
bool get_negative(cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 7);
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
	bool boundary = false;
	uint16_t addr = 0;
	
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
	        r->accumulator = op_ld(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 5 : 4;
		break;
		
	case 0xB9://LDA absolute y
		r->accumulator = op_ld(r, op_absolute_y(r, cm, &boundary));
		counter -= boundary ? 5 : 4;	
		break;
		
	case 0xA1://LDA indirect x
	        r->accumulator = op_ld(r, op_indirect_y(r, cm, &boundary));
		counter -= 6;
		break;
	
	case 0xB1://LDA indirect y
	        r->accumulator = op_ld(r, op_indirect_y(r, cm, &boundary));
		counter -= boundary ? 6 : 5;
		break;

	case 0xA2://LDX immediate
		r->x_index = op_ld(r, op_immediate(r, cm));
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
		r->x_index = op_ld(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;

	case 0xA0://LDY immediate
		r->y_index = op_ld(r, op_immediate(r, cm));
		counter -= 2;
		break;
			
	case 0xA4://LDY zero page
		r->y_index = op_ld(r, op_zero_page(r, cm));
		counter -= 3;
		break;
			
	case 0xB4://LDY zero page x
		r->y_index = op_ld(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0xAC://LDY absolute
		r->y_index = op_ld(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0xBC://LDY absolute x
		r->y_index = op_ld(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;
		
	case 0x85://STA zero page
		set_cpu_memory(cm, op_zero_page(r, cm), r->accumulator);
		counter -= 3;
		break;

	case 0x95://STA zero page x
		set_cpu_memory(cm, op_zero_page_x(r, cm), r->accumulator);
		counter -= 4;
		break;
		
	case 0x8D://STA absolute
		set_cpu_memory(cm, op_absolute(r, cm), r->accumulator);
		counter -= 4;
		break;
		
	case 0x9D://STA absolute x
		set_cpu_memory(cm, op_absolute_x(r, cm, &boundary), r->accumulator);
		counter -= boundary ? 4 : 5;
		break;
			
	case 0x99://STA absolute y
		set_cpu_memory(cm, op_absolute_y(r, cm, &boundary), r->accumulator);
		counter -= boundary ? 4 : 5;
		break;

	case 0x81://STA indirect x
		set_cpu_memory(cm, op_indirect_x(r, cm), r->accumulator);
		counter -= 6;
		break;

	case 0x91://STA indirect y
		set_cpu_memory(cm, op_indirect_y(r, cm, &boundary), r->accumulator);
		counter -= boundary ? 5 : 6;
		break;
		
	case 0x86://STX Zero Page
		set_cpu_memory(cm, op_zero_page(r, cm), r->x_index);
		counter -= 3;
		break;
		
	case 0x96://STX Zero Page, Y
		set_cpu_memory(cm, op_zero_page_y(r, cm), r->x_index);
		counter -= 4;
		break;
		
	case 0x8E://STX Absolute
		set_cpu_memory(cm, op_absolute(r, cm), r->x_index);
		counter -= 4;
		break;

	case 0x84://STY Zero Page
		set_cpu_memory(cm, op_zero_page(r, cm), r->y_index);
		counter -= 3;
		break;
		
	case 0x94://STY Zero Page, X
		set_cpu_memory(cm, op_zero_page_x(r, cm), r->y_index);
		counter -= 4;
		break;
		
	case 0x8C://STY Absolute
		set_cpu_memory(cm, op_absolute(r, cm), r->y_index);
		counter -= 4;
		break;
	 
	case 0xAA://TAX 
		r->x_index = op_t(r, r->accumulator);
		counter -= 2;
		break;
		
	case 0xA8://TAY
		r->y_index = op_t(r, r->accumulator);
		counter -= 2;
		break;
		
	case 0xBA://TSX
		r->x_index = op_t(r, r->stack_pointer);
		counter -= 2;
		break;
		
	case 0x8A://TXA
		r->accumulator = op_t(r, r->x_index);
		counter -= 2;
		break;
		
	case 0x9A://TXS
		r->stack_pointer = op_t(r, r->x_index);
		counter -= 2;
		break;
		
	case 0x98://TYA
		r->accumulator = op_t(r, r->y_index);
		counter -= 2;
		break;
		
	case 0x18://CLC
		set_carry(r, false);
		counter -= 2;
		break;
		
	case 0xD8://CLD *not used in NES*
		log_warn("CLD instruction, clear decimial flag, shouldn't be used in the NES");
		break;
		
	case 0x58://CLI
		set_interrupt(r, false);
		counter -= 2;
		break;
		
	case 0xB8://CLV
		set_overflow(r, false);
		counter -= 2;
		break;

	case 0x38://SEC
		set_carry(r, true);
		break;
		
	case 0x78://SEI
		set_interrupt(r, true);
		break;

	case 0xF8://SED
		log_warn("SED instruction, set decimal flag, shouldn't be use in the NES");
		break;
		
	case 0xC9://CMP immediate
		op_cmp(r, op_immediate(r, cm));
		counter -= 2;
		break;

	case 0xC5://CMP Zero Page
		op_cmp(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0xD5://CMP Zero Page, x
		op_cmp(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0xCD://CMP absolute
		op_cmp(r, op_absolute(r, cm));
		counter -= 4;
		break;
		
	case 0xDD://CMP absolute, x
		op_cmp(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;
		
	case 0xD9://CMP absolute, y
		op_cmp(r, op_absolute_y(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;
		
	case 0xC1://CMP indirect x
		op_cmp(r, op_indirect_x(r, cm));
		counter -= 6;
		break;
		
	case 0xD1://CMP indirect y
		op_cmp(r, op_indirect_y(r, cm, &boundary));
		counter -= boundary ? 5 : 6;
		break;

	case 0xE0://CPX immediate
		op_cpx(r, op_immediate(r, cm));
		counter -= 2;
		break;

	case 0xE4://CPX zero page
		op_cpx(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0xEC://CPX absolute
		op_cpx(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0xC0://CPY immediate
		op_cpy(r, op_immediate(r, cm));
		counter -= 2;
		break;

	case 0xC4://CPY zero page
		op_cpy(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0xCC://CPY absolute
		op_cpy(r, op_absolute(r, cm));		
		counter -= 4;
		break;

	case 0x29://AND immediate
		op_and(r, op_immediate(r, cm));
		counter -= 2;
		break;

	case 0x25://AND zero page
		op_and(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0x35://AND zero page, x
		op_and(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0x2D://AND absolute
		op_and(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0x3D://AND absolute, x
		op_and(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;

	case 0x39://AND aboslute, y
		op_and(r, op_absolute_y(r, cm, &boundary));
		counter -= boundary ? 4: 5;
		break;

	case 0x21://AND indirect, x
		op_and(r, op_indirect_x(r, cm));
		counter -= 6;
		break;

	case 0x31://AND indirect, y
		op_and(r, op_indirect_y(r, cm, boundary));
		counter -= 5;
		break;

	case 0x0A://ASL accumulator
		r->accumulator = op_asl(r, r->accumulator);
		counter -= 2;
		break;

	case 0x06://ASL zero page
		addr =  mem_zero_page(r, cm);
		set_cpu_memory(cm, addr, op_and(op_zero_page(r, cm)));
		counter -= 5;
		break;

	case 0x16://ASL zero page, x
		addr = mem_zero_page_x(r, cm);
		set_cpu_memory(cm, addr, op_asl(op_zero_page_x));
		counter -= 6;
		break;
		
	case 0x0E://ASL absolute
		addr = mem_absolute(r, cm);
		set_cpu_memory(cm, addr, op_asl(op_absolute(r, cm)));
		counter -= 6;
		break;

	case 0x24://BIT zero page
		op_bit(op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0x2C://BIT absolute
		op_bit(op_absolute(r, cm));
		counter -= 4;
		break;

	case 0x49://EOR immediate
		r->accumulator = op_eor(r, op_immediate(r, cm));
		counter -= 2;
		break;

	case 0x45://EOR zero page
		r->accumulator = op_eor(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0x55://EOR zero page, x
		r->accumulator = op_eor(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0x40://EOR absolute
		r->accumulator = op_eor(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0x50://EOR absolute, x
		r->accumulator = op_eor(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;

	case 0x59://EOR absolute, y
		r->accumulator = op_eor(r, op_absolute_y(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;

	case 0x41://EOR indirect, x
		r->accumulator = op_eor(r, op_indirect_x(r, cm));
		counter -= 6;
		break;

	case 0x51://EOR indirect y
		r->accumulator = op_eor(r, op_indirect_y(r, cm));
		counter -= boundary ? 5 : 6;
		break;
		
	case 0x4A://LSR accumulator 
		r->accumulator = op_lsr(r, r->accumulator);
		counter -= 2;
		break;

	case 0x46://LSR Zero Page
		addr = mem_zero_page(r, cm);
		set_cpu_memory(cm, addr, op_lsr(op_zero_page(r, cm)));
		counter -= 5;
		break;

	case 0x56://LSR zero page, x
		addr = mem_zero_page_x(r, cm);
		set_cpu_memory(cm, addr, op_lsr(op_zero_page_x(r, cm)));
		counter -= 6;
		break;

	case 0x4E://LSR absolute
		addr = mem_absolute(r, cm);
		set_cpu_memory(cm, addr, op_lsr(op_absolute(r, cm)));
		counter -= 6;
		break;

	case 0x5E://LSR absolute, x
		addr =  mem_absolute_x(r, cm);
		set_cpu_memory(cm, addr, op_lsr(op_absolute_x(r, cm)));
		break;
		
	case 0x09://ORA immediate
		r->accumulator = op_ora(r, op_immediate(r, cm));
		counter -= 2;
		break;
		
	case 0x05://ORA zero page
		r->accumulator = op_ora(r, op_zero_page(r, cm));
		counter -= 3;
		break;

	case 0x15://ORA zero page, x
		r->accumulator = op_ora(r, op_zero_page_x(r, cm));
		counter -= 4;
		break;

	case 0x0D://ORA absolute
		r->accumulator = op_ora(r, op_absolute(r, cm));
		counter -= 4;
		break;

	case 0x1D://ORA aboslute, x
		r->accumulator = op_ora(r, op_absolute_x(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;

	case 0x19://ORA absolute, y
		r->accumulator = op_ora(r, op_absolute_y(r, cm, &boundary));
		counter -= boundary ? 4 : 5;
		break;

	case 0x01://ORA indirect, x
		r->accumulator = op_ora(r, op_indirect_x(r, cm));
		counter -= 6;
		break;

	case 0x11://ORA indirect, y
		r->accumulator = op_ora(r, op_indirect_y(r, cm));
		counter -= 5;
		break;

	case 0x2A://ROL accumulator
		r->accumulator = op_rol(r, r->accumulator);
		counter -= 2;
		break;

	case 0x26://ROL zero page
		addr =  mem_zero_page(r, cm);
		set_cpu_memory(cm, addr, op_rol(r, op_zero_page(r, cm)));
		counter -= 5;
		break;

	case 0x36://ROL zero page, x
		addr = mem_zero_page_x(r, cm);
		set_cpu_memory(cm, addr, op_rol(r, op_zero_page_x(r, cm)));
		counter -= 6;
		break;

	case 0x2E://ROL absolute
		addr = mem_absolute(r, cm);
		set_cpu_memory(cm, addr, op_rol(r, op_absolute(r, cm)));
		counter -= 6;
		break;

	case 0x3E://ROL absolute x 
		addr = mem_absolute_x(r, cm);
		set_cpu_memory(cm, addr, op_rol(r, op_absolute_x(r, cm)));
		counter -= 7;
		break;

	case 0x6A://ROR accumulator
		r->accumulator = op_ror(r, r->accumulator);
		counter -= 2;
		break;

	case 0x66://ROR zero page
		addr =  mem_zero_page(r, cm);
		set_cpu_memory(cm, addr, op_ror(r, op_zero_page(r, cm)));
		counter -= 5;
		break;

	case 0x76://ROR zero page, x
		addr = mem_zero_page_x(r, cm);
		set_cpu_memory(cm, addr, op_ror(r, op_zero_page_x(r, cm)));
		counter -= 6;
		break;

	case 0x6E://ROR absolute
		addr = mem_absolute(r, cm);
		set_cpu_memory(cm, addr, op_ror(r, op_absolute(r, cm)));
		counter -= 6;
		break;

	case 0x7E://ROR absolute, x
		addr = mem_absolute_x(r, cm);
		set_cpu_memory(cm, addr, op_ror(r, op_absolute_x(r, cm)));
		counter -= 7;
		break;

	case 0xE9://SBC immediate
		
		break;

	case 0xE5://SBC zero page
		
		break;

	case 0xF%://SBC zero page, x
		
		break;

	case 0xED://SBC absolute
		
		break;

	case 0xFD://SBC absolute, x
		
		break;

	case 0xF9://SBC absolute, y
		
		break;

	case 0xE1://SBC indirect, x
		
		break;

	case 0xF1://SBC indirect, y
		
		break;

	case 0x://
		
		break;

	case 0x://
		
		break;

	case 0x://
		
		break;

	case 0x://
		
		break;


		
		
	default://illegal opcode
		log_warn("Illegal opcode at %X", r->instruction);
		break;
	}
	return counter;
}
