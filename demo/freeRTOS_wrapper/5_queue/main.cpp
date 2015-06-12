//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <cstring>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "diag/Trace.h"

#define USE_WRAPPER 1

#if !USE_WRAPPER
#include "BlinkLed.h"
#else
#include "tsk_test.h"
#endif

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via ITM).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#if !USE_WRAPPER
#define TASK_LEDGreen_PRIO		( tskIDLE_PRIORITY + 2 )
#define TASK_LEDBlue_PRIO		( tskIDLE_PRIORITY + 1 )

static void task_led_green(void *pvParameters);
static void task_led_blue(void *pvParameters);

QueueHandle_t xQueue1, xQueue2;

#endif

int main(int argc, char* argv[])
{
	// At this stage the system clock should have already been configured
	// at high speed.

#if !USE_WRAPPER
	xTaskCreate(task_led_green, (const char * ) "Led_Green", configMINIMAL_STACK_SIZE, NULL,
				TASK_LEDGreen_PRIO, NULL);

	xTaskCreate(task_led_blue, (const char * ) "Led_Blue", configMINIMAL_STACK_SIZE, NULL,
				TASK_LEDBlue_PRIO, NULL);

#else
	static TSK_T1 tsk_t1;
	static TSK_T2 tsk_t2;

	tsk_t1.link(tsk_t2);
	tsk_t2.link(tsk_t1);

#endif

	volatile size_t size = xPortGetFreeHeapSize();

	vTaskStartScheduler();    // should never return
}

struct AMessage
{
	uint32_t id_;
	uint8_t a_[20];
};

#if !USE_WRAPPER
void task_led_green(void *pvParameters)
{
//	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	xQueue1 = xQueueCreate(10, sizeof(AMessage));
	if (xQueue1 == 0)
	{
		// Queue was not created and must not be used.
	}

	AMessage msg;

	for (;;)
	{
		if (xQueueReceive(xQueue1, &msg, (TickType_t ) 2000) == false)
		{
			LED_Red.turnOn();
		}

		if (msg.id_ % 2 == 0)
		{
			LED_Green.toggle();
		}

//		vTaskDelay(xDelay);
	}

}

void task_led_blue(void *pvParameters)
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	static uint32_t count = 0;
	static uint32_t i = 0;

	AMessage msg;
	msg.id_ = count;
	memset(msg.a_, 0xFF, sizeof(uint8_t) * 20);
	msg.a_[i] = count;

	for (;;)
	{
		if ( xQueueSendToBack( xQueue1, ( void * ) &msg, ( TickType_t ) 10 ) != pdPASS)
		{
			LED_Orange.turnOn();
		}

		count++;
		i = (++i) % 20;

		msg.id_ = count;
		msg.a_[i] = count;

		LED_Blue.toggle();
		vTaskDelay(xDelay);
	}

}
#endif

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
