#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "cpu.h"
#include "memory.h"
#include "ppu.h"
#include "apu.h"
#include "video.h"
#include "controller.h"


int main(int argc, char **argv)
{
	bool d_flag = false;
	bool o_flag = false;

	char filename[MAX_BUFFER];
	
	for(int i=0; i < argc; i++) {
		if(strncmp(argv[i], "-d", 2)) {
			d_flag = true;
		}
		else if(strncmp(argv[i], "-o", 2)) {
		       o_flag = true;
		       i++;
		       memcpy(filename, argv[i], sizeof(argv[i]));
		}
	}

        rom_file *data;
	if(o_flag) {
		data = rom_file_init(open_rom_file(filename));
	}
	
	return 0;
}

char *open_rom_file(char filename[MAX_BUFFER])
{
	FILE *fp = NULL;
	size_t size;
	fp = fopen(filename, "rb");
	if(fp == NULL) {
		fprintf(stderr, "File not found");
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	char *file_buffer = malloc(size);
	file_buffer = fread(file_buffer, 1, size, fp);
	fclose(fp);
}

rom_file *rom_file_init(char *raw_file)
{
	rom_file *r = malloc(sizeof(rom_file));
	
	memcpy(r->header, raw_file, 4); /* first 4 bytes for the header */

}
