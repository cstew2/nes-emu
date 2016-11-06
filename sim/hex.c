#include <stdlib.h>

#include "sim/hex.h"

char *rom_to_hex(uint8_t *rom)
{
	char *string = malloc(sizeof(rom));
	memcpy(string, rom, sizeof(rom));
	return string;
}
