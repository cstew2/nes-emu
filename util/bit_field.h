#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include <stdint.h>


/* function prototype */
uint8_t get_field_bit(uint8_t byte, uint8_t offset);
uint8_t set_field_bit(uint8_t byte, uint8_t offset);

uint8_t get_nibble(uint8_t byte, uint8_t offset);
uint8_t set_nibble(uint8_t byte, uint8_t offset);
#endif
