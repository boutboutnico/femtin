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
/// \file	length_unit_type.hpp
/// \brief
/// \date	03/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_UNIT_BASE_TYPE_LENGTH_UNIT_TYPE_HPP_
#define FEMTIN_UNIT_BASE_TYPE_LENGTH_UNIT_TYPE_HPP_

/// === Includes	================================================================================

#include "../unit.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace unit
{

/// Length	Mass Time Intensity

/// ---	Lenght	------------------------------------------------------------------------------------

typedef Unit<uint32_t, 1, 0, 0, 0, 6> megameter;
typedef Unit<uint32_t, 1, 0, 0, 0, 3> kilometer;
typedef Unit<uint32_t, 1, 0, 0, 0, 2> hectometer;
typedef Unit<uint32_t, 1, 0, 0, 0, 1> decameter;
typedef Unit<uint32_t, 1, 0, 0, 0, 0> meter;
typedef Unit<uint32_t, 1, 0, 0, 0, -1> decimeter;
typedef Unit<uint32_t, 1, 0, 0, 0, -2> centimeter;
typedef Unit<uint32_t, 1, 0, 0, 0, -3> millimeter;
typedef Unit<uint32_t, 1, 0, 0, 0, -6> micrometer;
typedef Unit<uint32_t, 1, 0, 0, 0, -9> nanometer;

/// ------------------------------------------------------------------------------------------------
}///unit
}    ///femtin

#endif
/// === END OF FILE	================================================================================
