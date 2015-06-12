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
/// === Includes	================================================================================
#include <iostream>
#include <assert.h>

#include "femtin/mpl/test/mpl.hpp"
#include "femtin/unit/test/copy_constructor.hpp"
#include "femtin/unit/test/operator_plus_egal.hpp"
#include "femtin/unit/test/operator_plus_a_b.hpp"
#include "femtin/unit/test/operator_mul_egal.hpp"
#include "femtin/unit/test/operator_mul_a_b.hpp"
#include "femtin/unit/test/operator_div_egal.hpp"
#include "femtin/unit/test/operator_div_a_b.hpp"
#include "femtin/unit/test/speed_test.hpp"
#include "femtin/unit/test/electrical_test.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace femtin::test;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

int main()
{
	cout << "=====	Femtin MPL	=====" << endl;

	power();
	static_if();
	scale_converter();

	cout << "=====	Femtin Unit	=====" << endl;

	copy_constructor();
	operator_plus_egal();
	operator_plus_a_b();
	operator_mul_egal();
	operator_mul_a_b();
	operator_div_egal();
	operator_div_a_b();
	speed_test();
	electrical_test();

	cout << "All tests:\t\t Pass" << endl;

	return 0;
}

/// === END OF FILE	================================================================================

