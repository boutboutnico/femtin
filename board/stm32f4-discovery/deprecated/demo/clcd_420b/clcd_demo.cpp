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
/// \file	clcd_demo.cpp
///	\brief	
///	\date	09/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "clcd_demo.hpp"

/// === Includes	================================================================================

#include "femtin/iomanip.hpp"
#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "peripherals/clcd_420b/clcd_420b.hpp"
#include "bsp/led/led.hpp"

/// === Namespaces	================================================================================

using namespace femtin;
using namespace femtin::unit;
using namespace femtin::os;
using namespace board::led;
using namespace peripheral::lcd;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

namespace demo
{
namespace clcd_420b
{

void clcd_demo()
{
	/// --- Initialization	------------------------------------------------------------------------

	const millisecond delay { 1000 };
	static CLCD_420B lcd;
	lcd.initialize();

	/// --- Infinite Loop	------------------------------------------------------------------------
	for (;;)
	{
		LED_Green.toggle();
		lcd.clear();

		char c = 'a';
		lcd << c << ' ' << 'c' << endl;
		task_delay(delay);

		const char* s = "coucou";
		char str[] = "salut ";
		lcd << s << ' ' << str << ' ' << "string" << endl;
		task_delay(delay);

		int8_t v_int8 = -12;
		uint8_t v_uint8 = 34;
		lcd << v_int8 << ' ' << v_uint8 << endl;
		task_delay(delay);

		int16_t v_int16 = -345;
		uint16_t v_uint16 = 456;
		lcd << v_int16 << ' ' << v_uint16 << endl;
		task_delay(delay);

		int32_t v_int32 = -71234;
		uint32_t v_uint32 = 86456;
		lcd << v_int32 << ' ' << v_uint32 << endl;
		task_delay(delay);

		lcd.clear();
		lcd << ios_base::hex << v_uint16 << endl;
		lcd << ios_base::oct << v_uint16 << endl;
		lcd << ios_base::dec << v_uint16 << endl;
		task_delay(delay);

		lcd << width(4) << 43 << endl;
		task_delay(delay);

		lcd << xy(10, 2) << "10,2" << endl;
		task_delay(delay);

		lcd << row(3) << "row 3" << endl;
		task_delay(delay);

		lcd.backlight(false);
		task_delay(delay);

		lcd.backlight(true);
		task_delay(delay);

		lcd.cursor(false);
		task_delay(delay);

		lcd.cursor(true);
		task_delay(delay);

//		lcd.home();
//		lcd.print("Home");
//		task_delay(delay);
//
//		lcd.cursor_xy(10, 2);
//		lcd.print("10,2");
//		task_delay(delay);
//
//		lcd.move_to_row(1);
//		lcd.print("row 1");
//		task_delay(delay);
	}
}
/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
}
}

/// === END OF FILE	================================================================================
