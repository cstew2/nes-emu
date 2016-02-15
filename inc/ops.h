#ifndef OP_H
#define OP_H

#include <stdint.h>
#include "cpu.h"

int decode_op(uint8_t opcode, uint16_t operand);

#endif
