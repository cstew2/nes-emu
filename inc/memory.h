#ifndef MEMORY_H
#define MEMORY_H


/* memory map */
typedef struct{
	uint8_t cpu_ram[2048]; /* $0000-$07FF */
	/* $0800-$17FF 3 mirrors of $0000-$07FF every 2048 bytes*/
	uint8_t ppu_registers[8]; /* $2000-$2007 */
	/* $2008-3FFF 8184 mirrors of PPU registers every 8 bytes*/
	uint8_t apu_io_registers[32]; /* $4000-$401F */
	uint8_t cartridge_space[49120]; /* $4020-$FFFF */
	
}memory_map;

/* function prototypes */


#endif
