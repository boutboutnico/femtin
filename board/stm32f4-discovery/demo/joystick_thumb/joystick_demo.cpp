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
/// \file	joystick_demo.cpp
///	\brief	
///	\date	10/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "joystick_demo.hpp"

/// === Includes	================================================================================

#include "femtin/iomanip.hpp"
#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "bsp/led/led.hpp"
#include "peripherals/clcd_420b/clcd_420b.hpp"
#include "peripherals/joystick_thumb/joystick.hpp"

/// === Namespaces	================================================================================

using namespace femtin;
using namespace femtin::unit;
using namespace femtin::os;
using namespace board::led;
using namespace peripheral::lcd;
using namespace peripheral::joystick_thumb;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

namespace demo
{
namespace joystick
{

void joystick_demo()
{
	/// --- Constant	----------------------------------------------------------------------------

//	static const uint8_t arrow_right[8] = { 0b00000, 0b00100, 0b00010, 0b11111, 0b00010, 0b00100,
//											0b00000, 0b00000 };
//
//	static const uint8_t arrow_left[8] = { 0b00000, 0b00100, 0b01000, 0b11111, 0b01000, 0b00100,
//											0b00000, 0b00000 };

	static const uint8_t arrow_up[8] = { 0b00000, 0b00100, 0b01110, 0b10101, 0b00100, 0b00100,
											0b00000, 0b00000 };

	static const uint8_t arrow_down[8] = { 0b00000, 0b00100, 0b00100, 0b10101, 0b01110, 0b00100,
											0b00000, 0b00000 };
//	static const uint8_t code_arrow_right = 8;
//	static const uint8_t code_arrow_left = 9;
	static const uint8_t code_arrow_up = 8;
	static const uint8_t code_arrow_down = 9;

	/// --- Initialization	------------------------------------------------------------------------

	const millisecond delay { 200 };
	static CLCD_420B lcd;
	static Joystick joystick;

	lcd.initialize();
	joystick.initialize();

	/// --- Infinite Loop	------------------------------------------------------------------------

//	lcd_.store_custom(code_arrow_right, arrow_right);
//	task_delay(delay);
//	lcd_.store_custom(code_arrow_left, arrow_left);
//	task_delay(delay);
	lcd.store_custom(code_arrow_up, arrow_up);
	task_delay(delay);
	lcd.store_custom(code_arrow_down, arrow_down);
	task_delay(delay);

	lcd.home();
	lcd.clear();
	lcd.cursor(false);

	uint32_t vertical = 0, horizontal = 0;
	bool is_push = false;

	for (;;)
	{
		task_delay(delay);
		LED_Green.toggle();

		vertical = joystick.read_vertical();
		horizontal = joystick.read_horizontal();
		is_push = joystick.is_push();

		lcd << row(0) << width(6) << vertical << endl;
		lcd << width(6) << horizontal << endl;
		lcd << xy(5, 2);
		is_push ? lcd << "P" : lcd << "_";

		lcd << xy(15, 0);
		if (vertical >= 800) lcd.call_custom(code_arrow_up);
		else lcd << "_";

		lcd << xy(15, 2);
		if (vertical <= 200) lcd.call_custom(code_arrow_down);
		else lcd << "_";

		lcd << xy(14, 1);
		if (horizontal >= 800) lcd << "<";
		else lcd << "_";

		lcd << xy(16, 1);
		if (horizontal <= 200) lcd << ">";
		else lcd << "_";

		lcd << xy(15, 1);
		if (is_push == true) lcd << "X";
		else lcd << "_";
	}
}
/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
}
}

/// === END OF FILE	================================================================================
