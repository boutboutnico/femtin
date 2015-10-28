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
/// \file	component_registry.cpp
/// \brief
/// \date	28/10/2015
/// \author	nboutin
///
/// ================================================================================================
#include "component_registry.hpp"
using namespace femtin::system_controller;

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "bsp/trace_uart/trace_uart.hpp"

/// === Namespaces	================================================================================

using namespace femtin;
using namespace board::mcu;
using namespace application;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

Component_Registry::Component_Registry()
		: 	Task(application::COMPONENT_REGISTRY_TASK_NAME.c_str(),
					application::COMPONENT_REGISTRY_TASK_STACK_SIZE,
					application::COMPONENT_REGISTRY_TASK_PRIO),
			components_()
{
}

/// ------------------------------------------------------------------------------------------------

void Component_Registry::run()
{
	/// --- Initialization	------------------------------------------------------------------------

	trace << "==========\tStart\t==========" << endl;

	/// TODO test with for(IComponent* comp : components) ???
	for (uint8_t i = 0; i < COMPONENT_COUNT; i++)
	{
		components_[i]->initialize(*this) ?
				trace << "[" << components_[i]->name().c_str() << "]\tInitialized" << endl :
				trace << "[" << components_[i]->name().c_str() << "]\t!!! NOT initialized !!!"
						<< endl;
	}

	for (uint8_t i = 0; i < COMPONENT_COUNT; i++)
	{
		components_[i]->start() ?
				trace << "[" << components_[i]->name().c_str() << "]\tStarted " << ios_base::hex
						<< reinterpret_cast<uint32_t>(components_[i]->get_task().handle())
						<< ios_base::dec << endl :
				trace << "[" << components_[i]->name().c_str() << "]\t!!! NOT started !!!" << endl;
	}

	trace << Task::number_of_tasks() << " tasks are running" << endl;
	assert(TASK_COUNT == Task::number_of_tasks());

	/// --- Infinite Loop	------------------------------------------------------------------------

	char buffer[40 * TASK_COUNT];
	femtin::Array<TaskStatus_t, TASK_COUNT> task_status;

	for (;;)
	{
		Task::list_custom(buffer, task_status);
		trace << "Name\tState\tPrio\tNum\tStack" << endl;
		trace << buffer << endl;

		femtin::os::task_delay_until(unit::second(10));
	}
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
