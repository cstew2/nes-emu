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

uint8_t get_cpu_memory(const cpu_memory_map *m, const uint16_t addr)
{
	log_msg(INFO, "load cpu memory at address: %X\n", addr);
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
		return m->io_registers[(addr - 0x401F)];
	}
	else if(addr >= 0x4020 && addr <= 0xFFFF ) { 
		return m->cart_space[addr-0x4020];
	}
	else {
		log_msg(ERROR, "bad address given for CPU memory read: %X\n", addr);
	}
	return 0;
}

int set_cpu_memory(cpu_memory_map *m, const uint16_t addr, const uint8_t write)
{
	log_msg(INFO, "set cpu memory to %X at address: %X\n", write, addr);
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
	else if(addr >= 0x4020 && addr <= 0xFFFF ) { 
		m->cart_space[addr-0x4020] = write;
	}
	else {
		log_msg(ERROR, "bad address given for CPU memory write: %X\n", addr);
		return -1;
	}
	return 0;
}
