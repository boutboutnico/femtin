/*
 * filter.hpp
 *
 *  Created on: 19 nov. 2014
 *      Author: Nico_user
 */

#ifndef FILTER_HPP_
#define FILTER_HPP_

#include <stdint.h>

namespace filter
{

uint8_t low_pass_filter(uint32_t value);

bool hysteresis(uint32_t value, uint32_t threshold, bool& state) __attribute__ ((flatten));

void simple_moving_average(uint32_t value, uint32_t buff[], uint8_t size, uint32_t& sma);

uint32_t exponential_moving_average(uint32_t value, uint32_t old_value, uint32_t alpha)
		__attribute__ ((flatten));

}

#endif /* FILTER_HPP_ */
