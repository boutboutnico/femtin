///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef TEST_COPY_CONSTRUCTOR_HPP_
#define TEST_COPY_CONSTRUCTOR_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "unit/base_type/length_unit_type.hpp"
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
/// ------------------------------------------------------------------------------------------------

void copy_constructor()
{
	{
		meter m(1);
		decimeter dm(m);
		centimeter cm(m);
		millimeter mm(m);

		assert(dm.value() == m.value() * 10);
		assert(cm.value() == m.value() * 100);
		assert(mm.value() == m.value() * 1000);
	}

	{
		millimeter mm(1000);
		centimeter cm(mm);
		decimeter dm(mm);
		meter m(mm);

		assert(cm.value() == mm.value() / 10);
		assert(dm.value() == mm.value() / 100);
		assert(m.value() == mm.value() / 1000);
	}

	{
		/// 1 cm2 = 100 mm2
		centimeter2 cm2 = decimeter2(1);
		millimeter2 mm2 = centimeter2(1);
		millimeter2 mm2_2 = meter2(1);

		assert(cm2.value() == 100);
		assert(mm2.value() == 100);
		assert(mm2_2.value() == 1000 * 1000);
	}

	{
		meter2 m2 = millimeter2(1000 * 1000);

		assert(m2.value() == 1);
	}

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------
}
}/// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
