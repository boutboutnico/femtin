//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

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
#define TASK_LED4_PRIO		( tskIDLE_PRIORITY + 2 )
#define TASK_LED3_PRIO		( tskIDLE_PRIORITY + 1 )

static void task_led4(void *pvParameters);
static void task_led3(void *pvParameters);

static TaskHandle_t handle_led3 = NULL;

#endif

int main(int argc, char* argv[])
{
	// At this stage the system clock should have already been configured
	// at high speed.

#if !USE_WRAPPER
	xTaskCreate(task_led4, (const char * ) "Led4", configMINIMAL_STACK_SIZE, NULL, TASK_LED4_PRIO,
			NULL);

	xTaskCreate(task_led3, (const char * ) "Led3", configMINIMAL_STACK_SIZE, NULL, TASK_LED3_PRIO,
			&handle_led3);

#else
	static TSK_T1 tsk_t1;
	static TSK_T2 tsk_t2;

	tsk_t1.link(tsk_t2);

#endif

	volatile size_t size = xPortGetFreeHeapSize();

	vTaskStartScheduler();    // should never return
}

#if !USE_WRAPPER
void task_led4(void *pvParameters)
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	for (;;)
	{
		LED_Green.toggle();

		xTaskNotifyGive(handle_led3);

		vTaskDelay(xDelay);
	}

}

void task_led3(void *pvParameters)
{
//	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

	for (;;)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		LED_Blue.toggle();
//		vTaskDelay(xDelay);
	}

}
#endif

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
