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
/// \file	main.cpp
///	\brief
///	\date	04/06/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TEST_RING_BUFFER_ALL_TESTS_HPP_
#define FEMTIN_TEST_RING_BUFFER_ALL_TESTS_HPP_

/// === Includes	================================================================================

#include "constructor.hpp"
#include "read_write.hpp"
#include "operations.hpp"

/// === Namespaces	================================================================================
namespace femtin
{
namespace test
{
namespace ring_buffer
{

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

void ring_buffer_all()
{
	cout << "\n=== Ring Buffer" << endl;

	default_constructor();
	copy_constructor();
	operations();
	read_write();
	read_write_count_test();
}

}
}
}
#endif
/// === END OF FILE	================================================================================

