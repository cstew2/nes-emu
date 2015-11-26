#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cart.h"
#include "error.h"


uint8_t *open_rom_file(const char *filename)
{
	FILE *fp = NULL;
	size_t size;
	fp = fopen(filename, "rb");
	check_errno();
	
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	uint8_t *file_buffer = calloc(size, sizeof(uint8_t));
	fread(file_buffer, 1, size, fp);
	fclose(fp);

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
	
	r->mirror = raw_file[++pos] & 1; /* byte 6, bit 0 for mirror */
 	r->batt_ram = ((raw_file[pos]) >> 1) & 1; /* byte 6, bit 1 for battery ram */
	r->trainer =  ((raw_file[pos]) >> 2) & 1; /* byte 6, bit 2 for trainer */
	r->fourscreen = ((raw_file[pos]) >> 3) & 1; /* byte 6, bit 3 for fourscreen VRAM */
	r->low_mapper = (raw_file[pos] & 0xF0) >> 4; /* 4 high bits from byte 6 for the low bytes*/
		
	r->vs_system = raw_file[++pos] & 1; /* byte 7, bit 0 for vs_system */
	r->high_mapper = (raw_file[pos] & 0xF0) >> 4; /* four high bits from byte 7 for the high bytes */

	r->ram_bank_count = raw_file[++pos];
	r->pal_cart = raw_file[++pos];

	r->submapper = (raw_file[++pos] & 0xF0) >> 4;
	r->super_high_mapper = (raw_file[pos] & 0x0F) >> 4;
	
	r->prg_high = (raw_file[++pos] & 0x0F) >> 4;
	r->chr_high = (raw_file[pos] & 0xF0) >> 4;
	
	r->battery_prg_ram = (raw_file[++pos] & 0xF0) >> 4;
	r->non_battery_prg_ram = (raw_file[pos] & 0x0F) >> 4;
			     
	r->battery_chr_ram = (raw_file[++pos] & 0xF0) >> 4;
	r->non_battery_chr_ram = (raw_file[pos] & 0x0F) >> 4;
	
	r->pal_and_ntsc = (raw_file[++pos] >> 1) & 1;
	r->ntsc_cart = raw_file[pos] & 1;
		
	pos = 16; /* bytes 11-15 are zero */
	
	/* getting trainer data here */
		
	return r;
}

void rom_file_del(rom_file *r)
{
	
}

int dump_rom_file(const rom_file *data)
{
	printf("Header: %s\n"
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
