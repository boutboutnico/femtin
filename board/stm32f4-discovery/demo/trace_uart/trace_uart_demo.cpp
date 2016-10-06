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
/// \file	trace_uart_demo.cpp
///	\brief	
///	\date	08/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "trace_uart_demo.hpp"

/// === Includes	================================================================================

//#include "femtin/iomanip.hpp"
#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "bsp/trace_uart/trace_uart.hpp"

/// === Namespaces	================================================================================

using namespace femtin;
using namespace femtin::unit;
using namespace femtin::os;
using namespace board::mcu;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

namespace demo
{
namespace trace_uart
{

void trace_uart_demo()
{
	/// --- Initialization	------------------------------------------------------------------------

	const millisecond delay { 1000 };

	/// --- Infinite Loop	------------------------------------------------------------------------
	for (;;)
	{
		trace << endl << '1' << endl;
		trace << "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`" << endl;
		trace << "abcdefghijklmnopqrstuvwxyz{|}~" << endl;
		static uint32_t i = 0;
		trace << "val=" << i++ << endl;
		trace << 1234 << endl;											///"1234"
		trace << width(6) << -200 << width(3) << 5 << "%" << endl;    ///"  -200,  5%"
		trace << ios_base::left << width(6) << 100 << endl << ios_base::right;    ///"100   "
		trace << 12345678L << endl;		///"12345678"
		///	trace_printf("%04x\n", 0xA3);			///"00a3"
		trace << ios_base::hex << width(4) << 0xA3 << endl << ios_base::dec;
		///	trace_printf("%08LX\n", 0x123ABC);		///"00123ABC"
		///	trace_printf("%016b\n", 0x550F);		///"0101010100001111"
		///	trace_printf("%s\n", "String");			///"String"
		///	trace_printf("%-4s\n", "abc");			///"abc "
		///	trace_printf("%4s\n", "abc");			///" abc"
		///	trace_printf("%c\n", 'a');				///"a"
		///	trace_printf("%f\n", 10.0);            	///<xprintf lacks floating point support>
		task_delay(delay);
	}
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
}
}

/// === END OF FILE	================================================================================
