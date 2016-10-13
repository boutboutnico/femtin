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

#include "freertos_wrapper/joinable_task.hpp"

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

    LED_Green.toggle();
    this_task::sleep_until(std::chrono::seconds(2));
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

/// ------------------------------------------------------------------------------------------------

Task3::Task3() : Task("Task3", STACK_SIZE, STACK_PRIORITY) {}

/// ------------------------------------------------------------------------------------------------

void foo(void* _arg);
void bar(void* _arg);
uint32_t fib(uint32_t n);
void fib_run(void* _arg);

void foo(void* _arg)
{
  UNUSED(_arg);
  // simulate expensive operation
  LED_Red.toggle();
  femtin::this_task::sleep_for(std::chrono::seconds(1));
  LED_Red.toggle();
}

void bar(void* _arg)
{
  UNUSED(_arg);
  // simulate expensive operation
  LED_Blue.toggle();
  femtin::this_task::sleep_for(std::chrono::seconds(1));
  LED_Blue.toggle();
}

uint32_t fib(uint32_t n)
{
  if (n == 0)
    return 0;
  uint32_t previous = 0;
  uint32_t current  = 1;
  for (uint32_t i = 1; i < n; ++i)
  {
    femtin::this_task::sleep_for(std::chrono::milliseconds(100));

    uint32_t next = previous + current;
    previous      = current;
    current       = next;
  }
  return current;
}

struct fib_param_t
{
  fib_param_t(uint32_t _n) : n(_n), r(0) {}
  uint32_t n;
  uint32_t r;
};

void fib_run(void* _arg)
{
  fib_param_t* fp = static_cast<fib_param_t*>(_arg);

  fp->r = fib(fp->n);
}

/// ------------------------------------------------------------------------------------------------

void Task3::run()
{
  {
    Joinable_Task jtask1("jtask1", configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 4, foo, nullptr);
    Joinable_Task jtask2("jtask2", configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 4, bar, nullptr);

    jtask1.join();
    jtask2.join();
  }

  {
    // F10=55
    // F25 = 75025
    fib_param_t fb(10);
    Joinable_Task jtask_fib(
      "jtask_fib", configMINIMAL_STACK_SIZE, tskIDLE_PRIORITY + 4, fib_run, &fb);
    jtask_fib.join();
  }

  for (;;)
  {
    this_task::sleep_for(std::chrono::seconds(10));
  }
}

/// === END OF FILE
