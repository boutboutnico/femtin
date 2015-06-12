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
/// \file	software_timer.hpp
/// \brief	Cpp wrapper around FreeRTOS software timer
/// \date	19/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef SOFTWARE_TIMER_HPP_
#define SOFTWARE_TIMER_HPP_

/// === INCLUDES	================================================================================

#include "FreeRTOS.h"
#include "timers.h"

/// NAMESPACES	====================================================================================

namespace os
{

/// === CLASS	====================================================================================

class Software_Timer
{
public:
	/// Public Typedef	============================================================================

	typedef void (*timer_callback_t)(TimerHandle_t pxTimer);

	/// Public Declarations	========================================================================

	Software_Timer(	char const * const name,
					TickType_t time_ms,
					bool auto_reload,
					timer_callback_t callback);

	bool start();
	bool stop();
	bool change(TickType_t time_ms);
	bool reset();

	inline bool active() const;

private:
	/// Private Declarations	====================================================================

	TimerHandle_t handle_;
};

}

#endif	/// SOFTWARE_TIMER_HPP_
/// END OF FILE	====================================================================================
