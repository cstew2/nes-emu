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
	char *filename = NULL;
	
	for(int i=1; i < argc; i++) {
		if(!strncmp(argv[i], "-d", 2)) {
			d_flag = true;
		}
		else if(!strncmp(argv[i], "-f", 2)) {
		       i++;
		       int len = strlen(argv[i])+1;
		       filename = malloc(sizeof(char) * len);
		       strncpy(filename, argv[i], len);
		}
		else if(!strncmp(argv[i], "--help", 6)) {
			print_help();
		}
	}
	
	if(d_flag) {
		log_init(true);
	}

	if(filename != NULL){
		//start term
		start_nes(filename);
	}
	else {
		log_msg(ERROR, "You need to supply a file path to a iNES rom in order to run in terminal mode.\n");
	}
	
	if(d_flag)
	{
	    	log_term();
	}
	free(filename);
	return 0;
}

void start_nes(char *filename)
{
	log_msg(INFO, "Starting nes emulator...\n");
	start_nes_emu(filename);

}

void print_help(void)
{
	printf("nes usage: nes [OPTIONS]...\n\n"
	       "Options\n"
	       "-d \t debug on\n"
	       "-f \t open \"FILE\"\n"
		"");
}
