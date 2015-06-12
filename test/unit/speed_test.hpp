///
/// \file	speed_test.hpp
///	\brief	
///	\date	05/06/2015
/// \author	nboutin
///
#ifndef TEST_SPEED_TEST_HPP_
#define TEST_SPEED_TEST_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "femtin/unit/base_type/time_unit_type.hpp"
#include "femtin/unit/unit_type.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace femtin::unit;

namespace femtin
{
namespace test
{

void speed_test()
{
	{
		meter m(100);
		second s(10);

		speed sp = m / s;
		assert(sp.value() == 10);
	}
	{
		millimeter mm (100000);
		second s(10);

		speed sp = mm / millisecond(s);
		speed sp2 = meter(mm) / s;

		assert(sp.value() == 10);
		assert(sp2.value() == 10);
	}

	cout << "speed test:\t\t Pass" << endl;
}
/// ------------------------------------------------------------------------------------------------
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
