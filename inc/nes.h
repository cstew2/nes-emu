#ifndef NES_H_
#define NES_H_

#include "cpu.h"
#include "cpu_memory.h"
#include "ppu.h"
#include "ppu_memory.h"
#include "apu.h"
#include "video.h"
#include "controller.h"
#include "cart.h"

typedef struct {
	rom_file *rf;

	/* hardware */
	cpu_registers *r;
	cpu_memory_map *cm;
	ppu_memory_map *pm;
		
}nes_emu;

/* funciton prototypes */
nes_emu *init_nes_emu(rom_file *rf);
int main_nes_loop(nes_emu *e);
rom_file *load_nes_rom(char *filename);
int start_nes_emu(char *filename);

#endif
