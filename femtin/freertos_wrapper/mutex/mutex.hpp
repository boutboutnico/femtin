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
/// \file	mutex.hpp
/// \brief
/// \date	30/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_MUTEX_HPP_
#define FEMTIN_MUTEX_HPP_

/// === Includes

#include "FreeRTOS.h"
#include "semphr.h"

/// === Namespaces

namespace femtin
{

/// === Class Declarations

class Mutex
{
public:
  /// --- Public Types

  typedef SemaphoreHandle_t native_handle_t;

  /// --- Public Declarations

  /// TODO assert creation
  Mutex() { handle_ = xSemaphoreCreateMutex(); }

  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  /// --- Operations

  /// Locks the mutex. If another thread has already locked the mutex, a call to lock will block
  /// execution until the lock is acquired.
  void lock();

  /// Tries to lock the mutex. Returns immediately.
  /// successful lock acquisition returns true, otherwise returns false.
  bool try_lock();

  /// Unlocks the mutex.
  void unlock();

  /// --- Observers

  native_handle_t native_handle() const;

protected:
  /// --- Protected Attributes
  native_handle_t handle_;
};

/// === Inlines Declarations

inline void Mutex::lock()
{
  while (xSemaphoreTake(handle_, TIMEOUT_MAX) == pdFALSE)
    ;
}

inline bool Mutex::try_lock()
{
  return (xSemaphoreTake(handle_, TIMEOUT_MAX) == pdTRUE) ? true : false;
}

inline void Mutex::unlock() { xSemaphoreGive(handle_); }

inline Mutex::native_handle_t Mutex::native_handle() const { return handle_; }

// bool Mutex::acquireFromISR()
//{
//  BaseType_t pxHigherPriorityTaskWoken;
//
//  return xSemaphoreTakeFromISR(handle_, &pxHigherPriorityTaskWoken);
//}

// bool Mutex::releaseFromISR()
//{
//  /// From FreeRTOS V7.3.0 pxHigherPriorityTaskWoken
//  /// is an optional parameter and can be set to NULL.
//  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//  bool result                         = false;
//
//  result = xSemaphoreGiveFromISR(handle_, NULL);
//
//  vTaskNotifyGiveFromISR(handle_, &xHigherPriorityTaskWoken);
//  portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
//
//  return result;
//}

class Timed_Mutex : public Mutex
{
public:
  bool try_lock_for(const std::chrono::milliseconds& _time);
};

inline bool Timed_Mutex::try_lock_for(const std::chrono::milliseconds& _time)
{
  return (xSemaphoreTake(handle_, ticks(_time).count()) == pdTRUE) ? true : false;
}

struct adopt_lock_t // Tag for already locked mutex
{
};

constexpr adopt_lock_t adopt_lock{};

/// Acquire the mutex here with a constructor call, then release with
/// the destructor call in accordance with RAII style.
template <typename _Mutex>
class lock_guard
{
public:
  typedef _Mutex mutex_t;

  explicit lock_guard(mutex_t& __m) : mutex_(__m) { mutex_.lock(); }

  ~lock_guard() { mutex_.unlock(); }

  lock_guard(mutex_t& __m, adopt_lock_t) : mutex_(__m) {} // Already locked

  lock_guard(const lock_guard&) = delete;
  lock_guard& operator=(const lock_guard&) = delete;

private:
  mutex_t& mutex_;
};

/// ------------------------------------------------------------------------------------------------
}

#endif
/// === END OF FILE
