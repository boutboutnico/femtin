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
/// \file	array_all_tests.hpp
/// \brief	Array all tests launcher
/// \date	15/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TEST_ARRAY_ALL_TEST_HPP_
#define FEMTIN_TEST_ARRAY_ALL_TEST_HPP_

/// === Includes	================================================================================

#include "default_constructor.hpp"
#include "accessors.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace test
{
namespace array
{

/// ------------------------------------------------------------------------------------------------

void array_all()
{
//	cout << "\n=== Array" << endl;

	default_constructor();
	accessors();
	sub_array();
}

/// ------------------------------------------------------------------------------------------------
}
}
}

#endif
/// === END OF FILE	================================================================================
