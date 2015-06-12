/*
 * tsk_test.H
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#ifndef TSK_TEST_H_
#define TSK_TEST_H_

#include "task/task.hpp"
#include "semaphore/semaphore.hpp"

extern os::Semaphore sem_1;
extern os::Semaphore sem_2;

/// === CLASS	====================================================================================

class TSK_T1 : public os::Task
{
public:
	/// === Public Constants	====================================================================

	static const uint16_t STACK_SIZE = configMINIMAL_STACK_SIZE;
	static const UBaseType_t STACK_PRIORITY = ( tskIDLE_PRIORITY + 2);

	/// === Public Declarations	====================================================================

	TSK_T1();

	virtual void run();

private:
	/// === Private Declarations	================================================================
};

/// === CLASS	====================================================================================

class TSK_T2 : public os::Task
{
public:
	/// === Public Constants	====================================================================

	static const uint16_t STACK_SIZE = configMINIMAL_STACK_SIZE;
	static const UBaseType_t STACK_PRIORITY = ( tskIDLE_PRIORITY + 1);

	/// === Public Declarations	====================================================================

	TSK_T2();

	virtual void run();

private:
	/// === Private Declarations	================================================================
};

#endif	/// TSK_TEST_H_
/// END OF FILE	====================================================================================
