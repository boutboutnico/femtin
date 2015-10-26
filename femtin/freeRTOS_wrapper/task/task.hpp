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
/// \file	task.hpp
/// \brief	Cpp wrapper around FreeRTOS task
/// \date	31/03/2014
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TASK_HPP_
#define FEMTIN_TASK_HPP_

/// === Includes ===================================================================================

#include "FreeRTOS.h"
#include "task.h"

/// === Namespaces	================================================================================

namespace femtin
{
namespace os
{

/// === Class Declarations	========================================================================

class Task
{
public:
	/// Public Declarations	========================================================================

	Task(const char* name, const uint16_t stack_depth, const UBaseType_t priority);

	virtual void run() = 0;

	void suspend();

	void resume();

	inline TaskHandle_t handle() const;

private:
	/// Private Declarations	====================================================================

	static void callback(void* param);

	/// Private Attributs	========================================================================

	TaskHandle_t handle_;

};

/// === Inline Definitons	========================================================================

inline TaskHandle_t Task::handle() const
{
	return handle_;
}

/// ------------------------------------------------------------------------------------------------
}
}
#endif
/// === END OF FILE	================================================================================
