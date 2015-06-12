/*
 * tsk_test.H
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#ifndef TSK_TEST_H_
#define TSK_TEST_H_

#include "task/task.hpp"
//#include "semaphore/semaphore.hpp"
//#include "software_timer/software_timer.hpp"

class TSK_T1 : public os::Task
{
public:
	/// === PUBLIC ATTRIBUTS	================================================================

	static const uint16_t STACK_SIZE = configMINIMAL_STACK_SIZE;
	static const UBaseType_t STACK_PRIORITY = ( tskIDLE_PRIORITY + 2);

//	static const TickType_t TIMER_DURATION = 500;
//
//	static const uint8_t SEMAPHORE_N_TOKEN = 10;
//	static const uint16_t SEMAPHORE_TIMEOUT = 400;

	/// === PUBLIC DECLARATIONS	================================================================

	TSK_T1();

	virtual void run();

private:
	/// === PRIVATE DECLARATIONS	============================================================

//	static void callback(TimerHandle_t pxTimer);

	/// === PRIVATE ATTRIBUTS	================================================================

//	OS::Software_Timer timer;
//	static OS::Semaphore sem;
};

/// ------------------------------------------------------------------------------------------------

class TSK_T2 : public os::Task
{
public:
	TSK_T2()
			: Task("TSK_T2", configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 1 )
	{

	}
	virtual void run();
};

#endif /* TSK_TEST_H_ */
