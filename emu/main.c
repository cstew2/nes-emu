#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "emu/main.h"
#include "emu/error.h"
#include "emu/debug.h"

#include "nes/nes.h"

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
	
	if(d_flag) {
		debug_on = true;
	}

	//main start point
	start_nes_emu(filename);
	
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
