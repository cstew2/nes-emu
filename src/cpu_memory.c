#include <stdlib.h>

#include "cpu_memory.h"
#include "debug.h"
#include "error.h"

cpu_memory_map *cpu_memory_init(void)
{
	cpu_memory_map *m = NULL;
	m = malloc(sizeof(cpu_memory_map));
	
	check_memory(m->prg_rom_lower = calloc(16384, sizeof(uint8_t)));
	check_memory(m->prg_rom_upper = calloc(16384, sizeof(uint8_t)));
	return m;
}

int load_cpu_rom(cpu_memory_map *m, uint8_t *prg_rom, bool upper, bool lower)
{
	if(upper) {
		log_info("INFO: load PRG ROM into upper bank");
		m->prg_rom_upper = prg_rom;
	}
	else if(lower) {
		log_info("INFO: load PRG ROM into lower bank");
		m->prg_rom_lower = prg_rom;
	}

	return 0;
}

uint8_t get_cpu_memory(cpu_memory_map *m, uint16_t addr)
{
	log_info("INFO: load cpu memory at address: %X\n", addr);
	if(addr < 8192) { /* main cpu ram */
		int i = addr % 2048;
		if(addr < 256) {
			return m->zero_page[i];
		}
		else if(addr > 256 && addr < 512) {
			return m->stack_memory[i];
		}
		else if(addr > 512 && addr < 2048) {
			return m->cpu_ram[i];
		}
	}
	else if(addr > 16416  && addr < 24576) { /* cartrige expansion rom */
		return m->expansion_rom[addr];
	}
	else if(addr > 24576 && addr < 32768) { /* save ram */
		return m->save_ram[addr];
	}
	else if(addr >  32768 && addr < 65535) { /* PRG ROM */
		if(addr < 49152) { /*lower bank */
			return m->prg_rom_lower[addr];
		}
		else { /* upper bank */
			return m->prg_rom_upper[addr];
		}
	}
	else {
		log_err("ERROR: bad address given for CPU memory read: %X\n", addr);
	}
	return 0; /* use a better value */
}

int set_cpu_memory(cpu_memory_map *m, uint16_t addr, uint8_t write)
{
	log_info("INFO: set cpu memory to %X at address: %X\n", write, addr);
	if(addr < 8192) { /* main cpu ram */
		int i = addr % 2048;
		if(addr < 256) {
			m->zero_page[i] = write;
		}
		else if(addr > 256 && addr < 512) {
			m->stack_memory[i] = write;
		}
		else if(addr > 512 && addr < 2048) {
			m->cpu_ram[i] = write;
		}
	}
	else if(addr > 16416  && addr < 24576) { /* cartrige expansion rom */
		m->expansion_rom[addr] = write;
	}
	else if(addr > 24576 && addr < 32768) { /* save ram */
		m->save_ram[addr] = write;
	}
	else if(addr >  32768 && addr < 65535) { /* PRG ROM */
		if(addr < 49152) { /*lower bank */
			m->prg_rom_lower[addr] = write;
		}
		else { /* upper bank */
			m->prg_rom_upper[addr] = write;
		}
	}
	else {
		log_err("ERROR: bad address given for CPU memory write:%X\n", addr);
	}
	return 0; /* use a better value */
}
