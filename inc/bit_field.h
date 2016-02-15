#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>
#include <stdbool.h>

/* function prototype */
bool get_field_bit(const uint8_t byte, const uint8_t offset);
void set_field_bit(uint8_t byte, uint8_t offset, bool on);

uint8_t get_nibble(const uint8_t byte, const bool higher);
void set_nibble(uint8_t byte, uint8_t mask, bool higher);


#endif
