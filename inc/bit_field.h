#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>
#include <stdbool.h>

/* function prototype */
bool get_field_bit(const uint8_t byte, const uint8_t offset);
void set_field_bit(uint8_t byte, const uint8_t offset, const bool on);

uint8_t get_nibble(const uint8_t byte, const bool higher);
void set_nibble(uint8_t byte, const uint8_t mask, const bool higher);

uint8_t get_half_word(uint16_t word, const bool higher);
void set_half_word(uint16_t word, const uint8_t mask, const bool higher);

uint16_t combine(const uint8_t low, const uint8_t high);

#endif
