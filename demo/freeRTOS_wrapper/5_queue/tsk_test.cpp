/*
 * tsk_test.cpp
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#include "tsk_test.h"

/// === INCLUDES	================================================================================

#include <cstring>

#include "buffer.hpp"

#include "BlinkLed.h"
#include "direct_task_notification/direct_task_notification.hpp"

/// === Namespaces	================================================================================

using namespace femtin;

/// === STATIC IMPORT	============================================================================

extern TSK_T2 tsk_t2;

/// === STATIC DEFINITIONS	========================================================================
/// === PUBLIC DEFINITIONS	========================================================================

TSK_T1::TSK_T1()
		: 	Task("TSK_T1", STACK_SIZE, STACK_PRIORITY),
			queue1_(2, sizeof(uint32_t)),
			queue2_(2, sizeof(ST_Msg)),
			queue3_(2, sizeof(const Buffer<10>*))
{

}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::link(TSK_T2& t2)
{
	pt2_ = &t2;
}

/// ------------------------------------------------------------------------------------------------

void TSK_T1::run()
{
	uint32_t read32 = 0;
	ST_Msg msg_read1;
	Buffer<10> b_read;
	const Buffer<10>* pb_read = 0;

	for (;;)
	{
		if (queue1_.receive(&read32) == false)
		{
			LED_Red.turnOn();
		}

		if (read32 % 2 == 0)
		{
			LED_Green.toggle();
		}

		if (queue2_.receive(&msg_read1) == false)
		{
			LED_Red.turnOn();
		}

		if (msg_read1.id_ % 2 == 0)
		{
			LED_Green.toggle();
		}

		if (queue3_.receive(&pb_read) == false)
		{
			LED_Red.turnOn();
		}

		b_read.clear();
		b_read = *pb_read;

		uint8_t read8 = b_read.read<uint8_t>();
		if (read8 % 2 == 0)
		{
			LED_Green.toggle();
		}

	}
}

/// ------------------------------------------------------------------------------------------------

void TSK_T2::run()
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

	static uint32_t write32 = 0;
	static ST_Msg msg_write;
	msg_write.id_ = write32;
	memset(msg_write.a8_, 0xFF, sizeof(uint8_t) * ST_Msg::a_size);


	Buffer<10> b_write;
	b_write.add<uint32_t>(0x012345678);
	b_write.read<uint8_t>();
	const Buffer<10>* pb = &b_write;


	for (;;)
	{
		if (pt1_->getQueue1().sendToBack(&write32) == false)
		{
			LED_Orange.turnOn();
		}

		write32++;
		LED_Blue.toggle();

		vTaskDelay(xDelay);

		if (pt1_->getQueue2().sendToBack(&msg_write) == false)
		{
			LED_Orange.turnOn();
		}

		write32++;
		msg_write.id_ = write32;
		msg_write.a8_[write32 % ST_Msg::a_size] = write32 & 0xFF;
		LED_Blue.toggle();


		if (pt1_->getQueue3().sendToBack(&pb) == false)
		{
			LED_Orange.turnOn();
		}

		write32++;
		b_write.add<uint8_t>(write32 & 0xFF);
		LED_Blue.toggle();
	}
}

/// END OF FILE	====================================================================================
