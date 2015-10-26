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
/// \file	freeRTOS_wrapper.hpp
/// \brief	Cpp wrapper around FreeRTOS tools
/// \date	20/03/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_FREERTOS_WRAPPER_HPP_
#define FEMTIN_FREERTOS_WRAPPER_HPP_

/// === Includes	================================================================================

#include "FreeRTOS.h"

/// === Namespaces	================================================================================

namespace femtin
{
namespace os
{

const TickType_t TIMEOUT_MAX = portMAX_DELAY;

}
}
#endif
/// === END OF FILE	================================================================================
