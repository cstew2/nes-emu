#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "cart.h"
#include "error.h"
#include "debug.h"


int main(int argc, char **argv)
{
	bool d_flag = false;
	bool o_flag = false;

	char *filename = calloc(sizeof(char), MAX_BUFFER);

	if(argc < 2) {
	        print_help();
		exit(-1);
	}
	
	for(int i=1; i < argc; i++) {
		if(!strncmp(argv[i], "-d", 2)) {
			d_flag = true;
		}
		else if(!strncmp(argv[i], "-o", 2)) {
		       o_flag = true;
		       i++;
		       strncpy(filename, argv[i], strlen(argv[i]));
		}
		else if(!strncmp(argv[i], "--help", 6)) {
			print_help();
		}
	}
		
	rom_file *data;
	uint8_t *raw;
	if(o_flag) {
		raw = open_rom_file(filename);
		data = rom_file_init(raw);
	}
	else{
		fprintf(stderr, "Error:no rom file given\n");
		return -1;
	}
	
	if(d_flag) {
		debug_on = true;
		rom_file_info(data);
	}

	
	
	free(filename);
	free(raw);
	free(data);
	return 0;
}

void print_help(void)
{
	printf("nes usage: nes [OPTIONS]...\n\n"
	       "Options\n"
	       "-d \t debug on\n"
	       "-o \t open \"FILE\"\n"
		"");
}
