#ifndef APU_H
#define APU_H

#include <stdint.h>
#include <stdbool.h>


typedef struct { /* $4000-$4017 */
	/* pulse 1 channel */
	uint8_t pulse1_settings;
	uint8_t pulse1_sweep;
	uint8_t pulse1_low_timer;
	uint8_t pulse1_counter_high_timer;
	
	/* pulse 2 channel */
	uint8_t pulse2_settings;
	uint8_t pulse2_sweep;
	uint8_t pulse2_low_timer;
	uint8_t pulse2_counter_high_timer;

	/* triangle channel */
	uint8_t triangle_settings;
	uint8_t triangle_low_timer;
	uint8_t triangle_counter;

	/* noise channel */
	uint8_t noise_settings;
	uint8_t noise_loop_period;
	uint8_t noise_length_high_timer;

	/* 4015 DMA */
	
	/* DMC channel */
	uint8_t dmc_freq;
	uint8_t dmc_direct_load;
	uint8_t dmc_address;
	uint8_t dmc_length;
	
}apu_registers;

apu_registers *apu_init(void);
void apu_term(apu_registers *ar);



/* pulse 1 */
//$4000
uint8_t get_pulse1_duty(apu_registers *ar);
bool get_pulse1_length_counter(apu_registers *ar);
bool get_pulse1_constant_volume(apu_registers *ar);
uint8_t get_pulse1_envolope_volume(apu_registers *ar);
//$4001
bool get_pulse1_sweep_unit(apu_registers *ar);
uint8_t get_pulse1_peroid(apu_registers *ar);
bool get_pulse1_negative(apu_registers *ar);
uint8_t get_pulse1_shift_count(apu_registers *ar);
//$4002
uint8_t get_pulse1_timer_low(apu_registers *ar);
//$4003
uint8_t get_pulse1_length_counter_load(apu_registers *ar);
uint8_t get_pulse1_timer_high(apu_registers *ar);

/* pulse 2 */
//$4004
uint8_t get_pulse2_duty(apu_registers *ar);
bool get_pulse2_length_counter(apu_registers *ar);
bool get_pulse2_constant_volume(apu_registers *ar);
uint8_t get_pulse2_envolope_volume(apu_registers *ar);
//$4005
bool get_pulse2_sweep_unit(apu_registers *ar);
uint8_t get_pulse2_peroid(apu_registers *ar);
bool get_pulse2_negative(apu_registers *ar);
uint8_t get_pulse2_shift_count(apu_registers *ar);
//$4006
uint8_t get_pulse2_timer_low(apu_registers *ar);
//$4007
uint8_t get_pulse2_length_counter_load(apu_registers *ar);
uint8_t get_pulse2_timer_high(apu_registers *ar);

/* triangle */
//$4008
bool get_triangle_length_counter(apu_registers *ar);
uint8_t get_triangle_reload_value(apu_registers *ar);
//$400A
uint8_t get_triangle_timer_low(apu_registers *ar);
//$400B
uint8_t get_triangle_length_counter_load(apu_registers *ar);
uint8_t get_triangle_timer_high(apu_registers *ar);

/* noise */
//$400C
bool get_noise_length_counter(apu_registers *ar);
bool get_noise_constant_volume(apu_registers *ar);
uint8_t get_envelope_volume(apu_registers *ar);
//$400E
bool get_noise_loop_noise(apu_registers *ar);
uint8_t get_noise_noise_period(apu_registers *ar);
//$400F
uint8_t get_noise_length_counter_load(apu_registers *ar);

/* DMC */
//$4010
bool get_DMC_IRQ(apu_registers *ar);
bool get_DMC_loop_sample(apu_registers *ar);
uint8_t frequency_index(apu_registers *ar);
//$4011
uint8_t get_DMC_direct_load(apu_registers *ar);
//$4012
uint8_t get_DMC_sample_address(apu_registers *ar);
//$4013
uint8_t get_DMC_sample_length(apu_registers *ar);

/* other */
//$4015
bool get_DMC_interrupt(apu_registers *ar);
bool get_frame_interrupt(apu_registers *ar);
bool get_DMC_active(apu_registers *ar);
bool get_noise_enable(apu_registers *ar);
bool get_triangle_enable(apu_registers *ar);
bool get_pulse2_enable(apu_registers *ar);
bool get_pulse1_enable(apu_registers *ar);

//$4017
bool get_frame_counter_mode(apu_registers *ar);
bool get_frame_inhibit_flag(apu_registers *ar);

#endif
