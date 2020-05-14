#include "emu/debug.h"
#include "nes/cpu_memory.h"
#include "emu/cart.h"

#include "nrom.h"

void nrom_map(cpu_memory_map *m, cart *c)
{
	if(c->prg_count == 1) {
		m->prg_ram = calloc(0x2000, 1);
		m->prg_low_bank = c->cart_rom;
		m->prg_high_bank = c->cart_rom;
	}
	else if(c->prg_count == 2) {
		m->prg_ram = calloc(0x2000, 1);
		m->prg_low_bank = c->cart_rom;
		m->prg_high_bank = c->cart_rom + 0x4000;
	}
	else{
		log_msg(ERROR, "Something went wrong if the mapper is"
			       "%i==1 but PRG ROM Page count %i != 1 || 2",
			       c->low_mapper, c->prg_count);
	}
}
