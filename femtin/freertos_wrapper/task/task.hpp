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
/// \file	task.hpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	31/03/2014
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TASK_HPP_
#define FEMTIN_TASK_HPP_

/// === Includes ===================================================================================

#include "FreeRTOS.h"
#include "task.h"

#include "../freertos_wrapper.hpp"

/// === Namespaces =================================================================================

namespace femtin
{
namespace os
{

/// === Class Declarations =========================================================================

class Task
{
public:
  /// --- Public Functions -------------------------------------------------------------------------

  Task(const char* name, const uint16_t stack_depth, const UBaseType_t priority);

  virtual void run() = 0;

  void suspend();

  void resume();

  TaskHandle_t handle() const;
  eTaskState state() const;
  char* name() const;
  uint16_t stack_depth() const;
  UBaseType_t stack_high_water_mark() const;

  /// --- Task Utilities ---------------------------------------------------------------------------

  static TaskHandle_t current_task_handle();
  static TaskHandle_t idle_task_handle();
  static TickType_t tick_count();
  static UBaseType_t number_of_tasks();
  static void list(char* _write_buffer);
  //  static void list_custom(char* _write_buffer, femtin::Array_ptr<TaskStatus_t> _working_buffer);
  static void runtime_stats(char* _write_buffer);

private:
  /// --- Private Functions ------------------------------------------------------------------------

  static void callback(void* param);

  /// --- Private Attributs ------------------------------------------------------------------------

  TaskHandle_t handle_;
  const uint16_t stack_depth_;
};

/// === Inline Definitions =========================================================================

inline TaskHandle_t Task::handle() const
{
  return handle_;
}

inline eTaskState Task::state() const
{
  return eTaskGetState(handle_);
}

inline char* Task::name() const
{
  return pcTaskGetTaskName(handle_);
}

inline uint16_t Task::stack_depth() const
{
  return stack_depth_;
}

#if (INCLUDE_uxTaskGetStackHighWaterMark == 1)
inline UBaseType_t Task::stack_high_water_mark() const
{
  return uxTaskGetStackHighWaterMark(handle_);
}
#endif

/// --- Task Utilities -----------------------------------------------------------------------------

inline TaskHandle_t Task::current_task_handle()
{
  return xTaskGetCurrentTaskHandle();
}

inline TaskHandle_t Task::idle_task_handle()
{
  return xTaskGetIdleTaskHandle();
}

inline TickType_t Task::tick_count()
{
  if (is_in_ISR() == true)
  {
    return xTaskGetTickCountFromISR();
  }
  else
  {
    return xTaskGetTickCount();
  }
}

inline UBaseType_t Task::number_of_tasks()
{
  return uxTaskGetNumberOfTasks();
}

#if ((configUSE_TRACE_FACILITY == 1) && (configUSE_STATS_FORMATTING_FUNCTIONS > 0))
inline void Task::list(char* _write_buffer)
{
  vTaskList(_write_buffer);
}
#endif

#if ((configGENERATE_RUN_TIME_STATS == 1) && (configUSE_STATS_FORMATTING_FUNCTIONS > 0))
inline void runtime_stats(char* _write_buffer)
{
  vTaskGetRunTimeStats(_write_buffer);
}
#endif

/// ------------------------------------------------------------------------------------------------
}
}
#endif
/// === END OF FILE ================================================================================
