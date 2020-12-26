#include <stdlib.h>

#include "nes/cpu_memory.h"
#include "emu/debug.h"
#include "emu/error.h"

cpu_memory_map *cpu_memory_init(void)
{
	cpu_memory_map *m = calloc(sizeof(cpu_memory_map), 1);
	check_memory(m);
	
	return m;
}

void cpu_memory_term(cpu_memory_map *cm)
{
	free(cm);
}

uint8_t get_cpu_memory(const cpu_memory_map *m, const uint16_t addr)
{
	log_msg(INFO, "load cpu memory at address $%X\n", addr);
	if(addr < 0x1FFF) { /* main cpu ram */
		uint16_t i = addr % 0x07FF;
		if(addr < 0x00FF) {
			return m->zero_page[i];
		}
		else if(addr >= 0x0100 && addr <= 0x01FF) {
			return m->stack_memory[i-0x100];
		}
		else if(addr > 0x0200 && addr <= 0x07FF) {
			return m->cpu_ram[i-0x200];
		}
	}
	else if(addr >= 0x2000 && addr <= 0x3FFF) {
		return m->ppu_registers[(addr - 0x2000) % 0x8];
	}
	else if(addr >= 0x4000 && addr <= 0x4017) {
		return m->apu_registers[(addr - 0x4000)];
	}
	else if(addr >= 0x4018 && addr <= 0x401F) {
		return m->io_registers[(addr - 0x4018)];
	}
	else if(addr >= 0x4020 && addr <= 0x6000) { 
		return m->prg_ram[addr - 0x4020];
	}
	else if(addr >= 0x6000 && addr <= 0x7FFF) {
		return m->prg_nvram[addr - 0x6000];
	}
	else if(addr >= 0x8000 && addr <= 0xBFFF) {
		return m->prg_low_bank[addr - 0x800];
	}
	else if(addr >= 0xC000) {
		return m->prg_high_bank[addr - 0xC000];
	}
	else {
		log_msg(ERROR, "bad address given for CPU memory read: %X\n", addr);
	}
	return 0;
}

int set_cpu_memory(cpu_memory_map *m, const uint16_t addr, const uint8_t write)
{
	log_msg(INFO, "set cpu memory at address $%X to $%X \n", addr, write);
	if(addr < 0x1FFF) { /* main cpu ram */
		uint16_t i = addr % 0x07FF;
		if(addr < 0x00FF) {
			m->zero_page[i] = write;
		}
		else if(addr >= 0x0100 && addr <= 0x01FF) {
			m->stack_memory[i-0x100] = write;
		}
		else if(addr > 0x0200 && addr <= 0x07FF) {
			m->cpu_ram[i-0x200] = write;
		}
	}
	else if(addr >= 0x2000 && addr <= 0x3FFF) {
		m->ppu_registers[(addr - 0x2000) % 0x8] = write;
	}
	else if(addr >= 0x4000 && addr <= 0x4017) {
		m->apu_registers[(addr - 0x4000)] = write;
	}
	else if(addr >= 0x4018 && addr <= 0x401F) {
		m->io_registers[(addr - 0x401F)] = write;
	}
	else if(addr >= 0x4020 && addr <= 0x6000) { 
		m->prg_ram[addr - 0x4020] = write;
	}
	else if(addr >= 0x6000 && addr <= 0x7FFF) {
		m->prg_nvram[addr - 0x6000] = write;
	}
	else if(addr >= 0x8000 && addr <= 0xBFFF) {
		m->prg_low_bank[addr - 0x800] = write;
	}
	else if(addr >= 0xC000) {
		m->prg_high_bank[addr - 0xC000] = write;
	}
	else {
		log_msg(ERROR, "bad address given for CPU memory write: %X\n", addr);
		return -1;
	}
	return 0;
}
