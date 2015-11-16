#ifndef OP_H
#define OP_H

typedef enum {
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

typedef struct {
	uint8_t hex;
	char *opcode;
	addr_modes mode;
	uint8_t size;
	uint8_t cycle;
}op;

static const op op_list[] = {
	{0x00, "BRK", IMPLIED, 1, 7}, {0x01, "ORA", INDIRECT, 2, 6},
	
};

#endif
