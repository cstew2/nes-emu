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
	rom_file r;
	cpu_registers cr;
	cpu_memory_map cm;
       	ppu_registers pr;
	ppu_memory_map pm;
	
}nes_emu;

#endif
