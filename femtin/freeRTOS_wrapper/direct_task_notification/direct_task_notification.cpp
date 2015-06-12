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
/// \file	direct_task_notification.cpp
/// \brief	Cpp wrapper around FreeRTOS Direct to Task Notification
/// \date	20/03/2015
/// \author	nboutin
///
/// ================================================================================================
#include "direct_task_notification.hpp"
using namespace os;

/// === INCLUDES	================================================================================

#include "femtin/freeRTOS_wrapper/delay.hpp"

/// === Public Definitions	========================================================================

bool os::notifyGive(const TaskHandle_t& handle)
{
	return xTaskNotifyGive(handle);
}

/// ------------------------------------------------------------------------------------------------

void os::notifyGiveISR(const TaskHandle_t& handle)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	vTaskNotifyGiveFromISR(handle, &xHigherPriorityTaskWoken);
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

/// ------------------------------------------------------------------------------------------------

uint32_t os::notifyTake(bool is_cleared_on_exit, TickType_t timeout_ms)
{
	return ulTaskNotifyTake(is_cleared_on_exit, ms_to_ticks(timeout_ms));
}

/// === Private Definitions	========================================================================
/// END OF FILE	====================================================================================
