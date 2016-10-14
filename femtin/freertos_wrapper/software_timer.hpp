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
/// \file	software_timer.hpp
/// \brief	Cpp wrapper around FreeRTOS software timer
/// \date	19/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_FREERTOS_WRAPPER_SOFTWARE_TIMER_HPP_
#define FEMTIN_FREERTOS_WRAPPER_SOFTWARE_TIMER_HPP_

/// === Includes

#include <cassert>

#include "FreeRTOS.h"
#include "timers.h"

///	=== Namespaces

namespace femtin
{

/// === Class Declarations

class Software_Timer
{
public:
  /// --- Public Typedef

  typedef TimerHandle_t native_handle_t;
  /// TODO Change to have user_param by using vTimerSetTimerId
  typedef void (*callback_t)(native_handle_t _htimer);

  /// --- Public Declarations

  /// TODO use gsl for zstring
  Software_Timer(const char* _name,
                 const std::chrono::milliseconds& _time,
                 bool _auto_reload,
                 callback_t _callback)
  {
    handle_ = xTimerCreate(_name, ticks(_time).count(), _auto_reload, this, _callback);
    assert(handle_);
  }
  ~Software_Timer()
  {
    auto r = xTimerDelete(handle_, 0);
    assert(r == pdPASS);
  }

  /// --- Operations

  void start();
  void stop();
  void change(const std::chrono::milliseconds& _time);
  void reset();

  /// --- Observers

  native_handle_t native_handle() const;
  const char* name() const;
  bool is_active() const;
  std::chrono::milliseconds get_period() const;
  std::chrono::milliseconds remaining() const;

private:
  /// --- Private Declarations

  native_handle_t handle_;
};
/// === Inlines Definitions

inline void Software_Timer::start()
{
  auto r = xTimerStart(handle_, 0);
  assert(r == pdPASS);
}

inline void Software_Timer::stop()
{
  auto r = xTimerStop(handle_, 0);
  assert(r == pdPASS);
}

inline void Software_Timer::change(const std::chrono::milliseconds& _time)
{
  auto r = xTimerChangePeriod(handle_, ticks(_time).count(), 0);
  assert(r == pdPASS);
}

inline void Software_Timer::reset()
{
  auto r = xTimerReset(handle_, 0);
  assert(r == pdPASS);
}

inline Software_Timer::native_handle_t Software_Timer::native_handle() const { return handle_; }

inline const char* Software_Timer::name() const { return pcTimerGetName(handle_); }

inline bool Software_Timer::is_active() const { return xTimerIsTimerActive(handle_); }

inline std::chrono::milliseconds Software_Timer::get_period() const
{
  return ticks(xTimerGetPeriod(handle_));
}

inline std::chrono::milliseconds Software_Timer::remaining() const
{
  return ticks(xTimerGetExpiryTime(handle_) - scheduler::tick_count());
}

namespace software_timer
{
inline Task::id get_timer_daemon_task_id() { return xTimerGetTimerDaemonTaskHandle(); }
}
}
#endif
///	===	END OF FILE
