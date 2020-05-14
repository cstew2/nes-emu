#ifndef NES_H
#define NES_H

#include "nes/cpu.h"
#include "nes/cpu_memory.h"
#include "nes/ppu.h"
#include "nes/ppu_memory.h"
#include "nes/apu.h"
#include "emu/video.h"
#include "emu/controller.h"
#include "emu/cart.h"

typedef struct {
	cart *c;

	/* hardware */
	cpu_registers *r;
	cpu_memory_map *cm;
	ppu_memory_map *pm;
		
}nes_emu;

/* funciton prototypes */
nes_emu *init_nes_emu(cart *c);
int main_nes_loop(nes_emu *e);
cart *load_nes_rom(char *filename);
int start_nes_emu(char *filename);

#endif
