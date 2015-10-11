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
/// \file	default_constructor.hpp
/// \brief	Array default constructor tests
/// \date	15/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TEST_ARRAY_DEFAULT_CONSTRUCTOR_HPP_
#define FEMTIN_TEST_ARRAY_DEFAULT_CONSTRUCTOR_HPP_

/// === Includes	================================================================================

#include <iostream>
#include "../femtin/array.hpp"

/// === Namespaces	================================================================================

namespace femtin
{
namespace test
{
namespace array
{

/// ------------------------------------------------------------------------------------------------

void default_constructor()
{
	{
		Array<uint8_t, 0> a;
		assert(a.max_size() == 0);
	}
	{
		Array<uint8_t, 10> a;
		assert(a.max_size() == 10);
	}
	{
		Array<uint16_t, 5> a;
		assert(a.max_size() == 5);
	}
	{
		Array<uint32_t, 32> a;
		assert(a.max_size() == 32);
	}

	std::cout << __func__ << std::endl;
}

/// ------------------------------------------------------------------------------------------------
}
}
}

#endif
/// === END OF FILE	================================================================================
