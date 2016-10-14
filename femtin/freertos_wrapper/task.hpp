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

#include <cassert>
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

  /// --- Inner Enum Definitions

  enum class state_e : uint8_t
  {
    Ready = 0,
    Running,
    Blocked,
    Suspended,
    Deleted,
    Invalid,
  };

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

  ~Task() { vTaskDelete(id_.handle_); }

  virtual void run() = 0;

  /// --- Operations

  uint32_t get_priority() const;
  void set_priority(uint32_t _priority);

  void suspend();
  void resume();
  // abort_delay

  // xTaskNotifyStateClear
  void notify(uint32_t _value, eNotifyAction _action_e = eSetBits) const;

  bool wait(uint32_t& _notified_value,
            const std::chrono::milliseconds& _time,
            uint32_t _bits_to_clear_on_entry = 0x00,
            uint32_t _bits_to_clear_on_exit  = std::numeric_limits<uint32_t>::max());

  // light weight and faster binary or counting semaphore
  // xTaskNotifyGive
  // ulTaskNotifyTake

  /// --- Observers

  Task::id get_id() const;
  native_handle_t native_handle() const;

  state_e state() const;
  const char* name() const;
  uint16_t stack_depth() const;
  uint32_t stack_high_water_mark() const;

  /// --- Debug Purpose

  // uxTaskGetSystemState;
  // vTaskGetInfo;
  // xTaskGetHandle;

private:
  /// --- Private Functions

  static void callback(void* _arg)
  {
    /// TODO assert null pointer
    (static_cast<Task*>(_arg))->run();
  }

  state_e convert(const eTaskState _state) const;

  /// --- Private_attributs

  id id_;
  const uint16_t stack_depth_;
};

/// === Inline Definitions

inline uint32_t Task::get_priority() const { return uxTaskPriorityGet(id_.handle_); }

inline void Task::set_priority(const uint32_t _priority)
{
  vTaskPrioritySet(id_.handle_, _priority);
}

inline void Task::suspend() { vTaskSuspend(id_.handle_); }

/// xTaskResumeFromISR not very useful
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

inline Task::state_e Task::state() const { return convert(eTaskGetState(id_.handle_)); }

inline const char* Task::name() const { return pcTaskGetName(id_.handle_); }

inline uint16_t Task::stack_depth() const { return stack_depth_; }

#if (INCLUDE_uxTaskGetStackHighWaterMark == 1)
inline uint32_t Task::stack_high_water_mark() const
{
  return uxTaskGetStackHighWaterMark(id_.handle_);
}
#endif

inline Task::state_e Task::convert(const eTaskState _state) const
{
  switch (_state)
  {
  case eTaskState::eReady:
    return state_e::Ready;
  case eTaskState::eRunning:
    return state_e::Running;
  case eTaskState::eBlocked:
    return state_e::Blocked;
  case eTaskState::eSuspended:
    return state_e::Suspended;
  case eTaskState::eDeleted:
    return state_e::Deleted;
  default:
    return state_e::Invalid;
  }
}

namespace scheduler
{

enum class state_e : uint8_t
{
  Not_Started = 0,
  Running,
  Suspended,
};

namespace details
{

inline state_e convert(uint32_t _state)
{
  switch (_state)
  {
  case taskSCHEDULER_NOT_STARTED:
    return state_e::Not_Started;
  case taskSCHEDULER_RUNNING:
    return state_e::Running;
  case taskSCHEDULER_SUSPENDED:
    return state_e::Suspended;
  default:
    assert(false);
  }
  return state_e::Not_Started;
}
} // details

inline void start() { vTaskStartScheduler(); }

// vTaskEndScheduler : This has only been implemented for the x86 Real Mode PC port.

inline void suspend_all() { vTaskSuspendAll(); }

inline void resume_all() { xTaskResumeAll(); }

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
  return (is_in_ISR()) ? xTaskGetTickCountFromISR() : xTaskGetTickCount();
}

inline state_e state() { return details::convert(xTaskGetSchedulerState()); }

} // scheduler

namespace this_task
{
inline Task::id get_id() { return xTaskGetCurrentTaskHandle(); }

inline void yeld() { taskYIELD(); }

inline void sleep_for(const std::chrono::milliseconds& _time) { vTaskDelay(ticks(_time).count()); }

inline void sleep_until(const std::chrono::milliseconds& _time)
{
  uint32_t now = scheduler::tick_count();
  vTaskDelayUntil(&now, ticks(_time).count());
}

} // this_task

} // femtin

#endif
/// === END OF FILE
