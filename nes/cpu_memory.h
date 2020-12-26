#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdbool.h>

/* memory map */
typedef struct{
	uint8_t zero_page[256];              /* $0000-$00FF 256 bytes */
	uint8_t stack_memory[256];           /* $0100-$01FF  256 bytes */
	uint8_t cpu_ram[1536];               /* $0200-$07FF 1536 bytes */
	/* $0800-$1FFF 3 mirrors of $0000-$07FF every 2048 bytes*/
	
	/* ppu registers  $2000-$2007 8 bytes*/
	uint8_t *ppu_registers;
	/* $2008-3FFF 1023 mirrors of PPU registers every 8 bytes*/
	
	/* apu registers $4000-$4017 16 bytes */
	uint8_t *apu_registers;
	
        /* io registers $4018-$401F 16 bytes  */
	uint8_t *io_registers;
	
        /* cart address space $4020-$FFFF 49119 bytes */
	//$4020-$5FFF
	uint8_t *prg_ram;
	
	//$6000-$7FFF PRG RAM or NVRAM
	uint8_t *prg_nvram;
	
	//$8000-$FFFF PRG space
	//$8000-$BFFF
	uint8_t *prg_low_bank;
	//$0C000-$FFFF
	uint8_t *prg_high_bank;	
	
	/* 3 interrupts, at 0xFFFA, 0xFFFC, 0xFFFE */
	uint16_t *nmi_vector;
	uint16_t *reset_vector;
	uint16_t *irq_vector;
}cpu_memory_map;

/* function prototypes */
cpu_memory_map *cpu_memory_init(void);
void cpu_memory_term(cpu_memory_map *cm);

uint8_t get_cpu_memory(const cpu_memory_map *m, const uint16_t addr);
int set_cpu_memory(cpu_memory_map *m, const uint16_t addr, const uint8_t write);

#endif
