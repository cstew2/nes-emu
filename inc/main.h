#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

static const int MAX_BUFFER = 128;
static const uint8_t INES_HEADER[] = {'N', 'E', 'S', 0x1A};

typedef struct{
	struct rom_data{
		uint8_t header[4];
		uint8_t prg_count;
		uint8_t chr_count;
		bool mirror; /* 1 for vertical, 0 for horizontal */
		bool batt_ram; /* battery backed ram at $6000-$7FFF */
		bool trainer; /* 1 for a 512 byte trainer at $7000-71FF */
		bool fourscreen; /* 1 for a four-screen VRAM layout */
		uint8_t low_mapper_type; 
		bool vs_system; /* 1 for VS-System cartridges */
		uint8_t high_mapper_types;
		uint8_t ram_bank_count; /* number of 8kb RAM banks, 0 means 1 bank */
		bool pal_cart; /* 1 for pal, 0 for NTSC */
		uint8_t *prg_rom[65536]; /* 64kb pages*/
		uint8_t *chr_rom[8192]; /* 8kb pages*/
		uint8_t *title; /* 128kb */
	};
	int prg_pages;
	int chr_pages;
	
}rom_file;

/* function prototypes */
char *open_rom_file(char filename[MAX_BUFFER]);
rom_file *rom_file_init(char *raw_file);


#endif
