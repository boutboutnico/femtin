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
/// \file	task.cpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	31/03/2014
/// \author	nboutin
///
/// ================================================================================================
#include "task.hpp"
using namespace os;

/// === Includes	================================================================================

#include "task.h"

/// === Public Definitions	========================================================================

Task::Task(const char* name, const uint16_t stack_depth, const UBaseType_t priority)
{
	/// signed char xTaskGenericCreate(
	/// void (*)(void *),
	/// const char *,
	/// unsigned short int,
	/// void *, unsigned char, void * *, unsigned char *, const xMEMORY_REGION *)
	if (xTaskCreate(Task::callback, name, stack_depth, this, priority, &handle_) != pdPASS)
	{
		for (;;)
			;
	}
}

/// ------------------------------------------------------------------------------------------------

void Task::suspend()
{
	vTaskSuspend(handle_);
}

/// ------------------------------------------------------------------------------------------------

void Task::resume()
{
	vTaskResume(handle_);
}

/// === Private Definitions	========================================================================

void Task::callback(void* param)
{
	/// TODO : static_cast or reinterpret_cast ?
	(static_cast<Task*>(param))->run();
}

/// === END OF FILE	================================================================================
