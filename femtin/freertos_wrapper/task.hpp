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

/// === Includes

#include <assert.h>
#include <chrono>

#include <freertos_wrapper/freertos_port.hpp>

#include "FreeRTOS.h"
#include "task.h"

/// === Namespaces

namespace femtin
{

/// === Class Declarations

class Task
{
public:
  /// --- Public Types

  typedef TaskHandle_t native_handle_t;

  /// --- Inner Class Definition

  class id
  {
    friend class Task;

  public:
    id() : handle_() {}
    id(native_handle_t _handle) : handle_(_handle) {}
  private:
    friend bool operator==(Task::id _x, Task::id _y) { return _x.handle_ == _y.handle_; }
    native_handle_t handle_;
  };

  /// --- Public Functions

  Task(const char* _name, uint16_t _stack_depth, uint16_t _priority) : stack_depth_(_stack_depth)
  {
    /// TODO assert creation
    xTaskCreate(Task::callback, _name, _stack_depth, this, _priority, &id_.handle_);
  }

  virtual void run() = 0;

  /// --- Operations
  void suspend();
  void resume();

  void notify(uint32_t _value, eNotifyAction _action_e = eSetBits) const;

  bool wait(uint32_t& _notified_value,
            const std::chrono::milliseconds& _time,
            uint32_t _bits_to_clear_on_entry = 0x00,
            uint32_t _bits_to_clear_on_exit  = std::numeric_limits<uint32_t>::max());

  /// --- Observers
  Task::id get_id() const;
  native_handle_t native_handle() const;

  eTaskState state() const;
  char* name() const;
  uint16_t stack_depth() const;
  uint16_t stack_high_water_mark() const;

private:
  /// --- Private Functions

  static void callback(void* _arg)
  {
    /// TODO assert null pointer
    (static_cast<Task*>(_arg))->run();
  }

  /// --- Private_attributs

  id id_;
  const uint16_t stack_depth_;
};

/// === Inline Definitions

inline void Task::suspend() { vTaskSuspend(id_.handle_); }

inline void Task::resume() { vTaskResume(id_.handle_); }

inline void Task::notify(const uint32_t _value, const eNotifyAction _action_e) const
{
  auto r = false;
  if (is_in_ISR() == false)
  {
    r = (xTaskNotify(id_.handle_, _value, _action_e)) == pdPASS ? true : false;
  }
  /// From interrupt context
  else
  {
    auto higher_priority_task_woken = pdFALSE;
    r = (xTaskNotifyFromISR(id_.handle_, _value, _action_e, &higher_priority_task_woken)) == pdPASS
          ? true
          : false;

    portYIELD_FROM_ISR(higher_priority_task_woken);
  }

  assert(r);
}

inline bool Task::wait(uint32_t& _notified_value,
                       const std::chrono::milliseconds& _time,
                       uint32_t _bits_to_clear_on_entry,
                       uint32_t _bits_to_clear_on_exit)
{
  return (xTaskNotifyWait(_bits_to_clear_on_entry,
                          _bits_to_clear_on_exit,
                          &_notified_value,
                          ticks(_time).count()) == pdTRUE)
           ? true
           : false;
}

inline Task::id Task::get_id() const { return id_; }

inline Task::native_handle_t Task::native_handle() const { return id_.handle_; }

inline eTaskState Task::state() const { return eTaskGetState(id_.handle_); }

inline char* Task::name() const { return pcTaskGetTaskName(id_.handle_); }

inline uint16_t Task::stack_depth() const { return stack_depth_; }

#if (INCLUDE_uxTaskGetStackHighWaterMark == 1)
inline uint16_t Task::stack_high_water_mark() const { return uxTaskGetStackHighWaterMark(handle_); }
#endif

namespace task
{
inline Task::id get_idle_task_id() { return xTaskGetIdleTaskHandle(); }

inline uint32_t number_of_tasks() { return uxTaskGetNumberOfTasks(); }

#if ((configUSE_TRACE_FACILITY == 1) && (configUSE_STATS_FORMATTING_FUNCTIONS > 0))
inline void list(char* _write_buffer) { vTaskList(_write_buffer); }
#endif

#if ((configGENERATE_RUN_TIME_STATS == 1) && (configUSE_STATS_FORMATTING_FUNCTIONS > 0))
inline void runtime_stats(char* _write_buffer) { vTaskGetRunTimeStats(_write_buffer); }
#endif

inline uint32_t tick_count()
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
} // task

namespace this_task
{
inline Task::id get_id() { return xTaskGetCurrentTaskHandle(); }

inline void sleep_for(const std::chrono::milliseconds& _time) { vTaskDelay(ticks(_time).count()); }

inline void sleep_until(const std::chrono::milliseconds& _time)
{
  uint32_t now = task::tick_count();
  vTaskDelayUntil(&now, ticks(_time).count());
}

} // this_task
} // femtin

#endif
/// === END OF FILE
