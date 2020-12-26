#ifndef __6502_H__
#define __6502_H__

#include <stdint.h>

enum addressing_mode {
	NONE,
	IMPLIED,
	IMMEDIATE,
	ABSOLUTE,
	ZERO_PAGE,
	RELATIVE,
	INDIRECT,
	ZERO_PAGE_X,
	ZERO_PAGE_Y,
	INDIRECT_X,
	INDIRECT_Y,
	ABSOLUTE_X,
	ABSOLUTE_Y,
};

enum mnemonic_enum {
	ADC,
	AHX,
	ALR,
	ANC,
	AND,
	ASL,
	ARR,
	AXS,
	BCC,
	BCS,
	BEQ,
	BIT,
	BMI,
	BNE,
	BPL,
	BRK,
	BVC,
	BVS,
	CLC,
	CLD,
	CLI,
	CLV,
	CMP,
	CPX,
	CPY,
	DCP,
	DEC,
	DEX,
	DEY,
	EOR,
	INC,
	INX,
	INY,
	ISC,
	JMP,
	JSR,
	KIL,
	LAS,
	LAX,
	LDA,
	LDX,
	LDY,
	LSR,
	NOP,
	ORA,
	PHA,
	PHP,
	PLA,
	PLP,
	RLA,
	ROL,
	ROR,
	RRA,
	RTI,
	RTS,
	SAX,
	SBC,
	SEC,
	SED,
	SEI,
	SHY,
	SHX,
	SLO,
	SRE,
	STA,
	STP,
	STX,
	STY,
	TAS,
	TAX,
	TAY,
	TSX,
	TXA,
	TXS,
	TYA,
	XAA
};

struct opcode_def {
	const uint8_t opcode;
	const char * const mnemonic_string;
	const enum mnemonic_enum mnemonic;
	const int size;
	const int cycles;
	const enum addressing_mode mode;
};

extern const struct opcode_def nes_opcodes[];

#endif
