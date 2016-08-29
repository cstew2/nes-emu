#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "emu/cart.h"
#include "emu/error.h"
#include "emu/debug.h"
#include "util/bit_field.h"

uint8_t *open_rom_file(const char *filename)
{
	check_memory(filename);
	FILE *f = NULL;
	size_t size;
	f = fopen(filename, "rb");
	check_errno();
	
	
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	uint8_t *file_buffer = calloc(size, sizeof(uint8_t));
	fread(file_buffer, 1, size, f);
	fclose(f);

	return file_buffer;
}

rom_file *rom_file_init(const uint8_t *raw_file)
{
	rom_file *r = malloc(sizeof(rom_file));
	int pos = 0;
	memcpy(r->header, raw_file, 4); /* bytes 0-3 for header */
	pos = 3;
	
	r->prg_count = raw_file[++pos]; /* byte 4 for prg rom*/
	r->chr_count = raw_file[++pos]; /* byte 5 for chr rom */
	
	r->mirror = get_field_bit(raw_file[++pos], 0); /* byte 6, bit 0 for mirror */
 	r->batt_ram = get_field_bit(raw_file[pos], 1); /* byte 6, bit 1 for battery ram */
	r->trainer =  get_field_bit(raw_file[pos], 2); /* byte 6, bit 2 for trainer */
	r->fourscreen = get_field_bit(raw_file[pos], 3); /* byte 6, bit 3 for fourscreen VRAM */
	r->low_mapper = get_nibble(raw_file[pos], true); /* 4 high bits from byte 6 for the low bytes*/
		
	r->vs_system = get_field_bit(raw_file[++pos], 0); /* byte 7, bit 0 for vs_system */
	r->high_mapper = (raw_file[pos] & 0xF0) >> 4; /* four high bits from byte 7 for the high bytes */

	r->ram_bank_count = raw_file[++pos];
	r->pal_cart = raw_file[++pos];

	r->submapper = get_nibble(raw_file[++pos], true);
	r->super_high_mapper = get_nibble(raw_file[pos], false);
	
	r->prg_high = get_nibble(raw_file[++pos], false);
	r->chr_high = get_nibble(raw_file[pos], true);
	
	r->battery_prg_ram = get_nibble(raw_file[++pos], true);
	r->non_battery_prg_ram = get_nibble(raw_file[pos], false);
			     
	r->battery_chr_ram = get_nibble(raw_file[++pos], true);
	r->non_battery_chr_ram = get_nibble(raw_file[pos], false);
	
	r->pal_and_ntsc = get_field_bit(raw_file[++pos], 1);
	r->ntsc_cart = get_field_bit(raw_file[pos], 0); /* byte 12 */
	

	pos = 16; /* bytes 14-15 are zero */
	
	return r;
}

void rom_file_del(rom_file *r)
{
	free(r);
	r = NULL;
}

int rom_file_info(const rom_file *data)
{
	log_info("Header: %s\n"
	       "16kB ROM pages: %i\n"
	       "8kB VROM pages: %i\n"
	       "Mirroring: %i\n"
	       "Battering RAM: %i\n"
	       "Trainer: %i\n"
	       "fourscreen: %i\n"
	       "Low Mapper bits: %X\n"
	       "VS-System: %i\n"
	       "High mapper bits: %X\n"
	       "Ram Bank count: %i\n"	       
	       "Pal Cart: %i\n"
	       "\niNES 2.0\n"
	       "Sub Mapper: %i\n"
	       "Super high Mapper: %i\n"
	       "Super High ROM pages: %i\n"
	       "Super High VROM pages: %i\n"
	       "Battery backed RAM: %i\n"
	       "Non-Battery backed RAM: %i\n"
	       "Battery backed VRAM: %i\n"
	       "Non-Battery backed VRAM: %i\n"
	       "PAL and NTSC: %i\n"
	       "NTSC: %i\n",
	       data->header,
	       data->prg_count,
	       data->chr_count,
	       data->mirror,
	       data->batt_ram,
	       data->trainer,
	       data->fourscreen,
	       data->low_mapper,
	       data->vs_system,
	       data->high_mapper,
	       data->ram_bank_count,
	       data->pal_cart,
	       data->submapper,
	       data->super_high_mapper,
	       data->prg_high,
	       data->chr_high,
	       data->battery_prg_ram,
	       data->non_battery_prg_ram,
	       data->battery_chr_ram,
	       data->non_battery_chr_ram,
	       data->pal_and_ntsc,
	       data->ntsc_cart);
	return 0;
}
