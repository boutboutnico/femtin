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
/// \file	freertos_wrapper.hpp
/// \brief	Cpp wrapper around FreeRTOS tools
/// \date	20/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_FREERTOS_WRAPPER_HPP_
#define FEMTIN_FREERTOS_WRAPPER_HPP_

/// === Includes ===================================================================================

#include "FreeRTOS.h"

//#ifdef STM32F407xx	/// TODO use correct define
#include "stm32f4xx_hal.h"
//#endif

/// === Namespaces =================================================================================

namespace femtin
{
namespace os
{

/// --- Public Constants

const TickType_t TIMEOUT_MAX = portMAX_DELAY;

/// --- Public Functions

inline bool is_in_ISR()
{
  //#ifdef STM32F407xx /// TODO use correct define
  return __get_IPSR() != 0;
  //#else
  //#warning is_in_ISR must be defined according to target
  //#endif
}

/// ------------------------------------------------------------------------------------------------
}
}
#endif
/// === END OF FILE ================================================================================
