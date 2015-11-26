#ifndef OP_H
#define OP_H

#include <stdint.h>

typedef  enum {
	IMMEDIATE,
	ZERO_PAGE,
	ABSOLUTE,
	IMPLIED,
	ACCUMULATOR,
	INDEXED,
	ZERO_PAGE_INDEXED,
	INDIRECT,
	PRE_INDEXED_INDIRECT,
	POST_INDEXED_INDIRECT,
	RELATIVE
}addr_modes;

typedef  enum {
	X,
	Y,
	NONE
}index;

typedef struct {
	const uint8_t hex;
	const char *opcode;
	const addr_modes mode;
	const index i;
	const uint8_t length;
	const uint8_t cycle;
	const uint8_t extra_cycle;
}op;

static const op op_list[] = {
	{0x00, "BRK", IMPLIED,           NONE, 1, 2, 0},
	{0x01, "ORA", INDIRECT,          X,    2, 6, 0},
	{0x05, "ORA", ZERO_PAGE,         NONE, 2, 3, 0},
	{0x06, "ASL", ZERO_PAGE,         NONE, 1, 7, 0},
	{0x08, "PHP", IMPLIED,           NONE, 1, 3, 0},
	{0x09, "ORA", IMMEDIATE,         NONE, 2, 2, 0},
	{0x0A, "ASL", ACCUMULATOR,       NONE, 1, 2, 0},
	{0x0D, "ORA", ABSOLUTE,          NONE, 3, 4, 0},
	{0x0E, "ASL", ABSOLUTE,          NONE, 3, 6, 0},
	{0x10, "BPL", RELATIVE,          Y,    2, 2, 1},
	{0x11, "ORA", INDIRECT,          X,    2, 5, 1},
	{0x15, "ORA", ZERO_PAGE_INDEXED, X,    2, 4, 0},
	{0x16, "ASL", ZERO_PAGE_INDEXED, X,    2, 6, 0},
	{0x18, "CLC", IMPLIED,           NONE, 1, 2, 0},
	{0x19, "ORA", ABSOLUTE,          Y,    3, 4, 1},
	{0x1D, "ORA", ABSOLUTE,          X,    3, 4, 1},
	{0x1E, "ASL", ABSOLUTE,          X,    3, 7, 0},
	{0X20, "JSR", ABSOLUTE, NONE, 3, 6, 0}
	
};

#endif
