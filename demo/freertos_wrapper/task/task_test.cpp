/*
 * tsk_test.cpp
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#include "task_test.hpp"
using namespace femtin::demo;

/// === Includes ===================================================================================

#include "bsp/led/led.hpp"

/// === Namespaces =================================================================================

using namespace board::led;

/// === Public Definitions =========================================================================

Task1::Task1() : Task("Task1", STACK_SIZE, STACK_PRIORITY)
{
}

/// ------------------------------------------------------------------------------------------------

void Task1::run()
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

void Task2::run()
{
  const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

  for (;;)
  {
    LED_Orange.toggle();
    vTaskDelay(xDelay);
  }
}

/// === END OF FILE ================================================================================
