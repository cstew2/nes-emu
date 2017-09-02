#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "emu/main.h"
#include "emu/error.h"
#include "emu/debug.h"

#include "nes/nes.h"

#include "emu/gui.hxx"

int main(int argc, char **argv)
{
	bool d_flag = false;
	bool g_flag = false;

	char *filename = NULL;
	
	for(int i=1; i < argc; i++) {
		if(!strncmp(argv[i], "-d", 2)) {
			d_flag = true;
		}
		if(!strncmp(argv[i], "-g", 2)) {
			g_flag = true;
		}
		else if(!strncmp(argv[i], "-f", 2)) {
		       i++;
		       filename = malloc(sizeof(char) * strlen(argv[i]));
		       strncpy(filename, argv[i], strlen(argv[i]));
		}
		else if(!strncmp(argv[i], "--help", 6)) {
			print_help();
		}
	}
	
	if(d_flag) {
		debug_on = true;
		debug_init();
	}

	//main start point
	if(g_flag) {
		//start gui
		start_gui();
	}
	else if(filename != NULL){
		//start term
		start_nes(filename);
	}
	else {
		debug_message("You need to supply a file path to a iNES rom in order to run in terminal mode.\n"
			      "Or run in gui mode with \"-g\" to select one from a file browser.\n");
		printf("Run with -g for gui or supply a path to a rom file with -f\n");
	}
	if(d_flag)
	{
	    	debug_term();
	}
	free(filename);
	return 0;
}

void start_nes(char *filename)
{
	log_info("Starting nes emulator...\n");
	start_nes_emu(filename);

}

void print_help(void)
{
	printf("nes usage: nes [OPTIONS]...\n\n"
	       "Options\n"
	       "-d \t debug on\n"
	       "-o \t open \"FILE\"\n"
		"");
}
