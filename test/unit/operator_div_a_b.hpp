///
/// \file	operator_div_a_b.hpp
///	\brief	
///	\date	05/06/2015
/// \author	nboutin
///
#ifndef TEST_OPERATOR_DIV_A_B_HPP_
#define TEST_OPERATOR_DIV_A_B_HPP_

/// === Includes	================================================================================

#include <assert.h>
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
/// a@b 	(a).operator@ (b) 	operator@ (a, b)

void operator_div_a_b()
{
	/// One dimension
	{
		meter m1(12);
		meter m2(3);

		dimensionless d3 = m1 / m2;
		dimensionless d4 = m2 / m1;

		assert(d3.value() == 4);
		assert(d4.value() == 0);
	}

	{
		meter2 m2(12);
		meter m1(3);

		meter m3 = m2 / m1;

		assert(m3.value() == 4);
	}
#if 0
	/// One dimension - prefixes factor
	{
		decimeter dm1(2);
		decimeter dm2(3);

		decimeter2 dm3 = dm1 * dm2;
		decimeter2 dm4 = dm2 * dm1;

		assert(dm3.value() == 6);
		assert(dm4.value() == 6);
	}
	/// Two dimension
	{
		meter m(2);
		decimeter dm(30);

		meter2 m2 = m * meter(dm);
		meter2 m3 = meter(dm) * m;
		assert(m2.value() == 6);
		assert(m3.value() == 6);

		decimeter2 dm2 = decimeter(m) * dm;
		decimeter2 dm3 = dm * decimeter(m);
		assert(dm2.value() == 600);
		assert(dm3.value() == 600);
	}
	/// Three dimension
	{
		meter m(2);
		decimeter dm(34);
		centimeter cm(567);

		centimeter2 cm2 = dm * decimeter(m);
		centimeter2 cm3 = decimeter(m) * dm;

		assert(cm2.value() == 34 * 20 * 100);
		assert(cm3.value() == 34 * 20 * 100);

		decimeter2 dm2 = centimeter(m) * cm;
		decimeter2 dm3 = cm * centimeter(m);

		assert(dm2.value() == 200 * 567 / 100);
		assert(dm3.value() == 200 * 567 / 100);

		meter2 m2 = cm * centimeter(dm);
		meter2 m3 = centimeter(dm) * cm;

		assert(m2.value() == 567 * 340 / (100*100));
		assert(m3.value() == 567 * 340 / (100*100));
	}
#endif
	cout << __func__ << endl;
}
/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
