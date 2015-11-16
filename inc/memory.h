#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

/* memory map */
typedef struct{
	uint8_t *zero_page;              /* $0000-$00FF 256 bytes*/
	uint8_t *stack_memory;           /* $0100-$01FF  256 bytes*/
	uint8_t *cpu_ram;                /* $0200-$0FFF 1536 bytes */
	/* $0800-$17FF 3 mirrors of $0000-$07FF every 2048 bytes*/
	
	uint8_t ppu_registers[8];        /* $2000-$2007 8 bytes*/
	/* $2008-3FFF 8184 mirrors of PPU registers every 8 bytes*/
	uint8_t apu_io_registers[32];    /* $4000-$401F 32 bytes */
	
        uint8_t *expansion_rom;          /* $4020-5FFF 8160 */
	uint8_t *save_ram;               /* $6000-$7FFF 8192 */
	uint8_t *prg_rom_lower;          /* $8000-$BFFF 16384 bytes */
	uint8_t *prg_rom_upper;          /* $C000-$FFFA 16384 bytes */
	uint8_t nonmaskable_interupt[2]; /* $FFFA-$FFFB */
	uint8_t power_on_reset[2];       /* $FFFC-$FFFD */
	uint8_t break_handler[2];        /* $FFFE-$FFFF */
	
}memory_map;

/* function prototypes */
memory_map *memory_init();


#endif
