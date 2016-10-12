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
/// \file	task_util.hpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	12/12/2016
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TASK_UTIL_HPP
#define FEMTIN_TASK_UTIL_HPP

/// === Includes

#include <vector>

#include "FreeRTOS.h"
#include "task.h"

/// === Namespaces

namespace femtin
{
/// === Class Declarations

class Task_Util
{
public:
  /// --- Public Functions

  /// TODO Redesign
  static void list_custom(/*char* _write_buffer, std::vector<TaskStatus_t>& _working_buffer*/);
};
}
#endif
/// === END OF FILE
