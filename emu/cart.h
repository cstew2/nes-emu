#ifndef CART_H
#define CART_H

#include <stdint.h>
#include <stdbool.h>

static const uint8_t INES_HEADER[] = {'N', 'E', 'S', 0x1A};

typedef struct{
	uint8_t header[4];
	uint8_t prg_count;
	uint8_t chr_count;
	bool prg_nvram_exists;
	bool mirror;
	bool trainer_exists;
	bool fourscreen; 
	uint8_t low_mapper;

	bool nes;
	bool vs_system;
	bool play_choice;
	bool extended_console; 

	uint8_t high_mapper;
	bool pal_cart; 
	bool bus_conflict;
	
	bool ines20;
	
	/* NES 2.0 */
	uint8_t submapper; 
	uint8_t super_high_mapper; 
	uint8_t prg_count_high;
	uint8_t chr_count_high; 
	uint8_t prg_ram_size; 
	uint8_t prg_nvram_size; 
	uint8_t chr_ram_size;
	uint8_t chr_nvram_size;
	
	uint8_t pal_and_ntsc; 
	bool ntsc_cart; 

	const uint8_t *trainer_rom;
	const uint8_t *cart_rom;
}cart;


cart *cart_init(const uint8_t *raw_file);
void cart_del(cart *c);
int cart_info(const cart *data);

#endif
