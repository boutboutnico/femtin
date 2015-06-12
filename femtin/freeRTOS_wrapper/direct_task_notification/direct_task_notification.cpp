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

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/delay.hpp"

///	===	Namespaces	================================================================================

using namespace femtin::unit;

namespace femtin
{
namespace os
{

/// === Public Definitions	========================================================================

bool notifyGive(const TaskHandle_t& _handle)
{
	return xTaskNotifyGive(_handle);
}

/// ------------------------------------------------------------------------------------------------

void notifyGiveISR(const TaskHandle_t& _handle)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	vTaskNotifyGiveFromISR(_handle, &xHigherPriorityTaskWoken);
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

/// ------------------------------------------------------------------------------------------------

uint32_t notifyTake(bool is_cleared_on_exit, millisecond _timeout)
{
	return ulTaskNotifyTake(is_cleared_on_exit, ms_to_ticks(_timeout));
}

/// === Private Definitions	========================================================================

///	------------------------------------------------------------------------------------------------
}/// os
}/// femtin
/// END OF FILE	====================================================================================
