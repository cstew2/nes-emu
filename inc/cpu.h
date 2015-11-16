#ifndef CPU_H
#define CPU_H

#include <stdint.h>

static const double cpu_clock = 1.7897773f;

/* registers */
typedef struct {
	uint8_t accumulator; /* arithmatic and logic operations results stored */
	uint8_t x_index; /* counter or offset can be used to get the stack pointer */
	uint8_t y_index; /* counter or offset cannot be used to get the stack pointer */
	uint8_t status; /* 0-carry, 1-zero, 2-unused, 3-interupt, 4-break, 5-unused, 6-overflow, 7-negative */

	uint16_t program_counter;
	uint8_t stack_pointer; 
}cpu_registers;


/* function prototypes */


#endif
