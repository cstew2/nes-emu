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
	rom_file rf;

	/* hardware */
	cpu_registers r;
	cpu_memory_map cm;
	ppu_memory_map pm;
		
}nes_emu;

/* funciton prototypes */
int interpret_op(nes_emu *e, uint8_t opcode, uint16_t operand);
int get_opcode_bits(const uint8_t byte, const uint8_t offset);
int start_nes_emu(rom_file f);

#endif
