/*
 * tsk_test.cpp
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#include "tsk_test.h"

/// === INCLUDES	================================================================================

#include "BlinkLed.h"
#include "direct_task_notification/direct_task_notification.hpp"

/// === STATIC IMPORT	============================================================================

extern TSK_T2 tsk_t2;

/// === STATIC DEFINITIONS	========================================================================
/// === PUBLIC DEFINITIONS	========================================================================

TSK_T1::TSK_T1()
		: Task("TSK_T1", STACK_SIZE, STACK_PRIORITY)
{

}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::link(TSK_T2& t2)
{
	pt2_ = &t2;
}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::run()
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	for (;;)
	{
		LED_Green.toggle();

		os::notifyGive(pt2_->handle());

		vTaskDelay(xDelay);
	}
}

/// ------------------------------------------------------------------------------------------------

void TSK_T2::run()
{
	for (;;)
	{
		os::notifyTake(true, os::TIMEOUT_MAX);

		LED_Blue.toggle();
	}
}

/// END OF FILE	====================================================================================
