/*
 Femtin V0.0.1 - Copyright (C) 2015 Nicolas Boutin.
 All rights reserved

 This file is part of the Femtin distribution.

 Femtin is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License (version 2) as published by the
 Free Software Foundation.

 Femtin is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.
 */

/// ================================================================================================
///
/// \file	task.cpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	31/03/2014
/// \author	nboutin
///
/// ================================================================================================
#include "task.hpp"
using namespace femtin::os;

/// === Includes	================================================================================

#include <cstdio>
#include "task.h"

/// === Public Definitions	========================================================================

Task::Task(const char* _name, const uint16_t _stack_depth, const UBaseType_t _priority)
		: handle_(), stack_depth_(_stack_depth)
{
	/// signed char xTaskGenericCreate(
	/// void (*)(void *),
	/// const char *,
	/// unsigned short int,
	/// void *, unsigned char, void * *, unsigned char *, const xMEMORY_REGION *)
	if (xTaskCreate(Task::callback, _name, _stack_depth, this, _priority, &handle_) != pdPASS)
	{
		for (;;)
			;
	}
}

/// ------------------------------------------------------------------------------------------------

void Task::suspend()
{
	vTaskSuspend(handle_);
}

/// ------------------------------------------------------------------------------------------------

void Task::resume()
{
	vTaskResume(handle_);
}

/// ------------------------------------------------------------------------------------------------

//void Task::list_custom(char* _write_buffer, femtin::Array_ptr<TaskStatus_t> _working_buffer)
//{
//	if (uxTaskGetSystemState(_working_buffer.begin(), _working_buffer.max_size(), NULL) != 0)
//	{
//		char status;
//
//		/// Create a human readable table from the binary data.
//		for (size_t i = 0; i < _working_buffer.max_size(); i++)
//		{
//			switch (_working_buffer[i].eCurrentState)
//			{
//			case eReady:
//				status = 'R';
//				break;
//
//			case eBlocked:
//				status = 'B';
//				break;
//
//			case eSuspended:
//				status = 'S';
//				break;
//
//			case eDeleted:
//				status = 'D';
//				break;
//
//			default:
//				/// Should not get here, but it is included to prevent static checking errors.
//				status = 0x00;
//				break;
//			}
//
//			sprintf(_write_buffer, "%s\t%c\t%u\t%u\t%u\r\n", _working_buffer[i].pcTaskName, status,
//					(unsigned int) _working_buffer[i].uxCurrentPriority,
//					(unsigned int) _working_buffer[i].xTaskNumber,
//					(unsigned int) _working_buffer[i].usStackHighWaterMark * 4);
//			_write_buffer += strlen(_write_buffer);
//		}
//	}
//	else
//	{
//		/// Error
//	}
//}

/// === Private Definitions	========================================================================

void Task::callback(void* param)
{
/// TODO : static_cast or reinterpret_cast ?
	(static_cast<Task*>(param))->run();
}

/// === END OF FILE	================================================================================
