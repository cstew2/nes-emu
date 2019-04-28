#include <stdlib.h>

#include "nes/apu.h"
#include "util/bit_field.h"

apu_registers *apu_init(void)
{
	apu_registers *ar = calloc(1, sizeof(apu_registers));
	
	return ar;
}

void apu_term(apu_registers *ar)
{
	free(ar);
}


/* pulse 1 */
//$4000
uint8_t get_pulse1_duty(apu_registers *ar)
{
	return get_bits(ar->pulse1_settings, 2, 6);
}

bool get_pulse1_length_counter(apu_registers *ar)
{
	return get_field_bit(ar->pulse1_settings, 5);
}

bool get_pulse1_constant_volume(apu_registers *ar)
{
	return get_field_bit(ar->pulse1_settings, 4);
}

uint8_t get_pulse1_envolope_volume(apu_registers *ar)
{
	return get_nibble(ar->pulse1_settings, false);
}

//$4001
bool get_pulse1_sweep_unit(apu_registers *ar)
{
	return get_field_bit(ar->pulse1_sweep, 7);
}

uint8_t get_pulse1_peroid(apu_registers *ar)
{
	return get_bits(ar->pulse1_sweep, 3, 3);
}

bool get_pulse1_negative(apu_registers *ar)
{
	return get_field_bit(ar->pulse1_sweep, 3);
}

uint8_t get_pulse1_shift_count(apu_registers *ar)
{
	return get_bits(ar->pulse1_sweep, 3, 0);
}

//$4002
uint8_t get_pulse1_timer_low(apu_registers *ar)
{
	return ar->pulse1_low_timer;
}

//$4003
uint8_t get_pulse1_length_counter_load(apu_registers *ar)
{
	return get_bits(ar->pulse1_counter_high_timer, 5, 3);
}

uint8_t get_pulse1_timer_high(apu_registers *ar)
{
	return get_bits(ar->pulse1_counter_high_timer, 3, 0);
}

/* pulse 2 */
//$4000
uint8_t get_pulse2_duty(apu_registers *ar)
{
	return get_bits(ar->pulse2_settings, 2, 6);
}

bool get_pulse2_length_counter(apu_registers *ar)
{
	return get_field_bit(ar->pulse2_settings, 5);
}

bool get_pulse2_constant_volume(apu_registers *ar)
{
	return get_field_bit(ar->pulse2_settings, 4);
}

uint8_t get_pulse2_envolope_volume(apu_registers *ar)
{
	return get_nibble(ar->pulse2_settings, false);
}

//$4001
bool get_pulse2_sweep_unit(apu_registers *ar)
{
	return get_field_bit(ar->pulse2_sweep, 7);
}

uint8_t get_pulse2_peroid(apu_registers *ar)
{
	return get_bits(ar->pulse2_sweep, 3, 3);
}

bool get_pulse2_negative(apu_registers *ar)
{
	return get_field_bit(ar->pulse2_sweep, 3);
}

uint8_t get_pulse2_shift_count(apu_registers *ar)
{
	return get_bits(ar->pulse2_sweep, 3, 0);
}

//$4002
uint8_t get_pulse2_timer_low(apu_registers *ar)
{
	return ar->pulse2_low_timer;
}

//$4003
uint8_t get_pulse2_length_counter_load(apu_registers *ar)
{
	return get_bits(ar->pulse2_counter_high_timer, 5, 3);
}

uint8_t get_pulse2_timer_high(apu_registers *ar)
{
	return get_bits(ar->pulse2_counter_high_timer, 3, 0);
}
