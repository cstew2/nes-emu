#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool get_field_bit(uint8_t byte, uint8_t offset)
{
	return ((byte >> offset) & 1);
}

void set_field_bit(uint8_t byte, uint8_t offset, bool on)
{
	byte = ((byte >> offset) & on) << offset;
}

uint8_t get_nibble(uint8_t byte, bool higher)
{
	if(higher) {
		return (byte & 0xF0) >> 4;
	}
	else {
		return byte & 0x0F;
	}
	
}
void set_nibble(uint8_t byte, uint8_t mask, bool higher)
{
	if(higher) {
		byte = ((byte >> 4) & mask) << 4;
	}
	else {
		byte = byte & mask;
	}
}
