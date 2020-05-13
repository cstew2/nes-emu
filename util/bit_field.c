#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

bool get_field_bit(const uint8_t byte, const uint8_t offset)
{
	return ((byte >> offset) & 0x01);
}

void set_field_bit(uint8_t byte, uint8_t const offset, const bool on)
{
	byte &= (on << offset);
}

uint8_t get_nibble(const uint8_t byte, const bool higher)
{
	if(higher) {
		return (byte & 0xF0) >> 4;
	}
	else {
		return byte & 0x0F;
	}
	
}
void set_nibble(uint8_t byte, uint8_t const mask, const bool higher)
{
	if(higher) {
		byte = ((byte >> 4) & mask) << 4;
	}
	else {
		byte = byte & mask;
	}
}

uint8_t get_half_word(uint16_t word, const bool higher)
{
	if(higher) {
		return (word & 0xFF00) >> 8;
	}
	return (word & 0x00FF);
}

void set_half_word(uint16_t word, uint8_t const mask, const bool higher)
{
	if(higher) {
		word = ((word >> 8) & mask) << 8;
	}
	else {
		word = word & mask;
	}	
}

uint8_t get_bits(uint8_t byte, const uint8_t size, const uint8_t pos)
{
	return byte >> ((8 - size) - pos) & (256 - (1 << (8 - size)));
}

uint16_t combine(const uint8_t low, const uint8_t high)
{
	uint16_t w = high;
	return (w << 8) | low;
}
