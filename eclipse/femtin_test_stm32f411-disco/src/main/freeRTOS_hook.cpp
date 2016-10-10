///
/// \file	freeRTOS_hook.cpp
///	\brief	
///	\date	3 mars 2015
/// \author	nb_work
///

/// === INCLUDES	================================================================================

#include "freeRTOS_hook.h"
//#include "bsp/trace_uart/trace_uart.hpp"
//#include "femtin/trace/trace.hpp"

/// === NAMESPACES	================================================================================

/// === PUBLIC DEFINITIONS	========================================================================

#ifdef __cplusplus
extern "C"
{
#endif

/// ----------------------------------------------------------------------------------------------

#if ( configUSE_IDLE_HOOK > 0 )
/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
 to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
 task.  It is essential that code added to this hook function never attempts
 to block in any way (for example, call xQueueReceive() with a block time
 specified, or call vTaskDelay()).  If the application makes use of the
 vTaskDelete() API function (as this demo application does) then it is also
 important that vApplicationIdleHook() is permitted to return to its calling
 function, because it is the responsibility of the idle task to clean up
 memory allocated by the kernel to any task that has since been deleted. */
void vApplicationIdleHook(void)
{
}

#endif

/// ----------------------------------------------------------------------------------------------

#if  (configUSE_TICK_HOOK > 0)
/*The tick interrupt can optionally call an application defined hook (or callback) function - the
 tick hook. The tick hook provides a convenient place to implement timer functionality.
 The tick hook will only get called if configUSE_TICK_HOOK is set to 1 within FreeRTOSConfig.h.
 When this is set the application must provide the hook function with the following prototype:
 void vApplicationTickHook( void );
 vApplicationTickHook() executes from within an ISR so must be very short, not use much stack,
 and not call any API functions that don't end in "FromISR" or "FROM_ISR".
 */
void vApplicationTickHook(void)
{
}

#endif

/// ----------------------------------------------------------------------------------------------

#if (configCHECK_FOR_STACK_OVERFLOW > 0)

void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
	(void) pcTaskName;
	(void) pxTask;
	/* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	 function is called if a stack overflow is detected. */
//  taskDISABLE_INTERRUPTS ();
//	trace_printf("[StackOverFlow] !!! %s !!!\n", pcTaskName);
//	board::mcu::trace << "[StackOverFlow] !!! " << reinterpret_cast<char*>(pcTaskName) << " !!!"
//						<< femtin::endl;

//	TRACE_F("StackOverFlow", "!!! %s !!!\n", reinterpret_cast<char*>(pcTaskName));

	for (;;)
		;
}

#endif

/// ----------------------------------------------------------------------------------------------

#if (configUSE_MALLOC_FAILED_HOOK > 0)

/* vApplicationMallocFailedHook() will only be called if
 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
 function that will get called if a call to pvPortMalloc() fails.
 pvPortMalloc() is called internally by the kernel whenever a task, queue,
 timer or semaphore is created.  It is also called by various parts of the
 demo application.  If heap_1.c or heap_2.c are used, then the size of the
 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
 to query the size of free heap space that remains (although it does not
 provide information on how the remaining heap might be fragmented). */
void vApplicationMallocFailedHook(void)
{
//  taskDISABLE_INTERRUPTS ();
//	board::mcu::trace << "[MallocFailed] !!!" << femtin::endl;
//	TRACE_F("MallocFailed", "!!! Error !!!\n");
	for (;;)
		;
}

#endif

/// ----------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

/// === END OF FILES	============================================================================
