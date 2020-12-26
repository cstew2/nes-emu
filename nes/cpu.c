#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "emu/error.h"
#include "emu/debug.h"
#include "util/bit_field.h"
#include "nes/cpu.h"
#include "nes/ops.h"
#include "nes/6502.h"

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

	r->ticks = 0;
	r->instruction = 0x00;
	return r;
}

void cpu_registers_term(cpu_registers *cr)
{
	free(cr);
}

void set_carry(cpu_registers *r, const bool flag)
{
	set_field_bit(r->condition_codes, 0, flag);
}
void set_zero(cpu_registers *r, const bool flag)
{
	set_field_bit(r->condition_codes, 1, flag);
}
void set_interrupt(cpu_registers *r, const bool flag)
{
	set_field_bit(r->condition_codes, 2, flag);
}
void set_break(cpu_registers *r, const bool flag)
{
	set_field_bit(r->condition_codes, 4, flag);
}
void set_overflow(cpu_registers *r, const bool flag)
{
	set_field_bit(r->condition_codes, 6, flag);
}
void set_negative(cpu_registers *r, const bool flag)
{
	set_field_bit(r->condition_codes, 7, flag);
}

bool get_carry(const cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 0);
}
bool get_zero(const cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 1);
}
bool get_interrupt(const cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 2);
}
bool get_break(const cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 4);
}
bool get_overflow(const cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 6);
}
bool get_negative(const cpu_registers *r)
{
	return get_field_bit(r->condition_codes, 7);
}

void cpu_reset(cpu_registers *r)
{
	/* default values */ 
	r->stack_pointer -= 0x03;
	set_interrupt(r, true);
	return;
}

int fetch(cpu_registers *r, const cpu_memory_map *cm)
{
	r->instruction = get_cpu_memory(cm, r->program_counter);
	log_msg(INFO, "op: %X\n", r->instruction);
	
	return 0;
}

int decode(cpu_registers *r, const cpu_memory_map *cm)
{
	struct opcode_def current = nes_opcodes[r->instruction];
	r->mode = current.mode;

	bool boundary;
	
       	switch (r->mode) {
	case NONE:
		r->operand = 0x0;
		break;
	case IMPLIED:
		r->operand = 0x0;
		break;
	case IMMEDIATE:
	        r->operand = get_cpu_memory(cm, r->program_counter+1);
		break;
	case ABSOLUTE:
		r->operand = get_cpu_memory(cm, mem_absolute(r, cm));
		break;
	case ZERO_PAGE:
		r->operand = get_cpu_memory(cm, mem_zero_page(r, cm));
		break;
	case RELATIVE:
	        r->operand = get_cpu_memory(cm, r->program_counter+1);
		break;
	case INDIRECT:
		r->operand = get_cpu_memory(cm, mem_indirect(r, cm));
		break;
	case ZERO_PAGE_X:
		r->operand = get_cpu_memory(cm, mem_zero_page_x(r, cm));
		break;
	case ZERO_PAGE_Y:
		r->operand = get_cpu_memory(cm, mem_zero_page_y(r, cm));
		break;
	case INDIRECT_X:
		r->operand = get_cpu_memory(cm, mem_indirect_x(r, cm));
		break;
	case INDIRECT_Y:
		r->operand = get_cpu_memory(cm, mem_indirect_y(r, cm, &boundary));
		break;
	case ABSOLUTE_X:
		r->operand = get_cpu_memory(cm, mem_absolute_x(r, cm, &boundary));
		break;
	case ABSOLUTE_Y:
		r->operand = get_cpu_memory(cm, mem_absolute_y(r, cm, &boundary));
		break;
	default:
		log_msg(ERROR, "Non-existant addressing mode given %X", r->mode);
		break;
	}

	r->mnemonic = current.mnemonic;

	/* calculate cycles */
	r->cycles = current.cycles + boundary ? 1 : 0;
	
	return 0;
}

int execute(cpu_registers *r, cpu_memory_map *cm)
{
	switch(r->mnemonic) {
	case ADC:
		op_adc(r);
		break;
	case AHX:
		
		break;
	case ALR:
		
		break;
	case ANC:
		
		break;
	case AND:
		op_and(r);
		break;
	case ASL:
		op_asl(r);
		break;
	case ARR:

		break;
	case AXS:
		
		break;
	case BCC:
		op_b(r, get_carry(r) == false);
		break;
	case BCS:
		op_b(r, get_carry(r) == true);
		break;
	case BEQ:
		op_b(r, get_zero(r) == false);
		break;
	case BIT:
		op_bit(r);
		break;
	case BMI:
		op_b(r, get_negative(r) == true);
		break;
	case BNE:
		op_b(r, get_zero(r) == false);
		break;
	case BPL:
		op_b(r, get_negative(r) == false);
		break;
	case BRK:
		op_brk(r, cm);
		break;
	case BVC:
		op_b(r, get_overflow(r) == false);
		break;
	case BVS:
		op_b(r, get_overflow(r) == true);
		break;
	case CLC:
		set_carry(r, true);
		break;
	case CLD:
		break;
	case CLI:
		set_interrupt(r, false);
		break;
	case CLV:
		set_overflow(r, false);
		break;
	case CMP:
		op_cmp(r);
		break;
	case CPX:
		op_cpx(r);
		break;
	case CPY:
		op_cpy(r);
		break;
	case DCP:
		break;
	case DEC:
		
		break;
	case DEX:
		
		break;
	case DEY:
		
		break;
	case EOR:
		
		break;
	case INC:
		
		break;
	case INX:
		
		break;
	case INY:
		
		break;
	case ISC:
		
		break;
	case JMP:
		
		break;
	case JSR:
		
		break;
	case KIL:
		
		break;
	case LAS:
		
		break;
	case LAX:
		
		break;
	case LDA:
		
		break;
	case LDX:
		
		break;
	case LDY:
		
		break;
	case LSR:
		
		break;
	case NOP:
		
		break;
	case ORA:
		
		break;
	case PHA:
		
		break;
	case PHP:
		
		break;
	case PLA:
		
		break;
	case PLP:
		
		break;
	case RLA:
		
		break;
	case ROL:
		
		break;
	case ROR:
		
		break;
	case RRA:
		
		break;
	case RTI:
		
		break;
	case RTS:
		
		break;
	case SAX:
		
		break;
	case SBC:
		
		break;
	case SEC:
		
		break;
	case SED:
		
		break;
	case SEI:
		
		break;
	case SHY:
		
		break;
	case SHX:
		
		break;
	case SLO:
		
		break;
	case SRE:
		
		break;
	case STA:
		
		break;
	case STP:
		
		break;
	case STX:
		
		break;
	case STY:
		
		break;
	case TAS:
		
		break;
	case TAX:
		
		break;
	case TAY:
		
		break;
	case TSX:
		
		break;
	case TXA:
		
		break;
	case TXS:
		
		break;
	case TYA:
		
		break;
	case XAA:
		
		break;
	default:
		log_msg(ERROR, "Non-existant addressing mode given %X", r->mode);
		break;
	}

	r->program_counter++;
}
