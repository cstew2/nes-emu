#include <stdlib.h>

#include "cpu_memory.h"


cpu_memory_map *memory_init(void)
{
	cpu_memory_map *m = NULL;
	m = malloc(sizeof(cpu_memory_map));
	m->zero_page = NULL;
	m->stack_memory = NULL;
	m->cpu_ram = NULL;
	m->expansion_rom = NULL;
	m->save_ram = NULL;
	m->prg_rom_lower = NULL;
	m->prg_rom_upper = NULL;
	return m;
}

int load_cpu_rom(cpu_memory_map *m, uint8_t *prg_rom, bool upper, bool lower)
{
	
	if(upper) {
		m->prg_rom_upper = prg_rom;
	}
	if(lower) {
		m->prg_rom_lower = prg_rom;
	}

	return 0;
}
