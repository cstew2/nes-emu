#include "ops.h"

/* System */
void op_brk(cpu_registers *r, cpu_memory_map *cm)
{
	op_ph(r, cm, get_half_word(++r->program_counter, true));
	r->program_counter++;
	op_ph(r, cm, get_half_word(++r->program_counter, false));
	op_ph(r, cm, r->condition_codes | 0x04); //push with b flag set
	set_half_word(r->program_counter, get_cpu_memory(cm, 0xFFFE), false);
	set_half_word(r->program_counter, get_cpu_memory(cm, 0xFFFF), true);
}


/* storage */
uint8_t op_ld(cpu_registers *r, uint16_t operand)
{
	set_field_bit(r->condition_codes, 8, operand < 0x7F);
	set_field_bit(r->condition_codes, 1, operand == 0);
	return operand;
}

uint8_t op_st(cpu_registers *r, uint16_t operand)
{
	
}

uint8_t op_t(cpu_registers *r, uint16_t operand)
{

}
