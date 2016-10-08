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
/// \file	crc7.hpp
/// \brief	CRC7 calculation
/// \date	21/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_CRC_CRC7_HPP_
#define FEMTIN_CRC_CRC7_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <cstddef>

/// === Namespaces	================================================================================

namespace crc7
{

uint8_t crc7(uint8_t _crc, const uint8_t* _b, size_t _len);

}

#endif	/// FEMTIN_CRC_CRC7_HPP_
/// === END OF FILE	================================================================================
