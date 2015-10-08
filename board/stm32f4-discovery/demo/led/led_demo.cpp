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
/// \file	led_demo.cpp
///	\brief	
///	\date	08/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "led_demo.hpp"

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "bsp/led/led.hpp"

/// === Namespaces	================================================================================

using namespace femtin::unit;
using namespace femtin::os;
using namespace board::led;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

namespace demo
{
namespace led
{

void led_demo()
{
	/// --- Initialization	------------------------------------------------------------------------

	const millisecond delay { 500 };

	for (;;)
	{
		LED_Blue.toggle();
		LED_Green.toggle();
		LED_Orange.toggle();
		LED_Red.toggle();
		task_delay(delay);
	}
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
}
}

/// === END OF FILE	================================================================================
