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
/// \file	task_test.hpp
/// \brief
/// \date	11/10/2016
/// \author	nboutin
///
/// ================================================================================================

#ifndef TASK_TEST_HPP
#define TASK_TEST_HPP

/// === Includes

#include "freertos_wrapper/task/task.hpp"

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

/// === Class Declarations

class Task3 : public femtin::Task
{
public:
  /// --- Public Constants

  static const uint16_t STACK_SIZE     = configMINIMAL_STACK_SIZE;
  static const uint16_t STACK_PRIORITY = (tskIDLE_PRIORITY + 3);

  /// --- Public Declarations

  Task3();
  virtual void run();
};
}
}

#endif
/// === END OF FILE
