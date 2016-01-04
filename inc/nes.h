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

	/* hardware */
	cpu_registers cr;
	cpu_memory_map cm;
	ppu_memory_map pm;
		
}nes_emu;

/* funciton prototypes */
int get_op_code(nes_emu n, uint8_t opcode, uint16_t operand);

#endif
