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
/// \file	task_util.cpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	12/10/2016
/// \author	nboutin
///
/// ================================================================================================

#include "task_util.hpp"
using namespace femtin;

/// === Includes

#include <vector>

#include "FreeRTOS.h"
#include "task.h"

/// === Public Definitions

void Task_Util::list_custom(/*char* _write_buffer, std::vector<TaskStatus_t> _working_buffer*/)
{
  //  if (uxTaskGetSystemState(_working_buffer.begin(), _working_buffer.max_size(), NULL) != 0)
  //  {
  //    char status;
  //
  //    /// Create a human readable table from the binary data.
  //    for (size_t i = 0; i < _working_buffer.max_size(); i++)
  //    {
  //      switch (_working_buffer[i].eCurrentState)
  //      {
  //      case eReady:
  //        status = 'R';
  //        break;
  //
  //      case eBlocked:
  //        status = 'B';
  //        break;
  //
  //      case eSuspended:
  //        status = 'S';
  //        break;
  //
  //      case eDeleted:
  //        status = 'D';
  //        break;
  //
  //      default:
  //        /// Should not get here, but it is included to prevent static
  //        checking errors.status = 0x00;
  //        break;
  //      }
  //
  //      sprintf(_write_buffer,
  //              "%s\t%c\t%u\t%u\t%u\r\n",
  //              _working_buffer[i].pcTaskName,
  //              status,
  //              (unsigned int)_working_buffer[i].uxCurrentPriority,
  //              (unsigned int)_working_buffer[i].xTaskNumber,
  //              (unsigned int)_working_buffer[i].usStackHighWaterMark * 4);
  //      _write_buffer += strlen(_write_buffer);
  //    }
  //  }
  //  else
  //  {
  //    /// Error
  //  }
}

/// === Private Definitions
/// === END OF FILE
