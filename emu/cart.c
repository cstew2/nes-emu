#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "emu/cart.h"
#include "emu/error.h"
#include "emu/debug.h"
#include "util/bit_field.h"

uint8_t *open_rom_file(const char *filename)
{
	log_msg(INFO, "%s\n", filename);
	
	check_memory(filename);
	FILE *f = NULL;
	size_t size = 0;
	f = fopen(filename, "rb");
	//check_errno();
	
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	uint8_t *file_buffer = calloc(size+1, sizeof(uint8_t));
	fread(file_buffer, 1, size, f);
	file_buffer[size] = '\0';
	fclose(f);

	return file_buffer;
}

rom_file *rom_file_init(const uint8_t *raw_file)
{
	rom_file *r = malloc(sizeof(rom_file));

	//load header
	memcpy(r->header, raw_file, 4); /* bytes 0-3 for header */
	
	r->prg_count = raw_file[4]; /* byte 4 for prg rom*/
	r->chr_count = raw_file[5]; /* byte 5 for chr rom */
	
	r->mirror = get_field_bit(raw_file[6], 0); /* byte 6, bit 0 for mirror */
 	r->batt_ram = get_field_bit(raw_file[6], 1); /* byte 6, bit 1 for battery ram */
	r->trainer =  get_field_bit(raw_file[6], 2); /* byte 6, bit 2 for trainer */
	r->fourscreen = get_field_bit(raw_file[6], 3); /* byte 6, bit 3 for fourscreen VRAM */
	r->low_mapper = get_nibble(raw_file[6], true); /* 4 high bits from byte 6 for the low bytes*/

	/* byte 7 bits 0 and 1 to choice a system */
	int t = get_field_bit(raw_file[7], 0) + get_field_bit(raw_file[7], 1);
	r->nes = (t == 0);
	r->vs_system = (t == 1);
	r->play_choice = (t == 2);
	r->play_choice = (t == 3);
	
	/* byte 7, bit 2,3 if = 2 bytes 8-10 are nes 2.0 */
	r->ines20 = get_field_bit(raw_file[7], 2) == 0 &&
		    get_field_bit(raw_file[7], 2) == 1;
	r->high_mapper = get_nibble(raw_file[7], true); /* four high bits from byte 7 for the high bytes */

	if(r->ines20) {
		//byte 8
		r->super_high_mapper = get_nibble(raw_file[8], false);
		r->submapper = get_nibble(raw_file[8], true);

		r->prg_high = get_nibble(raw_file[9], false);
		r->chr_high = get_nibble(raw_file[9], true);	

		r->non_battery_prg_ram = get_nibble(raw_file[10], false);
		r->battery_prg_ram = get_nibble(raw_file[10], true);

		r->non_battery_chr_ram = get_nibble(raw_file[11], false);
		r->battery_chr_ram = get_nibble(raw_file[11], true);
			
		//0=NTSC, 2=PAL, 1,3=dual compatible
		r->pal_and_ntsc = get_field_bit(raw_file[12], 0) + get_field_bit(raw_file[12], 1);
		
	}
	else {
		r->battery_prg_ram = raw_file[8]; /*  */

		r->pal_cart = get_field_bit(raw_file[9], 0);
		
		//0=NTSC, 2=PAL, 1,3=dual compatible
		r->pal_and_ntsc = get_field_bit(raw_file[10], 0) + get_field_bit(raw_file[10], 1);
		r->batt_ram = get_field_bit(raw_file[10], 4);
		//bus conflict byte 10 bit 5
	}

	uint8_t mapper = combine(r->low_mapper, r->high_mapper);
	

	
	return r;
}

void rom_file_del(rom_file *r)
{
	free(r);
	r = NULL;
}

int rom_file_info(const rom_file *data)
{
	log_msg(INFO,
		"Header: %s\n"
		"16kB ROM pages: %i\n"
		"8kB VROM pages: %i\n"
		"Mirroring: %i\n"
		"Battering RAM: %i\n"
		"Trainer: %i\n"
		"fourscreen: %i\n"
		"Low Mapper bits: %X\n"
		"VS-System: %i\n"
		"High mapper bits: %X\n"
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
