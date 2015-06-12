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
/// \file	software_timer.cpp
/// \brief	Cpp wrapper around FreeRTOS software timer
/// \date	19/03/2015
/// \author	nboutin
///
/// ================================================================================================
#include "software_timer.hpp"
using namespace femtin::os;

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/delay.hpp"

///	===	Namespaces	================================================================================

using namespace femtin::unit;

/// === Public Definitions	========================================================================

Software_Timer::Software_Timer(	char const * const name,
								millisecond time_ms,
								bool auto_reload,
								timer_callback_t callback)
{
	///	 TimerHandle_t xTimerCreate
	///	  ( const char * const pcTimerName,
	///		const TickType_t xTimerPeriod,
	///		const UBaseType_t uxAutoReload,
	///		void * const pvTimerID,
	///		TimerCallbackFunction_t pxCallbackFunction );
	handle_ = xTimerCreate(name, os::ms_to_ticks(time_ms), auto_reload, this, callback);

	if (handle_ == NULL)
	{
		for (;;)
			;
	}
}

/// ------------------------------------------------------------------------------------------------

bool Software_Timer::start()
{
	return xTimerStart(handle_, 0);
}

/// ------------------------------------------------------------------------------------------------

bool Software_Timer::stop()
{
	return xTimerStop(handle_, 0);
}

/// ------------------------------------------------------------------------------------------------

bool Software_Timer::change(millisecond time_ms)
{
	return xTimerChangePeriod(handle_, os::ms_to_ticks(time_ms), 0);
}

/// ------------------------------------------------------------------------------------------------

bool Software_Timer::reset()
{
	return xTimerReset(handle_, 0);
}

/// ------------------------------------------------------------------------------------------------

bool Software_Timer::active() const
{
	return xTimerIsTimerActive(handle_);
}

/// === Private Definitions	========================================================================
/// END OF FILE	====================================================================================
