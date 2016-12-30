#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sim/asm.h"

char *rom_to_asm(uint8_t *rom)
{
	char *string = malloc(sizeof(rom));
	size_t i = 0;
	while(i < sizeof(rom)) {
		strcat(string, table[rom[i]].instruction);
		uint8_t operand_size = table[rom[i]].bytes;
		if(operand_size > 0 ) {
			strcat(string, rom[i+1]);
			if(operand_size > 1) {
				strcat(string, rom[i+2]);
			}
		}
		i += operand_size;
	}
	return string;
}

