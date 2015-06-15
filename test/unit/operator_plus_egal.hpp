///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef TEST_OPERATOR_PLUS_EGAL_HPP_
#define TEST_OPERATOR_PLUS_EGAL_HPP_

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

void operator_plus_egal()
{
	/// One dimension
	{
		meter m1(2);
		meter m2(3);

		m1 += m2;
		assert(m1.value() == 5);

		m2 += m1;
		assert(m2.value() == 8);
	}
	/// Two dimension
	{
		meter m(2);
		decimeter dm(30);

		m += dm;
		assert(m.value() == 5);

		dm += m;
		assert(dm.value() == 80);
	}

	cout << __func__ << endl;
}
/// ------------------------------------------------------------------------------------------------
}
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
