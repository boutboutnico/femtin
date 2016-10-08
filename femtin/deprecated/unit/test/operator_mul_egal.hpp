///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef TEST_OPERATOR_MUL_EGAL_HPP_
#define TEST_OPERATOR_MUL_EGAL_HPP_

/// === Includes	================================================================================

#include <assert.h>

/// === Namespaces	================================================================================

using namespace std;
using namespace femtin::unit;

namespace femtin
{
namespace test
{
/// a@b 	(a).operator@ (b) 	operator@ (a, b)

void operator_mul_egal()
{
	{
		meter m1(2);

		m1 *= 3;
		assert(m1.value() == 6);
	}
	{
		meter2 m2(3);

		m2 *= 4;
		assert(m2.value() == 12);
	}

	cout << "operator_mul_egal:\t Pass" << endl;
}
/// ------------------------------------------------------------------------------------------------
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
