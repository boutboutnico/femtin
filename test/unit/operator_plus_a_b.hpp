///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef TEST_OPERATOR_PLUS_A_B_HPP_
#define TEST_OPERATOR_PLUS_A_B_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "../femtin/unit/unit_type.hpp"

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

void operator_plus_a_b()
{
	/// One dimension
	{
		meter m1(2);
		meter m2(3);

		meter m3 = m1 + m2;
		meter m4 = m2 + m1;

		assert(m3.value() == 5);
		assert(m4.value() == 5);
	}
	/// One dimension - prefixes factor
	{
		decimeter dm1(2);
		decimeter dm2(3);

		decimeter dm3 = dm1 + dm2;
		decimeter dm4 = dm2 + dm1;

		assert(dm3.value() == 5);
		assert(dm4.value() == 5);
	}
	/// Two dimension
	{
		meter m(2);
		decimeter dm(30);

		meter m2 = m + meter(dm);
		meter m3 = meter(dm) + m;
		assert(m2.value() == 5);
		assert(m3.value() == 5);

		decimeter dm2 = decimeter(m) + dm;
		decimeter dm3 = dm + decimeter(m);
		assert(dm2.value() == 50);
		assert(dm3.value() == 50);
	}
	/// Three dimension
	{
		meter m(2);
		decimeter dm(34);
		centimeter cm(567);

		centimeter cm2 = dm + decimeter(m);
		centimeter cm3 = decimeter(m) + dm;

		assert(cm2.value() == 540);
		assert(cm3.value() == 540);

		decimeter dm2 = centimeter(m) + cm;
		decimeter dm3 = cm + centimeter(m);

		assert(dm2.value() == 76);
		assert(dm3.value() == 76);

		meter m2 = cm + centimeter(dm);
		meter m3 = centimeter(dm) + cm;

		assert(m2.value() == 9);
		assert(m3.value() == 9);
	}

	cout << __func__ << endl;
}
/// ------------------------------------------------------------------------------------------------
}
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
