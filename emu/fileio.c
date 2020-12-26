#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "emu/debug.h"
#include "emu/fileio.h"

uint8_t *open_binary_file(const char *filename)
{
	log_msg(INFO, "Reading %s\n", filename);
	
	if(!filename) {
		log_msg(ERROR, "null filename passed");
	}
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
