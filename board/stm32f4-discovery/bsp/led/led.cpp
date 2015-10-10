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
/// \file	led.cpp
/// \brief
/// \date	22/03/2015
/// \author	nboutin
///
/// ================================================================================================
#include "led.hpp"
using namespace board::led;

/// === Includes	================================================================================

#include "portable/pinout_mapping.hpp"

/// === Static Instantiation	====================================================================

LED board::led::LED_Green(LED_GREEN_GPIO_PORT, LED_GREEN_PIN);
LED board::led::LED_Orange(LED_ORANGE_GPIO_PORT, LED_ORANGE_PIN);
LED board::led::LED_Red(LED_RED_GPIO_PORT, LED_RED_PIN);
LED board::led::LED_Blue(LED_BLUE_GPIO_PORT, LED_BLUE_PIN);

/// === Public Definitions	========================================================================

LED::LED(port_type _port, pin_type _pin)
		: pin_(_pin), port_(_port)
{
	initialize();
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================

void LED::initialize()
{
	/// --- Clock
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/// --- Configure pin in output push/pull mode
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = pin_;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(port_, &GPIO_InitStructure);

	/// Start with led turned off
	off();
}

/// === END OF FILE	================================================================================
