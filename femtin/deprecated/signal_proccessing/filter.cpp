/*
 * filter.cpp
 *
 *  Created on: 19 nov. 2014
 *      Author: Nico_user
 */

#include "filter.hpp"

#include "string.h"

//#include "FreeRTOS.h"
//#include "serial.h"

namespace filter
{

/// ------------------------------------------------------------------------------------------------
uint8_t low_pass_filter(uint32_t value)
{
	// http://en.wikipedia.org/wiki/Low-pass_filter#Continuous-time_low-pass_filters

	// I will use fixed point arithmetics with 5 decimals
	static const uint16_t decimal_offset = 10000;
	static uint32_t smoothed = 0;
	static bool square_wave_output = true;

//    const uint32_t input = digitalRead(dcf77_analog_sample_pin) * decimal_offset;
	const uint32_t input = value * decimal_offset;

	// compute N such that the smoothed signal will always reach 50% of
	// the input after at most 50 samples (=50ms).
	// N = 1 / (1- 2^-(1/50)) = 72.635907286
	const uint16_t N = 73;
	smoothed = ((N - 1) * smoothed + input) / N;

	// introduce some hysteresis

	if ((square_wave_output == false) == (smoothed >= decimal_offset / 2))
	{
		// smoothed value more >= 50% away from output
		// ==> switch output
		square_wave_output = !square_wave_output;

		// ==> max the smoothed value in order to introduce some
		//     hysteresis, this also ensures that there is no
		//     "infinite memory"
		smoothed = square_wave_output ? decimal_offset : 0;
	}

//    digitalWrite(filtered_dcf77_pin, square_wave_output);
	return square_wave_output;
}

/// ------------------------------------------------------------------------------------------------

void simple_moving_average(uint32_t value, uint32_t buff[], uint8_t size, uint32_t& sma)
{
	/// Computing value
	sma = sma - (buff[0] / size) + (value / size);

	/// Shift history
	memmove(&buff[0], &buff[1], sizeof(uint32_t) * (size - 1));

	buff[size - 1] = value;
}

/// ------------------------------------------------------------------------------------------------

/// real a:= dt / (RC + dt)
///  for i from 1 to n
///       y[i] := y[i-1] + a * (x[i] - y[i-1])

uint32_t exponential_moving_average(uint32_t value, uint32_t old_value, uint32_t alpha_10000)
{
	uint32_t ema = 0;
	static const uint32_t offset = 10000;
	/// ema1 = v1
	/// ema_t = alpha * val_t + (1 - alpha) * ema_t-1
	/// ema_t = (val_t - ema_t-1) alpha / 10000 + ema_t-1

	ema = value - old_value;
	ema *= alpha_10000;
	ema += (old_value * offset);
	ema /= offset;

	return ema;
}

/// ------------------------------------------------------------------------------------------------

bool hysteresis(uint32_t value, uint32_t threshold, bool& state)
{

	if ((state == false) == (value >= threshold))
	{
		state = !state;

		return true;
	}

	return false;
}

/// ------------------------------------------------------------------------------------------------

}
/// END OF FILE	====================================================================================
