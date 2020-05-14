#include <stdlib.h>
#include <unistd.h>

#include "nes/nes.h"
#include "emu/debug.h"
#include "emu/error.h"
#include "emu/fileio.h"

nes_emu *init_nes_emu(cart *c)
{
	nes_emu *e = calloc(sizeof(nes_emu), 1);
	check_memory(e);
	e->c = c;
	e->r = cpu_registers_init();
	e->cm = cpu_memory_init();

	nrom_map(e->cm, e->c);
		
	return e;
}

int main_nes_loop(nes_emu *e)
{
 	bool quit = true;
	while(quit) {
		fetch(e->r, e->cm);
		execute(e->r, e->cm);
		e->r->ticks++;	
		log_msg(INFO, "pc:%X, a:%X, x:%X, y:%X, sp:%X, c:%X\n",
			 e->r->program_counter,
			 e->r->accumulator,
			 e->r->x_index,
			 e->r->y_index,
			 e->r->stack_pointer,
			 e->r->condition_codes);
		//sleep(1);
	}
	return 0;
}

cart *load_nes_rom(char *filename)
{
        uint8_t *raw_file = open_binary_file(filename);
	cart *c = cart_init(raw_file);
	
        cart_info(c);

	
	return c;
}

int start_nes_emu(char *filename)
{
	if(filename != NULL) {
		cart *c = load_nes_rom(filename);
		log_msg(INFO, "Succesfully loaded %s rom\n", filename);
		
		nes_emu *e = init_nes_emu(c);
		log_msg(INFO, "Succesfully initiated the NES cpu core\n");

		log_msg(INFO, "Main loop initialised\n");
		main_nes_loop(e);
		log_msg(INFO, "Main loop ended\n");
	}
	
	return 0;
}
