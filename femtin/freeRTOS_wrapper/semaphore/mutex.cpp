/// ================================================================================================
///
/// \file	mutex.cpp
///	\brief	
///	\date	30/05/2015
/// \author	nboutin
///
/// ================================================================================================

#include "mutex.hpp"
using namespace femtin::os;

/// === Includes	================================================================================

#include <assert.h>
#include "femtin/freeRTOS_wrapper/delay.hpp"

/// === Namespaces	================================================================================

using namespace femtin::unit;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

Mutex::Mutex()
{
	handle_ = xSemaphoreCreateMutex();
	assert(handle_ != NULL);
}

/// ------------------------------------------------------------------------------------------------

bool Mutex::acquire(millisecond timeout)
{
	return xSemaphoreTake(handle_, os::ms_to_ticks(timeout));
}

/// ------------------------------------------------------------------------------------------------

bool Mutex::acquireFromISR()
{
	BaseType_t pxHigherPriorityTaskWoken;

	return xSemaphoreTakeFromISR(handle_, &pxHigherPriorityTaskWoken);
}

/// ------------------------------------------------------------------------------------------------

bool Mutex::release()
{
	return xSemaphoreGive(handle_);
}

/// ------------------------------------------------------------------------------------------------

bool Mutex::releaseFromISR()
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
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
