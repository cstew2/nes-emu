#include <stdlib.h>

#include "bit_field.h"
#include "cpu_memory.h"
#include "ops.h"

int brk(cpu_registers *r)
{
	//does nothing
	return 2;
}

int ora_imm(cpu_registers *r, uint8_t operand)
{
	set_accumulator(r, operand | get_accumulator(r));

	set_negative(r, get_accumulator(r) > 0x7F);
	set_zero(r, get_accumulator(r) == 0);
		
	return 2;
}

int ora_zp(cpu_registers *r, uint8_t operand, cpu_memory_map *m)
{
	set_accumulator(r, get_cpu_memory(m, operand) | get_accumulator(r));
	set_negative(r, get_accumulator(r) > 0x7F);
	set_zero(r, get_accumulator(r) == 0);
	
	return 3;
}

int ora_zpx(cpu_registers *r, uint8_t operand, cpu_memory_map *m)
{
	set_accumulator(r, get_cpu_memory(m, operand + get_x_index(r)) | get_accumulator(r));
	set_negative(r, get_accumulator(r) > 0x7F);
	set_zero(r, get_accumulator(r) == 0);

	return 4;
}

int ora_abs(cpu_registers *r, uint16_t operand)
{
	set_accumulator(r, get_cpu_memory(m, operand) | get_accumulator(r));
	set_negative(r, get_accumulator(r) > 0x7F);
	set_zero(r, get_accumulator(r) == 0);
	
	return 4;
}

int ora_absx(cpu_registers *r, uint16_t operand)
{
	uint16_t i = op + get_x_index(r);
	set_accumulator(r, get_cpu_memory(m, i) | get_accumulator);
	set_negative(r, get_accumulator(r) > 0x7F);
	set_zero(r, get_accumulator(r) == 0);

	if((i & 0xFF00) - (get_program_counter(r) & 0xFF00)) {
		return 5;
	}
	else {
		return 4;
	}	
}
int ora_absy(cpu_registers *r, uint16_t operand)
{
	
}
int ora_indx(cpu_registers *r, uint8_t operand)
{

}
int ora_indy(cpu_registers *r, uint8_t operand)
{

}
