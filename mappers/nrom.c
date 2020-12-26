#include <stdlib.h>

#include "emu/debug.h"
#include "nes/cpu_memory.h"
#include "emu/cart.h"

#include "nrom.h"

void nrom_map(cpu_memory_map *m, cart *c)
{
	m->prg_ram = NULL;
	
	m->prg_nvram = calloc(0x4000, 1);
	m->prg_low_bank = c->cart_rom;

	if(c->prg_count == 1) {
		m->prg_high_bank = c->cart_rom;
	}
	else if(c->prg_count == 2) {
		m->prg_high_bank = c->cart_rom + 0x4000;
	}
	
	m->nmi_vector = (uint16_t *)(m->prg_high_bank + 0x3FFA);
	m->reset_vector = (uint16_t *)(m->prg_high_bank + 0x3FFC);
	m->irq_vector = (uint16_t *)(m->prg_high_bank + 0x3FFE);
}

void nrom_unmap(cpu_memory_map *m)
{
	free(m->prg_nvram);
	m->prg_low_bank = NULL;
	m->prg_high_bank = NULL;
	m->nmi_vector = NULL;
        m->reset_vector = NULL;
        m->irq_vector = NULL;
}
