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
/// \file	soft_timer_demo.hpp
/// \brief
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================

#ifndef TASK_SOFT_TIMER_DEMO_HPP
#define TASK_SOFT_TIMER_DEMO_HPP

/// === Includes

#include "freertos_wrapper/software_timer.hpp"
#include "freertos_wrapper/task.hpp"

/// === Namespaces

namespace femtin
{
namespace demo
{

/// === Class Declarations

class Task1 : public femtin::Task
{
public:
  /// --- Public Constants

  static const uint16_t STACK_SIZE     = configMINIMAL_STACK_SIZE;
  static const uint16_t STACK_PRIORITY = (tskIDLE_PRIORITY + 1);

  /// --- Public Declarations

  Task1();
  virtual void run();

private:
  /// --- Private Functions

  static void callback(native_handle_t _htimer);

  /// --- Private Attributs

  Software_Timer timer1_;
  Software_Timer timer2_;
};

/// === Class Declarations

class Task2 : public femtin::Task
{
public:
  /// --- Public Constants

  static const uint16_t STACK_SIZE     = configMINIMAL_STACK_SIZE;
  static const uint16_t STACK_PRIORITY = (tskIDLE_PRIORITY + 2);

  /// --- Public Declarations

  Task2();
  virtual void run();
};
}
}

#endif
/// === END OF FILE
