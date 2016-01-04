#include <stdlib.h>

#include "nes.h"

int get_op_code(nes_emu e, uint8_t opcode, uint16_t operand)
{
	switch(opcode) {
		
	case 0x00: return brk(e->r); break;
	case 0x01: return ora_indx(e->r, operand); break;
	case 0x05: return ora_zp(e->r, operand); break;
	}
}
