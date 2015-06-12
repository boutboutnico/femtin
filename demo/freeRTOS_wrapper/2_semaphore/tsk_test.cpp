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

os::Semaphore sem_1(0);
os::Semaphore sem_2(0);

/// === PUBLIC DEFINITIONS	========================================================================

TSK_T1::TSK_T1()
		: Task("TSK_T1", STACK_SIZE, STACK_PRIORITY)
{

}

/// ------------------------------------------------------------------------------------------------

TSK_T2::TSK_T2()
		: Task("TSK_T2", STACK_SIZE, STACK_PRIORITY)
{

}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::run()
{
	BlinkLed led4(3, 12);
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	for (;;)
	{
		sem_2.take();

		LED_Green.toggle();
		vTaskDelay(xDelay);

		sem_1.give();
	}
}

/// ------------------------------------------------------------------------------------------------

void TSK_T2::run()
{
	BlinkLed led3(3, 13);
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

	sem_2.give();

	for (;;)
	{
		sem_1.take();

		LED_Orange.toggle();
		vTaskDelay(xDelay);

		sem_2.give();
	}
}

/// END OF FILE	====================================================================================
