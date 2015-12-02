#ifndef APU_H
#define APU_H

#include <stdint.h>

typedef struct { /* $4000-$4017 */
	uint8_t square1_vol;
	uint8_t square1_sweep;
	uint8_t square1_low;
	uint8_t square1_high;
	
	uint8_t square2_vol;
	uint8_t square2_sweep;
	uint8_t square_low;
	uint8_t square_high;

	uint8_t tri;
	uint8_t unused1;
	uint8_t tri_low;
	uint8_t tri_high;
	
	uint8_t noise_vol;
	uint8_t unused2;
	uint8_t noise_low;
	uint8_t noise_high;

	uint8_t dmc_freq;
	uint8_t dmc_raw;
	uint8_t dmc_start;
	uint8_t dmc_len;
	
	/* $4014 DMA access to sprite memory */
	
	uint8_t sound_channel; /* bit 0-4 for channels 1-5 */
}apu_registers;

#endif
