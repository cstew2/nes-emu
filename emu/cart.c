#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "emu/cart.h"
#include "emu/error.h"
#include "emu/debug.h"
#include "util/bit_field.h"

cart *cart_init(const uint8_t *raw_file)
{
	cart *r = calloc(sizeof(cart), 1);
	check_memory(r);

	//load header
	memcpy(r->header, raw_file, 4); /* bytes 0-3 for header */
	
	r->prg_count = raw_file[4]; /* byte 4 for prg rom*/
	r->chr_count = raw_file[5]; /* byte 5 for chr rom */
	
	r->mirror = get_field_bit(raw_file[6], 0); /* byte 6, bit 0 for mirror */
 	r->prg_nvram_exists = get_field_bit(raw_file[6], 1); /* byte 6, bit 1 for non-volatile ram */
	r->trainer_exists =  get_field_bit(raw_file[6], 2); /* byte 6, bit 2 for trainer */
	r->fourscreen = get_field_bit(raw_file[6], 3); /* byte 6, bit 3 for fourscreen VRAM */
	r->low_mapper = get_nibble(raw_file[6], true); /* 4 high bits from byte 6 for the low bytes*/

	/* byte 7 bits 0 and 1 to choice a system */
	uint8_t t = get_bits(raw_file[7], 0, 2);
	r->nes = (t == 0);
	r->vs_system = (t == 1);
	r->play_choice = (t == 2);
	r->play_choice = (t == 3);
	
	/* byte 7, bit 2,3 if = 2 bytes 8-10 are nes 2.0 */
	r->ines20 = get_field_bit(raw_file[7], 2) == 0 &&
		    get_field_bit(raw_file[7], 3) == 1;
	r->high_mapper = get_nibble(raw_file[7], true); /* four high bits from byte 7 for the high bytes */

	if(r->ines20) {
		//byte 8
		r->super_high_mapper = get_nibble(raw_file[8], false);
		r->submapper = get_nibble(raw_file[8], true);
		
		//byte 9
		r->prg_count_high = get_nibble(raw_file[9], false);
		r->chr_count_high = get_nibble(raw_file[9], true);	

		//byte 10
		r->prg_ram_size = get_nibble(raw_file[10], false);
		r->prg_nvram_size = get_nibble(raw_file[10], true);

		//byte 11
		r->chr_ram_size = get_nibble(raw_file[11], false);
		r->chr_nvram_size = get_nibble(raw_file[11], true);

		//byte 12
		//0=NTSC, 1=PAL, 2=multi-region, 3=dendy
		r->pal_and_ntsc = get_bits(raw_file[12], 0, 2);
		
	}
	else {
		//byte 8
		r->prg_nvram_size = raw_file[8] * 8192; 

		//byte 9
		//0=NTSC, 1=PAL
		r->pal_cart = get_field_bit(raw_file[9], 0);

		//byte 10
		//0=NTSC, 2=PAL 1,3=multi-region
		r->pal_and_ntsc = get_bits(raw_file[10], 0, 2);
		r->prg_nvram_exists = get_field_bit(raw_file[10], 4); 
		r->bus_conflict = get_field_bit(raw_file[10], 5);
	}

	if(r->trainer_exists) {
		r->trainer_rom = raw_file + 0x10;
		r->cart_rom = raw_file + 0x210;
	}
	else{
		r->trainer_rom = NULL;
		r->cart_rom = raw_file + 0x10;
	}
	return r;
}

void cart_del(cart *c)
{
	free(c);
}

int cart_info(const cart *data)
{
	log_msg(INFO,
		"Cart Header:\n"
		"Magic Number: %s\n"
		"16kB PRG ROM pages: %i\n"
		"8kB CHR ROM pages: %i\n"
		"Mirroring: %i\n"
		"Program Non-Volatile RAM: %i\n"
		"Trainer: %i\n"
		"fourscreen: %i\n"
		"Low Mapper bits: %X\n"
		"VS-System: %i\n"
		"High mapper bits: %X\n"
		"iNES 2.0: %i\n"
		"Sub Mapper: %i\n"
		"Super High Mapper: %i\n"
		"Super High ROM pages: %i\n"
		"Super High VROM pages: %i\n"
		"PRG Ram Size: %i\n"
		"PRG NVRAM Size: %i\n"
		"CHR RAM SIZE: %i\n"
		"CHR NVRAM SIZE: %i\n"
		"Pal Cart: %i\n"
		"PAL and NTSC: %i\n"
		"NTSC: %i\n",
		data->header,
		data->prg_count,
		data->chr_count,
		data->mirror,
		data->prg_nvram_exists,
		data->trainer_exists,
		data->fourscreen,
		data->low_mapper,
		data->vs_system,
		data->high_mapper,
		data->ines20,
		data->submapper,
		data->super_high_mapper,
		data->prg_count_high,
		data->chr_count_high,
		data->prg_ram_size,
		data->prg_nvram_size,
		data->chr_ram_size,
		data->chr_nvram_size,
		data->pal_cart,
		data->pal_and_ntsc,
		data->ntsc_cart);
	return 0;
}
