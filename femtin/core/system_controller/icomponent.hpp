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
/// \file	icomponent.hpp
/// \brief
/// \date	28/10/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_SYSTEM_CONTROLLER_ICOMPONENT_HPP_
#define FEMTIN_SYSTEM_CONTROLLER_ICOMPONENT_HPP_

/// === Includes	================================================================================

#include "appli_conf.hpp"
#include "femtin/string.hpp"

/// === Namespaces	================================================================================

namespace femtin
{

namespace system_controller
{

/// === Forward Declarations	====================================================================

class Component_Registry;

/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class IComponent
{
public:
	/// === Public Declarations	====================================================================

	virtual const String<application::COMPONENT_NAME_LEN_MAX>& name() const = 0;

	virtual void* get_API_service()
	{
		assert(false);
		return NULL;
	}

	virtual const femtin::os::Task& get_task() const = 0;

	virtual bool initialize(Component_Registry& _comp_reg) = 0;

	virtual bool start() = 0;

};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}
}

#endif
/// === END OF FILE	================================================================================
