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
/// \file	component_registry.hpp
/// \brief
/// \date	28/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_SYSTEM_CONTROLLER_COMPONENT_REGISTRY_HPP_
#define FEMTIN_SYSTEM_CONTROLLER_COMPONENT_REGISTRY_HPP_

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/task/task.hpp"
#include "femtin/array.hpp"
#include "icomponent.hpp"
#include "appli_conf.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace system_controller
{

/// === Class Declarations	========================================================================

class Component_Registry : public os::Task
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	Component_Registry();

protected:
	///	=== Protected Attributs	====================================================================

	femtin::Array<IComponent*, application::COMPONENT_COUNT> components_;

private:
	/// === Private Declarations	================================================================

	virtual void run();
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}
}

#endif
/// === END OF FILE	================================================================================
