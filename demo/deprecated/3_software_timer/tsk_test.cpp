/*
 * tsk_test.cpp
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#include "tsk_test.h"

/// === INCLUDES	================================================================================

#include "BlinkLed.h"

/// === STATIC IMPORT	============================================================================
/// === STATIC DEFINITIONS	========================================================================
/// === PUBLIC DEFINITIONS	========================================================================

TSK_T1::TSK_T1()
		: 	Task("TSK_T1", STACK_SIZE, STACK_PRIORITY),
			timer("TIM1", TIMER_DURATION, true, TSK_T1::callback)
{

}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::run()
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	LED_Red.turnOn();
	LED_Blue.turnOn();

	timer.start();

	for (;;)
	{
		LED_Green.toggle();
		vTaskDelay(xDelay);
	}
}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::callback(TimerHandle_t pxTimer)
{
	LED_Orange.toggle();
}

/// ------------------------------------------------------------------------------------------------

void TSK_T2::run()
{
	BlinkLed led3(3, 13);
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

	for (;;)
	{
		LED_Red.toggle();
		vTaskDelay(xDelay);
	}
}

/// END OF FILE	====================================================================================
