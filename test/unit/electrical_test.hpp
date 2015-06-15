///
/// \file	speed_test.hpp
///	\brief	
///	\date	05/06/2015
/// \author	nboutin
///
#ifndef TEST_ELECTRICAL_TEST_HPP_
#define TEST_ELECTRICAL_TEST_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "unit/base_type/time_unit_type.hpp"
#include "unit/base_type/intensity_unit_type.hpp"
#include "unit/unit_type.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace femtin::unit;

namespace femtin
{
namespace test
{
namespace unit
{

void electrical_test()
{
	{
		/// U = R.I
		volt v(230);
		ohm r(100);

		ampere i = v / r;

		assert(i.value() == 2);
	}
	{
//		millivolt mv(5000);
//		ohm r(4700);
//
//		cout << milliohm(r).value() << endl;
//
//		milliampere mi = mv / milliohm(r);
//		assert(mi.value() == 1);
	}
	{
		volt v(5);
		ampere i(12);

		watt p = v * i;
		assert(p.value() == 60);
	}

	cout << __func__ << endl;
}
/// ------------------------------------------------------------------------------------------------
}
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
