#include "nes/ops.h"

/* memory for addressing modes */
uint16_t mem_zero_page(const cpu_registers *r, const cpu_memory_map *cm)
{
	return get_cpu_memory(cm, r->program_counter+1);
}

uint16_t mem_zero_page_x(const cpu_registers *r, const cpu_memory_map *cm)
{
	return (get_cpu_memory(cm, r->program_counter+1) + r->x_index) & 0x00FF;
}

uint16_t mem_zero_page_y(const cpu_registers *r, const cpu_memory_map *cm)
{
	return (get_cpu_memory(cm, r->program_counter+1) + r->x_index) & 0x00FF;
}

uint16_t mem_absolute(const cpu_registers *r, const cpu_memory_map *cm)
{
	return bytes_to_word(get_cpu_memory(cm, r->program_counter+1),
			     get_cpu_memory(cm, r->program_counter+2));
}

uint16_t mem_absolute_x(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary)
{
	uint16_t addr = bytes_to_word(get_cpu_memory(cm, r->program_counter+1),
				      get_cpu_memory(cm, r->program_counter+2));
	*boundary = ((addr & 0xFF00) == ((addr + r->x_index) & 0xFF00));
	return addr + r->x_index;
}

uint16_t mem_absolute_y(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary)
{
	uint16_t addr = bytes_to_word(get_cpu_memory(cm, r->program_counter+1),
				      get_cpu_memory(cm, r->program_counter+2));
	
	*boundary = ((addr & 0xFF00) == ((addr + r->y_index) & 0xFF00));
	return addr + r->y_index;
}

uint16_t mem_indirect(const cpu_registers *r, const cpu_memory_map *cm)
{
	uint16_t addr = bytes_to_word(get_cpu_memory(cm, r->program_counter+1),
				      get_cpu_memory(cm, r->program_counter+2));
	return bytes_to_word(get_cpu_memory(cm, addr),
			     get_cpu_memory(cm, addr+1));
}

uint16_t mem_indirect_x(const cpu_registers *r, const cpu_memory_map *cm)
{
	uint16_t addr = get_cpu_memory(cm, r->program_counter+1) + r->x_index;
	return bytes_to_word(get_cpu_memory(cm, addr & 0x00FF),
			     get_cpu_memory(cm, (addr+1) & 0x00FF));	
}

uint16_t mem_indirect_y(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary)
{
	uint16_t zp = get_cpu_memory(cm, r->program_counter+1);
	uint16_t addr = bytes_to_word(get_cpu_memory(cm, zp & 0x00FF),
				      get_cpu_memory(cm, (zp+1) & 0x00FF));
	
	*boundary = ((addr & 0xFF00) == ((addr + r->y_index) & 0xFF00));
	return addr + r->y_index;
}

uint16_t mem_relative(const cpu_registers *r, const cpu_memory_map *cm, bool *boundary)
{
	uint16_t addr = 0;
	if(get_field_bit(addr, 7)) {
		addr = r->program_counter + 2 + (get_cpu_memory(cm, r->program_counter+1) & 0x80);
	}
	else {
		addr = r->program_counter + 2 - (get_cpu_memory(cm, r->program_counter+1) & 0x80);
	}
	*boundary = (r->program_counter & 0xFF00) == (addr & 0xFF00);
	return addr;
}

/* opcodes */

/* System */
void op_brk(cpu_registers *r, cpu_memory_map *cm)
{
	r->program_counter++;
	r->operand = get_half_word(r->program_counter-1, false);
	op_ph(r, cm);
	r->operand = get_half_word(r->program_counter-1, true);
	op_ph(r, cm);
	r->operand = r->condition_codes | 0x04;
	op_ph(r, cm); //push with b flag set
        r->program_counter = *cm->irq_vector;
}


/* storage */
void op_ld(cpu_registers *r)
{
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
	
}

void op_t(cpu_registers *r)
{
        set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
	
}

/* registers */
void op_cmp(cpu_registers *r)
{
	r->operand -= r->accumulator;
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
	set_carry(r, !r->operand >> 8);
	
}

void op_cpx(cpu_registers *r)
{
	r->operand -= r->x_index;
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
	set_carry(r, !r->operand >> 8);
	
}

void op_cpy(cpu_registers *r)
{
	r->operand -= r->y_index;
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
	set_carry(r, !r->operand >> 8);
	
}

/* bitwise */
void op_and(cpu_registers *r)
{
	r->operand &= r->accumulator;
	set_negative(r, (r->operand >> 8) & 1);
	set_zero(r, r->operand == 0);
	
}

void op_asl(cpu_registers *r)
{
	r->operand <<= 1;
	set_zero(r, r->operand == 0);
	set_negative(r, get_field_bit(r->operand, 7));
	
}

void op_bit(cpu_registers *r)
{
	r->operand &= r->accumulator;
	set_zero(r, r->operand);
	set_negative(r, get_field_bit(r->operand, 7));
	set_overflow(r, get_field_bit(r->operand, 6));
}

void op_eor(cpu_registers *r)
{
	r->operand |= r->accumulator;
	set_zero(r, r->operand == 0);
	set_negative(r, get_field_bit(r->operand, 7));
        
}

void op_lsr(cpu_registers *r)
{
	set_carry(r, get_field_bit(r->operand, 0));
	r->operand >>= 1;
	set_negative(r, 0);
	set_zero(r, r->operand == 0);
	
}

void op_ora(cpu_registers *r)
{
	r->operand |= r->accumulator;
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
	
}

void op_rol(cpu_registers *r)
{
	bool carry = get_carry(r);
	set_carry(r, get_field_bit(r->operand, 7));
	r->operand <<= 1;
	set_field_bit(r->operand, 0, carry);
	set_zero(r, r->operand == 0);
	set_negative(r, get_field_bit(r->operand, 7));
	
}

void op_ror(cpu_registers *r)
{
	bool carry = get_carry(r);
	set_carry(r, get_field_bit(r->operand, 0));
	r->operand >>= 1;
	set_field_bit(r->operand, 7, carry);
	set_zero(r, r->operand == 0);
	set_negative(r, get_field_bit(r->operand, 7));
	
}

/* math */
void op_sbc(cpu_registers *r)
{
	r->operand = r->accumulator - r->operand - (1 - get_carry(r));
	set_carry(r, 0);    //FIX
	set_overflow(r, 0); //FIX
	set_zero(r, r->operand == 0);
	set_negative(r, get_field_bit(r->operand, 7));
	
}

void op_adc(cpu_registers *r)
{
	r->operand = r->accumulator + r->operand + get_carry(r);
	set_carry(r, 0); //FIX
	set_overflow(r, 0); //FIX
	set_zero(r, r->operand == 0);
	set_negative(r, get_field_bit(r->operand, 7));
	
}

void op_de(cpu_registers *r)
{
	r->operand -= 1;
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
}

void op_in(cpu_registers *r)
{
	r->operand += 1;
	set_negative(r, get_field_bit(r->operand, 7));
	set_zero(r, r->operand == 0);
}

/* stack */
uint8_t op_pl(cpu_registers *r, cpu_memory_map *cm)
{
	return get_cpu_memory(cm, r->stack_pointer++);
}

void op_ph(cpu_registers *r, cpu_memory_map *cm)
{
	set_cpu_memory(cm, r->stack_pointer--, r->operand);
}

/* branch */
void op_b(cpu_registers *r, bool condition)
{
	if(condition) {
		r->program_counter += r->operand;
	}
}

/* jumps */
void op_j(cpu_registers *r, bool condition)
{
	r->program_counter = r->operand;
}
