///
/// \file	operator_div_a_b.hpp
///	\brief	
///	\date	04/06/2015
/// \author	nboutin
///
#ifndef TEST_OPERATOR_DIV_EGAL_HPP_
#define TEST_OPERATOR_DIV_EGAL_HPP_

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

void operator_div_egal()
{
	{
		meter m1(6);

		m1 /= 3;
		assert(m1.value() == 2);
	}
	{
		meter2 m2(12);

		m2 /= 4;
		assert(m2.value() == 3);
	}

	cout << "operator_div_egal:\t Pass" << endl;
}
/// ------------------------------------------------------------------------------------------------
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
