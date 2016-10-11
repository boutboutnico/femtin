/*
 * tsk_test.H
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#ifndef TSK_TEST_H_
#define TSK_TEST_H_

#include "task/task.hpp"
#include "queue/queue.hpp"

class TSK_T2;

struct ST_Msg
{
	static const uint8_t a_size = 10;
	uint32_t id_;
	uint8_t a8_[a_size];
};

typedef const uint8_t Array_t[10];

class TSK_T1 : public os::Task
{
public:
	/// === PUBLIC ATTRIBUTS	================================================================

	static const uint16_t STACK_SIZE = configMINIMAL_STACK_SIZE;
	static const UBaseType_t STACK_PRIORITY = ( tskIDLE_PRIORITY + 2);

	/// === PUBLIC DECLARATIONS	================================================================

	TSK_T1();

	virtual void run();
	void link(TSK_T2& t2);
	inline const os::Queue& getQueue1() const;
	inline const os::Queue& getQueue2() const;
	inline const os::Queue& getQueue3() const;

private:
	/// === PRIVATE DECLARATIONS	============================================================

	TSK_T2* pt2_;
	os::Queue queue1_;
	os::Queue queue2_;
	os::Queue queue3_;

	/// === PRIVATE ATTRIBUTS	================================================================
};

inline const os::Queue& TSK_T1::getQueue1() const
{
	return queue1_;
}

inline const os::Queue& TSK_T1::getQueue2() const
{
	return queue2_;
}

inline const os::Queue& TSK_T1::getQueue3() const
{
	return queue3_;
}

/// ------------------------------------------------------------------------------------------------

class TSK_T2 : public os::Task
{
public:
	TSK_T2()
			: Task("TSK_T2", configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 1)
	{

	}
	virtual void run();

	void link(TSK_T1& _t1)
	{
		pt1_ = &_t1;
	}

private:

	TSK_T1* pt1_;
};

#endif /* TSK_TEST_H_ */
