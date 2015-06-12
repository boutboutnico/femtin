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
/// \file	mutex.hpp
/// \brief
/// \date	30/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_MUTEX_HPP_
#define FEMTIN_MUTEX_HPP_

/// === Includes	================================================================================

#include "FreeRTOS.h"
#include "semphr.h"
#include "femtin/freeRTOS_wrapper/freeRTOS_wrapper.hpp"

/// === Namespaces	================================================================================

namespace os
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class Mutex
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	Mutex();

	virtual bool acquire(TickType_t timeout_ms = TIMEOUT_MAX);
	virtual bool acquireFromISR();

	virtual bool release();
	virtual bool releaseFromISR();

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	SemaphoreHandle_t handle_;
};

#pragma GCC diagnostic pop

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// os

#endif	/// FEMTIN_MUTEX_HPP_
/// === END OF FILE	================================================================================
