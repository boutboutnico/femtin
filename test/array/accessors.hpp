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
/// \file	accessors.hpp
/// \brief	Array accessors tests
/// \date	15/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TEST_ARRAY_ACCESSORS_HPP_
#define FEMTIN_TEST_ARRAY_ACCESSORS_HPP_

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

void accessors()
{
	{
		Array<uint8_t, 10> a;

		for (size_t i = 0; i < 10; i++)
		{
			a[i] = i * 2;
			assert(a[i] == i * 2);
			assert(*(a.data() + i) == i * 2);
		}
	}

	std::cout << __func__ << std::endl;
}

/// ------------------------------------------------------------------------------------------------

///	Array_ptr<T> subarray(size_t _pos = 0, size_t _count = L)
void sub_array()
{
	{
		Array<uint8_t, 10> a;

		for (size_t i = 0; i < 10; i++)
		{
			a[i] = i;
		}

		Array_ptr<uint8_t> ap = a.subarray();

		for (size_t i = 0; i < 10; i++)
		{
			assert(ap[i] == i);
		}
	}
	{
		Array<uint8_t, 10> a;

		for (size_t i = 0; i < 10; i++)
		{
			a[i] = i;
		}

		Array_ptr<uint8_t> ap = a.subarray(3);

		for (size_t i = 0; i < 10 - 3; i++)
		{
			assert(ap[i] == i + 3);
		}
	}
	{
		Array<uint8_t, 10> a;

		for (size_t i = 0; i < 10; i++)
		{
			a[i] = i;
		}

		Array_ptr<uint8_t> ap = a.subarray(4, 6);

		for (size_t i = 0; i < 3; i++)
		{
			assert(ap[i] == i + 4);
		}
	}

	std::cout << __func__ << std::endl;
}

/// ------------------------------------------------------------------------------------------------
}
}
}

#endif
/// === END OF FILE	================================================================================
