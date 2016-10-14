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
/// \file	main.cpp
/// \brief
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================

/// === Includes

#include "freertos_wrapper/task.hpp"

#include "task_test.hpp"

/// === Namespaces

using namespace femtin::demo;

/// === Public Definitions

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

/// ------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.

  static Task1 task1;
  static Task2 task2;
  static Task3 task3;

  femtin::scheduler::start(); // should never return
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic pop

/// === END OF FILE
