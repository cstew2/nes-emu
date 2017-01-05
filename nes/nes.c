#include <stdlib.h>

#include "nes/nes.h"
#include "emu/debug.h"
#include "emu/error.h"

#include "emu/gui.hxx"

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
 	bool quit = true;
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
	if(filename != NULL) {
		rom_file *rf = load_nes_rom(filename);
		log_info("Succesfully loaded %s rom\n", filename);
		
		nes_emu *e = init_nes_emu(rf);
		log_info("Succesfully initiated the NES cpu core\n");

		log_info("Main loop initialised\n");
		main_nes_loop(e);
		log_info("Main loop ended\n");
	}
	
	return 0;
}
