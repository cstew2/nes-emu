#ifndef PPU_MEMORY_H
#define PPU_MEMORY_H

#include <stdint.h>

typedef struct {
	uint8_t pattern_table0[4096]; /* $0000-$0FFF */
	uint8_t pattern_table1[4096]; /* $1000-$1FFF */
	uint8_t name_table0[1024]; /* $2000-$23FF */
	uint8_t name_table1[1024]; /* $2400-$27FF */
	uint8_t name_table2[1024]; /* $2800-$2BFF */
	uint8_t name_table3[1024]; /* $2C00-$2FFF */
	/* $3000-$3EFF mirror of $2000-$2EFF*/
	uint8_t palette_ram[32]; /* $3F00-$3F1F */
	/* $3F20-$3FFF mirrors of $3F00-$3F1F */
}ppu_memory_map;




#endif
