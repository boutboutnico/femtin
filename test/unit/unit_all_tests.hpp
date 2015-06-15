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
#ifndef FEMTIN_TEST_UNIT_TESTS_HPP_
#define FEMTIN_TEST_UNIT_ALL_TESTS_HPP_

/// === Includes	================================================================================

#include <iostream>

#include "copy_constructor.hpp"
#include "operator_plus_egal.hpp"
#include "operator_plus_a_b.hpp"
#include "operator_mul_egal.hpp"
#include "operator_mul_a_b.hpp"
#include "operator_div_egal.hpp"
#include "operator_div_a_b.hpp"
#include "speed_test.hpp"
#include "electrical_test.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
namespace unit
{

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

void unit_all()
{
	cout << "\n=== Unit" << endl;

	copy_constructor();
	operator_plus_egal();
	operator_plus_a_b();
	operator_mul_egal();
	operator_mul_a_b();
	operator_div_egal();
	operator_div_a_b();
	speed_test();
	electrical_test();
}

}
}
}
#endif
/// === END OF FILE	================================================================================

