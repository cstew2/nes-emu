#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>
#include <stdbool.h>

/* function prototype */
bool get_field_bit(const uint8_t byte, const uint8_t offset);
uint8_t set_field_bit(const uint8_t byte, const uint8_t offset, const bool on);

uint8_t get_nibble(const uint8_t byte, const bool higher);
uint8_t set_nibble(const uint8_t byte, const uint8_t mask, const bool higher);

uint8_t get_half_word(const uint16_t word, const bool higher);
uint8_t set_half_word(const uint16_t word, const uint16_t mask, const bool higher);

uint8_t get_bits(const uint8_t byte, const uint8_t offset, const uint8_t count);
uint16_t bytes_to_word(const uint8_t low, const uint8_t high);

#endif
