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
/// \file	task_test.cpp
/// \brief
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================

#include "task_test.hpp"
using namespace femtin::demo;

/// === Includes

#include "bsp/led/led.hpp"

/// === Namespaces

using namespace board::led;

/// === Public Definitions

Task1::Task1() : Task("Task1", STACK_SIZE, STACK_PRIORITY) {}

/// ------------------------------------------------------------------------------------------------

void Task1::run()
{
  for (;;)
  {
    LED_Green.toggle();
    this_task::sleep_for(std::chrono::seconds(1));
  }
}

/// ------------------------------------------------------------------------------------------------

Task2::Task2() : Task("Task2", STACK_SIZE, STACK_PRIORITY) {}

/// ------------------------------------------------------------------------------------------------

void Task2::run()
{
  for (;;)
  {
    LED_Orange.toggle();
    this_task::sleep_for(std::chrono::milliseconds(500));
  }
}

/// === END OF FILE
