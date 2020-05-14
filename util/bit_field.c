#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

bool get_field_bit(const uint8_t byte, const uint8_t offset)
{
	return ((byte >> offset) & 0x01);
}

uint8_t set_field_bit(const uint8_t byte, uint8_t const offset, const bool on)
{
        if(on) {
		return byte | (0x01 << offset);
	}
	return byte | 0xFE << offset;
}

uint8_t get_nibble(const uint8_t byte, const bool higher)
{
	if(higher) {
		return (byte & 0xF0) >> 4;
	}
	return byte & 0x0F;
}
uint8_t set_nibble(const uint8_t byte, uint8_t const mask, const bool higher)
{
	if(higher) {
		return byte | ((0xF0 & mask) << 4);
	}
	return byte | (0x0F & mask);
}

uint8_t get_half_word(const uint16_t word, const bool higher)
{
	if(higher) {
		return (word & 0xFF00) >> 8;
	}
	return (word | 0x00FF);
}

uint16_t set_half_word(const uint16_t word, uint16_t const mask, const bool higher)
{
	if(higher) {
		return word | ((0x00FF & mask) << 8);
	}
	return word | (0x00FF & mask);
}

uint8_t get_bits(const uint8_t byte, const uint8_t offset, const uint8_t count)
{
	return (8-(offset+count)) << (byte << (offset+count));
}

uint16_t bytes_to_word(const uint8_t low, const uint8_t high)
{
	uint16_t w = high;
	return (w << 8) | low;
}
