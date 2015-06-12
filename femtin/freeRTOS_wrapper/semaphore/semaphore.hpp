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
/// \file	semaphore.hpp
/// \brief	Cpp wrapper around FreeRTOS semaphore
/// \date	17/11/2014
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_SEMAPHORE_HPP_
#define FEMTIN_SEMAPHORE_HPP_

/// === Includes	================================================================================

#include "FreeRTOS.h"
#include "semphr.h"
#include "femtin/unit/base_type/time_unit_type.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace os
{

/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class Semaphore
{
public:
	/// === Public Declarations	====================================================================

	Semaphore(uint8_t n_token);

	virtual bool take(unit::millisecond timeout);
	virtual bool takeFromISR();

	virtual bool give();
	virtual bool giveFromISR();

private:
	/// === Private Attributes	====================================================================

	SemaphoreHandle_t handle_;
};

#pragma GCC diagnostic pop

/// === Inline Definitions	========================================================================

///	------------------------------------------------------------------------------------------------
}/// os
}/// femtin
#endif
/// === END OF FILE	================================================================================
