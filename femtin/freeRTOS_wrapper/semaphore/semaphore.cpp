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
/// \file	semaphore.hpp
/// \brief	Cpp wrapper around FreeRTOS semaphore
/// \date	17/11/2014
/// \author	nboutin
///
/// ================================================================================================
#include "semaphore.hpp"
using namespace femtin::os;

/// === Includes	================================================================================

#include <assert.h>
#include "femtin/freeRTOS_wrapper/delay.hpp"

///	===	Namespaces	================================================================================

using namespace femtin::unit;

/// === Public Definitions	========================================================================

Semaphore::Semaphore(uint8_t n_token)
{
	if (n_token == 0)
	{
		handle_ = xSemaphoreCreateBinary();
	}
	else
	{
		handle_ = xSemaphoreCreateCounting(n_token, n_token);
	}

	assert(handle_ != NULL);
}

/// ------------------------------------------------------------------------------------------------

bool Semaphore::take(millisecond timeout)
{
	return xSemaphoreTake(handle_, os::ms_to_ticks(timeout));
}

/// ------------------------------------------------------------------------------------------------

bool Semaphore::takeFromISR()
{
	BaseType_t pxHigherPriorityTaskWoken;

	return xSemaphoreTakeFromISR(handle_, &pxHigherPriorityTaskWoken);
}

/// ------------------------------------------------------------------------------------------------

bool Semaphore::give()
{
	return xSemaphoreGive(handle_);
}

/// ------------------------------------------------------------------------------------------------

bool Semaphore::giveFromISR()
{
	/// From FreeRTOS V7.3.0 pxHigherPriorityTaskWoken
	/// is an optional parameter and can be set to NULL.
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	bool result = false;

	result = xSemaphoreGiveFromISR(handle_, NULL);

	vTaskNotifyGiveFromISR(handle_, &xHigherPriorityTaskWoken);
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);

	return result;
}

/// ------------------------------------------------------------------------------------------------

/// === END OF FILE	================================================================================
