#include "nes/ops.h"

/* memory for addressing modes */
uint8_t mem_zero_page(cpu_registers *r, cpu_memory_map *cm)
{
	return get_cpu_memory(cm, r->program_counter) & 0x00FF;
}

uint8_t mem_zero_page_x(cpu_registers *r, cpu_memory_map *cm)
{
	return (get_cpu_memory(cm, r->program_counter) + r->x_index) & 0x00FF;
}

uint16_t mem_absolute(cpu_registers *r, cpu_memory_map *cm)
{
	return combine(get_cpu_memory(cm, r->program_counter),
		       get_cpu_memory(cm, r->program_counter+1));
}

uint16_t mem_absolute_x(cpu_registers *r, cpu_memory_map *cm)
{
	return combine(get_cpu_memory(cm, r->program_counter),
		       get_cpu_memory(cm, r->program_counter+1)) + r->x_index;
}

uint16_t mem_relative(cpu_registers *r, cpu_memory_map *cm, bool boundary)
{
	uint16_t addr = get_cpu_memory(cm, r->program_counter);
	boundary = (addr & 0xFF00) != (addr & 0xFF00);
	
	return addr;
}

uint16_t mem_indirect(cpu_registers *r, cpu_memory_map *cm)
{
	uint16_t addr = combine(get_cpu_memory(cm, r->program_counter),
				get_cpu_memory(cm, r->program_counter+1) & 0xFF);
	//indirect jmp bug
	r->program_counter =+ 2;
	return combine(addr, ((addr + 1) & 0xFF));
}

/* addressing modes */
uint8_t op_zero_page(cpu_registers *r, cpu_memory_map *cm)
{
	return get_cpu_memory(cm, mem_zero_page(r, cm));
}

uint8_t op_zero_page_x(cpu_registers *r, cpu_memory_map *cm)
{
	return get_cpu_memory(cm, mem_zero_page_x(r, cm));
}

uint8_t op_zero_page_y(cpu_registers *r, cpu_memory_map *cm)
{
	return get_cpu_memory(cm,
	      (get_cpu_memory(cm, r->program_counter++) + r->y_index) & 0x00FF);
}

uint8_t op_absolute(cpu_registers *r, cpu_memory_map *cm)
{
	uint8_t addr = get_cpu_memory(cm, mem_absolute(r, cm));
	r->program_counter += 2;
	return addr;
}

uint8_t op_absolute_x(cpu_registers *r, cpu_memory_map *cm, bool boundary)
{
	uint16_t addr =  combine(get_cpu_memory(cm, r->program_counter),
				    get_cpu_memory(cm, r->program_counter+1));
	r->program_counter += 2;
	boundary = !((addr + r->x_index) & 0xFF00) == (addr & 0xFF00);
	return get_cpu_memory(cm, addr + r->x_index);
}

uint8_t op_absolute_y(cpu_registers *r, cpu_memory_map *cm, bool boundary)
{
        uint16_t addr = combine(get_cpu_memory(cm, r->program_counter),
				   get_cpu_memory(cm, r->program_counter+1));
	r->program_counter += 2;
	boundary = !((addr + r->y_index) & 0xFF00) == (addr & 0xFF00);
	return get_cpu_memory(cm, addr + r->y_index);
}

uint16_t op_indirect(cpu_registers *r, cpu_memory_map *cm)
{
	uint16_t addr = combine(
		get_cpu_memory(cm, r->program_counter),
		get_cpu_memory(cm, r->program_counter+1));
	r->program_counter += 2;
        return combine(
		get_cpu_memory(cm, addr),
		get_cpu_memory(cm, addr+1));
}
	
uint8_t op_immediate(cpu_registers *r, cpu_memory_map *cm)
{
	return get_cpu_memory(cm, r->program_counter++);
}

uint8_t op_indirect_x(cpu_registers *r, cpu_memory_map *cm)
{
        uint16_t addr = (get_cpu_memory(cm, r->program_counter++) + r->x_index) & 0xFF;
	return get_cpu_memory(cm, combine(get_cpu_memory(cm, addr),
					  get_cpu_memory(cm, addr+1)));
}

uint8_t op_indirect_y(cpu_registers *r, cpu_memory_map *cm, bool boundary)
{
	uint16_t addr = get_cpu_memory(cm, r->program_counter++);
	boundary = !((addr + r->y_index) & 0xFF00) == (addr & 0xFF00);
	return get_cpu_memory(cm, combine(addr, addr+1)) + r->y_index;
}


/* opcodes */

/* System */
void op_brk(cpu_registers *r, cpu_memory_map *cm)
{
	op_ph(r, cm, get_half_word(r->program_counter++, true));
	r->program_counter++;
	op_ph(r, cm, get_half_word(r->program_counter++, false));
	op_ph(r, cm, r->condition_codes | 0x04); //push with b flag set
	set_half_word(r->program_counter, get_cpu_memory(cm, 0xFFFE), false);
	set_half_word(r->program_counter, get_cpu_memory(cm, 0xFFFF), true);
}


