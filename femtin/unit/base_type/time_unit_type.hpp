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
/// \file	time_unit_type.hpp
/// \brief
/// \date	03/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_UNIT_BASE_TYPE_TIME_UNIT_TYPE_HPP_
#define FEMTIN_UNIT_BASE_TYPE_TIME_UNIT_TYPE_HPP_

/// === Includes	================================================================================

#include "femtin/unit/unit.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace unit
{

/// Length	Mass Time Intensity

/// ---	Time	------------------------------------------------------------------------------------
typedef Unit<uint32_t, 0, 0, 1, 0, 0> second;
typedef Unit<uint32_t, 0, 0, 1, 0, -3> millisecond;
typedef Unit<uint32_t, 0, 0, 1, 0, -6> microsecond;
typedef Unit<uint32_t, 0, 0, 1, 0, -9> nanosecond;

/// ------------------------------------------------------------------------------------------------
}///unit
}    ///femtin

#endif
/// === END OF FILE	================================================================================
