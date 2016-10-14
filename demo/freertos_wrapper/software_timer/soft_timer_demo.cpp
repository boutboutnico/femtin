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
/// \file	soft_timer_demo.cpp
/// \brief
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================

#include "soft_timer_demo.hpp"
using namespace femtin::demo;

/// === Includes

#include "bsp/led/led.hpp"

#include "freertos_wrapper/joinable_task.hpp"

/// === Namespaces

using namespace board::led;

/// === Public Definitions

Task1::Task1()
  : Task("Task1", STACK_SIZE, STACK_PRIORITY)
  , timer1_("Timer1", std::chrono::seconds(1), true, Task1::callback)
  , timer2_("Timer2", std::chrono::milliseconds(500), true, Task1::callback)
{
}

/// ------------------------------------------------------------------------------------------------

void Task1::run()
{
  timer1_.start();
  timer2_.start();

  for (;;)
  {
    LED_Green.toggle();
    this_task::sleep_for(std::chrono::seconds(1));
  }
}

/// ------------------------------------------------------------------------------------------------

void Task1::callback(native_handle_t _htimer)
{
  UNUSED(_htimer);
  LED_Blue.toggle();
}

/// ------------------------------------------------------------------------------------------------

Task2::Task2() : Task("Task2", STACK_SIZE, STACK_PRIORITY) {}

/// ------------------------------------------------------------------------------------------------

void Task2::run()
{
  for (;;)
  {
    LED_Orange.toggle();
    this_task::sleep_for(std::chrono::milliseconds(250));
  }
}

/// === END OF FILE
