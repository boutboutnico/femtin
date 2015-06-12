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

//OS::Semaphore TSK_T1::sem(TSK_T1::SEMAPHORE_N_TOKEN);

/// === PUBLIC DEFINITIONS	========================================================================

TSK_T1::TSK_T1()
		: Task("TSK_T1", STACK_SIZE, STACK_PRIORITY)
//,			timer("TIM1", TIMER_DURATION, true, TSK_T1::callback)
{

}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::run()
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	for (;;)
	{
		LED_Green.toggle();
		vTaskDelay(xDelay);
	}

#if 0
//	xSerialxPrintf_P(&xSerialPort, PSTR("Enter run\n"));

//	static const TickType_t delay = 500;

//	bitSet(DDRB, DDB4);
//	bitClear(PORTB, PORTB4);

//	BlinkLed led4(3, 12);

//	timer.start();

	for (;;)
	{
//		if (sem.take(SEMAPHORE_TIMEOUT))
//		{
////			xSerialxPrintf_P(&xSerialPort, PSTR("Get\n"));
//		}
//		else
//		{
////			xSerialxPrintf_P(&xSerialPort, PSTR("Timeout\n"));
//		}
////		bitSet(PORTB, PORTB4);
//		led4.turnOn();
//
//		if (sem.take(SEMAPHORE_TIMEOUT))
//		{
////			xSerialxPrintf_P(&xSerialPort, PSTR("Get\n"));
//		}
//		else
//		{
////			xSerialxPrintf_P(&xSerialPort, PSTR("Timeout\n"));
//		}
////		bitClear(PORTB, PORTB4);
//		led4.turnOff();

//		bitClear(PORTB, PORTB4);
//		led4.turnOn();
//		OS::delayUntil(delay);
////
////		bitSet(PORTB, PORTB4);
//		led4.turnOff();
//		OS::delayUntil(delay);

//		xSerialxPrintf_P(&xSerialPort, PSTR("Current Timestamp: %lu xTaskGetTickCount(): %u\r\n"),
//				time(NULL), xTaskGetTickCount());
	}
#endif
}

/// ------------------------------------------------------------------------------------------------

//void TSK_T1::callback(TimerHandle_t pxTimer)
//{
//	sem.give();
//}

/// ------------------------------------------------------------------------------------------------

void TSK_T2::run()
{
	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

	for (;;)
	{
		LED_Orange.toggle();
		vTaskDelay(xDelay);
	}
}

/// END OF FILE	====================================================================================
