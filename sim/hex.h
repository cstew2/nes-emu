#ifndef HEX_H
#define HEX_H

#include <stdint.h>
#include <stdbool.h>

static bool hex_open = false;

char *rom_to_hex(uint8_t *rom);

#endif
