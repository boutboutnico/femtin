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
#ifndef FEMTIN_TEST_MPL_ALL_TESTS_HPP_
#define FEMTIN_TEST_MPL_ALL_TESTS_HPP_

/// === Includes	================================================================================

#include "mpl.hpp"

/// === Namespaces	================================================================================
namespace femtin
{
namespace test
{
namespace mpl
{

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

void mpl_all()
{
	cout << "\n=== MPL" << endl;
	power();
	static_if();
	scale_converter();
}

}
}
}
#endif
/// === END OF FILE	================================================================================
