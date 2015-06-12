///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef TEST_MPL_HPP_
#define TEST_MPL_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "femtin/mpl/mpl_utility.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
/// ------------------------------------------------------------------------------------------------

void power()
{
	{
		static const uint32_t pow = Power<uint32_t, 10U, 2U>::VALUE;
		static const uint32_t val = 100U;

		assert(pow == val);
	}

	cout << "mpl power:\t\t Pass" << endl;
}

/// ------------------------------------------------------------------------------------------------

void static_if()
{
	{
		static const uint32_t value = StaticIf<uint32_t, 1 != 0, 100U, 200U>::VALUE;
		assert(value == 100);

		static const uint32_t value2 = StaticIf<uint32_t, 1 == 0, 100U, 200U>::VALUE;
		assert(value2 == 200);
	}
	cout << "mpl static_if:\t\t Pass" << endl;
}

/// ------------------------------------------------------------------------------------------------

void scale_converter()
{
	{
		uint32_t val = ScaleConverter<uint32_t, 1, 2>::convert(4);
		assert(val == 40);
	}
	{
		uint32_t val = ScaleConverter<uint32_t, 0, 2>::convert(4);
		assert(val == 400);
	}
	{
		uint32_t val = ScaleConverter<uint32_t, 2, 0>::convert(400);
		assert(val == 4);
	}
	cout << "mpl scale_converter:\t Pass" << endl;
}

/// ------------------------------------------------------------------------------------------------
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
