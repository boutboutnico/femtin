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
/// \file	joinable_task.hpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_JOINABLE_TASK_HPP_
#define FEMTIN_JOINABLE_TASK_HPP_

/// === Includes

#include "FreeRTOS.h"
#include "task.h"

#include "../freertos_wrapper.hpp"

/// === Namespaces

namespace femtin
{
namespace os
{

/// === Class Declarations

class Joinable_Task
{
public:
  /// --- Public Types

  typedef TaskHandle_t handle_t;

  typedef void* arg_t;
  typedef void (*pfunction_t)(arg_t);

  /// --- Public FunctJoinable_Task
  Joinable_Task(const char* _name,
                uint16_t _stack_depth,
                uint16_t _priority,
                pfunction_t _pfunction,
                void* _arg)
    : pfunction_(_pfunction), arg_(_arg), handle_(nullptr), stack_depth_(_stack_depth)
  {
    /// TODO assert creation
    xTaskCreate(Joinable_Task::callback, _name, _stack_depth, this, _priority, &handle_);
  }

  ~Joinable_Task() { vTaskDelete(handle_); }

  /// --- Operations

  /// @warning must be called from a task
  void join()
  {
    /// TODO assert deadlock against task waiting for itself
  }

private:
  /// --- Private Functions

  static void callback(void* _arg)
  {
    Joinable_Task* task = static_cast<Joinable_Task*>(_arg);
    task->pfunction_(task->arg_);
  }

  /// --- Private Attributs

  pfunction_t pfunction_;
  arg_t arg_;

  handle_t handle_;
  const uint16_t stack_depth_;
};
/// === Inlines Definitions
}
}
#endif
/// === END OF FILE