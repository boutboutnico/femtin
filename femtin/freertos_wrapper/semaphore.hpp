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
/// \file	semaphore.hpp
/// \brief	Cpp wrapper around FreeRTOS semaphore
/// \date	17/11/2014
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_SEMAPHORE_HPP_
#define FEMTIN_SEMAPHORE_HPP_

/// === Includes

#include <assert.h>

#include "FreeRTOS.h"
#include "semphr.h"

/// === Namespaces

namespace femtin
{

/// === Class Declarations

class Semaphore
{
public:
  /// --- Public Types

  typedef SemaphoreHandle_t native_handle_t;

  /// --- Public Declarations

  Semaphore()
  {
    handle_ = xSemaphoreCreateBinary();
    assert(handle_ != NULL);
  }
  explicit Semaphore(uint8_t _max_token, uint8_t _init_token)
  {
    handle_ = xSemaphoreCreateCounting(_max_token, _init_token);
    assert(handle_ != NULL);
  }
  ~Semaphore() { vSemaphoreDelete(handle_); }

  Semaphore(const Semaphore&) = delete;
  Semaphore& operator=(const Semaphore&) = delete;

  void take();
  bool try_take();
  bool try_take_for(const std::chrono::milliseconds& _time);

  void give();

private:
  /// --- Private Attributes

  native_handle_t handle_;
};

/// === Inline Definitions

inline void Semaphore::take() { xSemaphoreTake(handle_, TIMEOUT_MAX); }

inline bool Semaphore::try_take() { return (xSemaphoreTake(handle_, 0)) == pdTRUE ? true : false; }

inline bool Semaphore::try_take_for(const std::chrono::milliseconds& _time)
{
  return (xSemaphoreTake(handle_, ticks(_time).count()) == pdTRUE) ? true : false;
}

inline void Semaphore::give()
{
  auto r = xSemaphoreGive(handle_);
  assert(r == pdTRUE);
}

// bool Semaphore::takeFromISR()
//{
//  BaseType_t pxHigherPriorityTaskWoken;
//
//  return xSemaphoreTakeFromISR(handle_, &pxHigherPriorityTaskWoken);
//}

// bool Semaphore::giveFromISR()
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

///	------------------------------------------------------------------------------------------------
}
#endif
/// === END OF FILE
