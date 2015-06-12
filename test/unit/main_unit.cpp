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
/// === Includes	================================================================================
#include <iostream>
#include <assert.h>

#include "unit/unit_type.hpp"
#include "mpl/mpl_utility.hpp"

#include "operator_plus_egal.hpp"
#include "operator_plus_a_b.hpp"

/// === Namespaces	================================================================================

using namespace std;
using namespace femtin::test;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

int main()
{
	cout << "=====	Femtin Unit	=====" << endl;

	operator_plus_egal();
	operator_plus_a_b();

	/// ========================

	{
		using namespace femtin;

		static const uint32_t pow = Power<uint32_t, 10U, 2U>::VALUE;
		static const uint32_t val = 100U;

		assert(pow == val);
	}

	{

		using namespace femtin;
		static const uint32_t value = StaticIf<uint32_t, 1 != 0, 100U, 200U>::VALUE;
		assert(value == 100);

		static const uint32_t value2 = StaticIf<uint32_t, 1 == 0, 100U, 200U>::VALUE;
		assert(value2 == 200);
	}

	{
		using namespace femtin;

		uint32_t val = ScaleConverter<uint32_t, 1, 2>::convert(4);
		assert(val == 40);
	}

	{
		using namespace femtin::unit;

		meter m(1);
		decimeter dm(m);
		centimeter cm(m);
		millimeter mm(m);

		assert(dm.value() == m.value() * 10);
		assert(cm.value() == m.value() * 100);
		assert(mm.value() == m.value() * 1000);
	}

	{
		using namespace femtin::unit;

		millimeter mm(1000);
		centimeter cm(mm);
		decimeter dm(mm);
		meter m(mm);

		assert(cm.value() == mm.value() / 10);
		assert(dm.value() == mm.value() / 100);
		assert(m.value() == mm.value() / 1000);
	}

	{
		using namespace femtin::unit;

		meter m1(1);
		meter m2(2);
		meter m3(3);
		decimeter dm(40);

		assert(m1.value() == 1);

		m1 *= 3;
		assert(m1.value() == 3);
	}

	{
		using namespace femtin::unit;

		{
			meter m1(2);
			meter m2(3);
			meter2 a = m1 * m2;
			assert(a.value() == 6);
			meter2 a2 = m2 * m1;
			assert(a2.value() == 6);
		}

		{
			meter m1(2);
			decimeter dm1(30);
			meter2 a = m1 * meter(dm1);
			assert(a.value() == 6);
		}
		{
			meter m(2);
			decimeter dm(30);
			meter2 a = m * dm;
			assert(a.value() == 6);
//			cout << a.value() << endl;

			meter2 a2 = dm * m;
//			assert(a2.value() == 6);
			cout << a2.value() << endl;
		}
		{
			millimeter mm(2000);
			decimeter dm(40);
			meter2 a = mm * dm;
			cout << "8 => " << a.value() << endl;
//			assert(a.value() == 8);
		}
		{
//			millimeter mm(2000);
//			meter m(4);
//			meter2 a = mm * m;
//			cout <<"8 => " << a.value() << endl;

		}
	}

	{
		using namespace femtin::unit;

		meter m(100);
		second s(10);

		speed sp = m / s;
		assert(sp.value() == 10);
//		cout << sp.value() << endl;
	}

	{
		using namespace femtin::unit;

		millivoltage mv(5000);
		voltage v(5);
		ohm r(4700);
		ampere i(12);

//		milliampere mi = mv / r;
//		cout << mi.value() << endl;

		watt p = v * i;
		assert(p.value() == 60);
//		cout << p.value() << endl;
	}

	return 0;
}

/// === END OF FILE	================================================================================

