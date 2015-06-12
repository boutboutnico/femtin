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
/// \file	algorithm.hpp
/// \brief	Frequently used algorithm
/// \date	11/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_ALGORITHM_HPP_
#define FEMTIN_ALGORITHM_HPP_

/// === Includes	================================================================================
/// === Namespaces	================================================================================

namespace femtin
{

/// ------------------------------------------------------------------------------------------------

/// \brief	return minimal value between a and b
template<typename T>
inline T min(T _a, T _b)
{
	return (_a < _b) ? _a : _b;
}

/// ------------------------------------------------------------------------------------------------
}/// femtin

#endif	/// FEMTIN_ALGORITHM_HPP_
/// === END OF FILE	================================================================================
