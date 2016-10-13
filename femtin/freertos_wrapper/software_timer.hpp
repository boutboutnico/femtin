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
  typedef void (*callback_t)(native_handle_t _htimer);

  /// --- Public Declarations

  /// TODO use gsl for zstring
  Software_Timer(char const* const _name,
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

  bool start();
  bool stop();
  bool change(const std::chrono::milliseconds& _time);
  bool reset();

  /// --- Observers

  bool is_active() const;

private:
  /// --- Private Declarations

  native_handle_t handle_;
};
/// === Inlines Definitions

inline bool Software_Timer::start() { return xTimerStart(handle_, 0); }

inline bool Software_Timer::stop() { return xTimerStop(handle_, 0); }

inline bool Software_Timer::change(const std::chrono::milliseconds& _time)
{
  return xTimerChangePeriod(handle_, ticks(_time).count(), 0);
}

inline bool Software_Timer::reset() { return xTimerReset(handle_, 0); }

inline bool Software_Timer::is_active() const { return xTimerIsTimerActive(handle_); }
}
#endif
///	===	END OF FILE