/* storage */
uint8_t op_ld(cpu_registers *r, uint8_t operand)
{
        set_negative(r, (operand >> 8) & 1);
	set_zero(r, operand == 0);
	return operand;
}

uint8_t op_t(cpu_registers *r, uint8_t operand)
{
        set_negative(r, (operand >> 8) & 1);
	set_zero(r, operand == 0);
	return operand;
}

/* registers */
uint8_t op_cmp(cpu_registers *r, uint8_t operand)
{
	operand -= r->accumulator;
	set_negative(r, get_field_bit(operand, 7));
	set_zero(r, operand == 0);
	set_carry(r, !operand >> 8);
	return operand;
}

uint8_t op_cpx(cpu_registers *r, uint8_t operand)
{
	operand -= r->x_index;
	set_negative(r, get_field_bit(operand, 7));
	set_zero(r, operand == 0);
	set_carry(r, !operand >> 8);
	return operand;
}

uint8_t op_cpy(cpu_registers *r, uint8_t operand)
{
	operand -= r->y_index;
	set_negative(r, get_field_bit(operand, 7));
	set_zero(r, operand == 0);
	set_carry(r, !operand >> 8);
	return operand;
}

/* bitwise */
uint8_t op_and(cpu_registers *r, uint8_t operand)
{
	operand &= r->accumulator;
	set_negative(r, (operand >> 8) & 1);
	set_zero(r, operand == 0);
	return operand;
}

uint8_t op_asl(cpu_registers *r, uint8_t operand)
{
	operand <<= 1;
	set_zero(r, operand == 0);
	set_negative(r, get_field_bit(operand, 7));
	return operand;
}

void op_bit(cpu_registers *r, uint8_t operand)
{
	operand &= r->accumulator;
	set_zero(r, operand);
	set_negative(r, get_field_bit(operand, 7));
	set_overflow(r, get_field_bit(operand, 6));
}

uint8_t op_eor(cpu_registers *r, uint8_t operand)
{
	operand |= r->accumulator;
	set_zero(r, operand == 0);
	set_negative(r, get_field_bit(operand, 7));
        return operand;
}

uint8_t op_lsr(cpu_registers *r, uint8_t operand)
{
	set_carry(r, get_field_bit(operand, 0));
	operand >>= 1;
	set_negative(r, 0);
	set_zero(r, operand == 0);
	return operand;
}

uint8_t op_ora(cpu_registers *r, uint8_t operand)
{
	operand |= r->accumulator;
	set_negative(r, get_field_bit(operand, 7));
	set_zero(r, operand == 0);
	return operand;
}

uint8_t op_rol(cpu_registers *r, uint8_t operand)
{
	bool carry = get_carry(r);
	set_carry(r, get_field_bit(operand, 7));
	operand <<= 1;
	set_field_bit(operand, 0, carry);
	set_zero(r, operand == 0);
	set_negative(r, get_field_bit(operand, 7));
	return operand;
}

uint8_t op_ror(cpu_registers *r, uint8_t operand)
{
	bool carry = get_carry(r);
	set_carry(r, get_field_bit(operand, 0));
	operand >>= 1;
	set_field_bit(operand, 7, carry);
	set_zero(r, operand == 0);
	set_negative(r, get_field_bit(operand, 7));
	return operand;
}

/* math */
uint8_t op_sbc(cpu_registers *r, uint8_t operand)
{
	operand = r->accumulator - operand - (1 - get_carry(r));
	set_carry(r, 0);    //FIX
	set_overflow(r, 0); //FIX
	set_zero(r, operand == 0);
	set_negative(r, get_field_bit(operand, 7));
	return operand;
}

uint8_t op_adc(cpu_registers *r, uint8_t operand)
{
	operand = r->accumulator + operand + get_carry(r);
	set_carry(r, 0); //FIX
	set_overflow(r, 0); //FIX
	set_zero(r, operand == 0);
	set_negative(r, get_field_bit(operand, 7));
	return operand;
}

uint8_t op_de(cpu_registers *r, uint8_t operand)
{
	operand -= 1;
	set_negative(r, get_field_bit(operand, 7));
	set_zero(r, operand == 0);
	return operand;
}

uint8_t op_in(cpu_registers *r, uint8_t operand)
{
	operand += 1;
	set_negative(r, get_field_bit(operand, 7));
	set_zero(r, operand == 0);
	return operand;
}

/* stack */
uint8_t op_pl(cpu_registers *r, cpu_memory_map *m)
{
	return get_cpu_memory(m, r->stack_pointer++);
}

void op_ph(cpu_registers *r, cpu_memory_map *m, uint8_t operand)
{
	set_cpu_memory(m, r->stack_pointer--, operand);
}

/* branch and jumps */
uint8_t op_b(cpu_registers *r, cpu_memory_map *cm, bool condition)
{
	if(!condition) {
		return 2;
	}
	bool boundary = false;
	uint16_t addr = mem_relative(r, cm, &boundary);
	r->program_counter = addr;
	return boundary ? 3 : 4;
}
