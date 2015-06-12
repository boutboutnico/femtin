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
/// \file	average.hpp
/// \brief	Average tools
/// \date	04/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_AVERAGE_HPP_
#define FEMTIN_AVERAGE_HPP_

/// ===	Includes	================================================================================
/// ===	Namespaces	================================================================================

namespace femtin
{

/// X_avg_0 = X_0
///
/// 			X_avg_n-1 * (n - 1) + X_n
/// X_avg_n = -----------------------------
///						n
inline uint32_t simple_moving_average(const uint32_t _n, const uint32_t _val, const uint32_t _avg)
{
	return ((_avg * (_n - 1) + _val) / (_n));
}

}    /// Namespace femtin

#endif	/// FEMTIN_AVERAGE_HPP_
/// === END OF FILE	================================================================================
