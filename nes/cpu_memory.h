#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

/* memory map */
typedef struct{
	uint8_t zero_page[256];              /* $0000-$00FF 256 bytes*/
	uint8_t stack_memory[256];           /* $0100-$01FF  256 bytes*/
	uint8_t cpu_ram[1536];                /* $0200-$0FFF 1536 bytes */
	/* $0800-$1FFF 3 mirrors of $0000-$07FF every 2048 bytes*/
	
	/* ppu registers  $2000-$2007 8 bytes*/
	/* $2008-3FFF 1023 mirrors of PPU registers every 8 bytes*/
	
	/* apu registers $4000-$4017 16 bytes */
        /* io registers $4018 -$401F 16 bytes  */
	
        uint8_t expansion_rom[8160];          /* $4020-5FFF 8160 */
	uint8_t save_ram[8192];               /* $6000-$7FFF 8192 */
	uint8_t *prg_rom_lower;          /* $8000-$BFFF 16384 bytes */
	uint8_t *prg_rom_upper;          /* $C000-$FFFA 16384 bytes */
	/* 3 interrupts, each 2 bytes at end of upper prg_rom bank */
}cpu_memory_map;

/* function prototypes */
cpu_memory_map *cpu_memory_init(void);
int load_cpu_rom(cpu_memory_map *m, uint8_t *prg_rom, bool upper, bool lower);

uint8_t get_cpu_memory(cpu_memory_map *m, uint16_t addr);
int set_cpu_memory(cpu_memory_map *m, uint16_t addr, uint8_t write);

#endif
