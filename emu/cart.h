#ifndef CART_H
#define CART_H

#include <stdint.h>
#include <stdbool.h>

static const uint8_t INES_HEADER[] = {'N', 'E', 'S', 0x1A};

typedef struct{
	uint8_t header[4];
	uint8_t prg_count;
	uint8_t chr_count;
	bool mirror; /* 1 for vertical, 0 for horizontal */
	bool batt_ram; /* battery backed ram at $6000-$7FFF */
	bool trainer; /* 1 for a 512 byte trainer at $7000-71FF */
	bool fourscreen; /* 1 for a four-screen VRAM layout */
	uint8_t low_mapper;

	bool nes;
	bool vs_system; /* 1 for VS-System cartridges */
	bool play_choice; /* 1 for playchoice 10 cartridges */
	bool extended_console; /* 1 for extended console cartridges */

	uint8_t high_mapper;
	bool pal_cart; /* 1 for pal, 0 for NTSC */
	
	bool ines20;
	
	/* NES 2.0 */
	uint8_t submapper; /* for conflicting mapps high bits of byte 8*/
	uint8_t super_high_mapper; /* bits 8-11 for the mapper low bits of byte 8 */
	uint8_t prg_high; /* 4 extra bits for prg_count low bits of byte 9*/
	uint8_t chr_high; /* 4 extra bits for chr_count high bits of byte 9*/
	uint8_t battery_prg_ram; /* quantity of battery backed prg ram high bits of byte 10*/
	uint8_t non_battery_prg_ram; /* quantity of non battery backed prg ram low bits of byte 10*/
	uint8_t battery_chr_ram;
	uint8_t non_battery_chr_ram;
	
	uint8_t pal_and_ntsc; /* 0 can work on both */
	bool ntsc_cart; /* 0 for NTSC, 1 for PAL *//*  */

	uint8_t *trainer_rom;
	uint8_t *prg_rom;
	uint8_t *chr_rom;	
}rom_file;


uint8_t *open_rom_file(const char *filename);
rom_file *rom_file_init(const uint8_t *raw_file);
void rom_file_del(rom_file *r);
int rom_file_info(const rom_file *data);



#endif
