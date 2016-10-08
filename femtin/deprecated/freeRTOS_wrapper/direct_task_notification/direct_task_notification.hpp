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
/// \file	direct_task_notification.hpp
/// \brief	Cpp wrapper around FreeRTOS Direct to Task Notification
/// \date	20/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef DIRECT_TASK_NOTIFICATION_HPP_
#define DIRECT_TASK_NOTIFICATION_HPP_

/// === Includes	================================================================================

#include "FreeRTOS.h"
#include "task.h"
#include "femtin/freeRTOS_wrapper/freeRTOS_wrapper.hpp"
#include "femtin/unit/base_type/time_unit_type.hpp"

///	===	Namespaces	================================================================================

namespace femtin
{
namespace os
{

bool notifyGive(const TaskHandle_t& _handle);

void notifyGiveISR(const TaskHandle_t& _handle);

uint32_t notifyTake(bool is_cleared_on_exit, unit::millisecond _timeout);

/// ------------------------------------------------------------------------------------------------

}
}
#endif
/// END OF FILE	====================================================================================
