#include <stdlib.h>

#include "nes.h"
#include "debug.h"
#include "error.h"

nes_emu *init_nes_emu(rom_file *rf)
{
	nes_emu *e = malloc(sizeof(nes_emu));
	check_memory(e);
	e->rf = rf;
	e->r = cpu_registers_init();
	e->cm = cpu_memory_init();
	return e;
}

int main_nes_loop(nes_emu *e)
{
 	bool quit = false;
	while(quit) {
		fetch(e->r, e->cm);
		execute(e->r, e->cm);
		e->r->ticks++;
	}
	return 0;
}

rom_file *load_nes_rom(char *filename)
{
	rom_file *rom;
	uint8_t *raw;
       
	raw = open_rom_file(filename);
	rom = rom_file_init(raw);
	
	if(debug_on) {
		rom_file_info(rom);
	}
	
	return rom;
}

int start_nes_emu(char *filename)
{
	rom_file *rf = load_nes_rom(filename);
	log_info("Succesfully loaded %s rom", filename);
	nes_emu *e = init_nes_emu(rf);
	log_info("succesfully initiated the NES cpu core");
		
	main_nes_loop(e);

	return 0;
}
