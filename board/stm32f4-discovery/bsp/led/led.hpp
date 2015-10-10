/*
 Femtin V0.0.1 - Copyright (C) 2015 Nicolas Boutin.
 All rights reserved

 This file is part of the Femtin distribution.

 Femtin is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License (version 2) as published by the
 Free Software Foundation.

 Femtin is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.
 */

/// ================================================================================================
///
/// \file	led.hpp
/// \brief
/// \date	22/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef BOARD_LED_LED_HPP_
#define BOARD_LED_LED_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"

/// === Namespaces	================================================================================

namespace board
{
namespace led
{

/// === Forward Declarations	====================================================================

class LED;

/// === Extern Declarations	========================================================================

extern LED LED_Green;
extern LED LED_Orange;
extern LED LED_Red;
extern LED LED_Blue;

/// === Class Declarations	========================================================================

class LED
{
public:
	/// === Basic Types	============================================================================

	typedef uint16_t pin_type;
	typedef GPIO_TypeDef* port_type;

	/// === Public Declarations	====================================================================

	LED(port_type _port, pin_type _pin);

	inline void toggle() __attribute__((always_inline));

	inline void on() __attribute__((always_inline));

	inline void off() __attribute__((always_inline));

private:
	/// === Private Declarations	================================================================

	void initialize();

	/// === Private Attributes	====================================================================

	const pin_type pin_;
	const port_type port_;
};

/// === Inline Definitions	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

inline void LED::toggle()
{
	HAL_GPIO_TogglePin(port_, pin_);
}

/// ------------------------------------------------------------------------------------------------

inline void LED::on()
{
	HAL_GPIO_WritePin(port_, pin_, GPIO_PinState::GPIO_PIN_SET);
}

/// ------------------------------------------------------------------------------------------------

inline void LED::off()
{
	HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_RESET);
}

#pragma GCC diagnostic pop
/// ------------------------------------------------------------------------------------------------
}/// led
}    /// board
#endif
/// === END OF FILE	================================================================================
