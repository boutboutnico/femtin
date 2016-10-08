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
/// \file	delay.hpp
/// \brief	Cpp wrapper around FreeRTOS tools
/// \date	20/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_DELAY_HPP_
#define FEMTIN_DELAY_HPP_

/// === Includes	================================================================================

#include "FreeRTOS.h"
#include "task.h"
#include "../unit/base_type/time_unit_type.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace os
{
/// ------------------------------------------------------------------------------------------------

/// TODO Use constexp ??
inline TickType_t ms_to_ticks(unit::millisecond _time)
{
	return pdMS_TO_TICKS(_time.value());
}

/// ------------------------------------------------------------------------------------------------

/// TODO Use constexp ??
inline unit::millisecond ticks_to_ms(TickType_t ticks)
{
	return unit::millisecond(ticks * portTICK_PERIOD_MS);
}

/// ------------------------------------------------------------------------------------------------

inline void task_delay(unit::millisecond _time)
{
	vTaskDelay(pdMS_TO_TICKS(_time.value()));
}

/// ------------------------------------------------------------------------------------------------

inline void task_delay_until(unit::millisecond _time)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();

	vTaskDelayUntil(&xLastWakeTime, ms_to_ticks(_time));
}
///	------------------------------------------------------------------------------------------------
}/// os
}    /// femtin
#endif	/// FEMTIN_DELAY_HPP_
/// === END OF FILE	================================================================================
