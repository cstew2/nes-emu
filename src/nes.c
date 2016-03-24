#include <stdlib.h>

#include "nes.h"

int start_nes_emu(rom_file *rf)
{
	nes_emu *e = malloc(sizeof(nes_emu));
	e->rf = rf;
	e->r = cpu_registers_init();
	e->cm = cpu_memory_init();
}

int main_nes_loop(nes_emu *e)
{
	
}
