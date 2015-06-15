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
/// \brief
/// \date	15/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef FEMTIN_TEST_STRING_ALL_TESTS_HPP_
#define FEMTIN_TEST_STRING_ALL_TESTS_HPP_

/// === Includes	================================================================================

#include <iostream>

#include "constructor.hpp"
#include "copy_constructor.hpp"
#include "operations.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
namespace string
{

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

void string_all()
{
	cout << "\n=== String" << endl;

	/// --- Constructor
	default_constructor();
	array_constructor();
	copy_constructor();
	element_access();
	operations();

//	copy_assignment();
//	test_constructor();

}

}
}
}
#endif
/// === END OF FILE	================================================================================

#if 0
class Test
{
public:

	template<size_t L>
	void set(const String<L>& _s)
	{
		s_ = _s;
	}

	String<15>& get()
	{
		return s_;
	}

private:
	String<15> s_;
};

void copy_assignment()
{
	String<9> s1("tobis");
	String<10> s2("cape");
	String<11> s3("guf");

	assert(s2.size() == 4);

	s2 = s1;
	assert(s2.size() == 5);

	s2 = s3;
	assert(s2.size() == 3);

	String<10> s4;
	assert(s4.size() == 0);
	s4 = "lipu";
	cout << s4.size() << endl;
	assert(s4.size() == 4);
}

void test_constructor()
{
	static const uint8_t ss1 = 10;
	String<ss1> s1;

	assert(s1.capacity() == ss1);
	assert(s1.max_size() == ss1);
	assert(s1.size() == 0);
	assert(s1.empty() == true);
	assert(s1.full() == false);

	s1 += 'A';
	assert(s1.capacity() == ss1 - 1);
	assert(s1.max_size() == ss1);
	assert(s1.size() == 1);
	assert(s1.empty() == false);
	assert(s1.full() == false);

	s1 += 'B';
	s1 += 'C';
	s1 += 'D';
	s1 += 'E';
	s1 += 'F';
	s1 += '0';

	static const uint8_t ss2 = 15;
	String<ss2> s2;

	s2 = s1;

	Test t;
	t.set(s2);

	cout << t.get().c_str() << endl;

	const String<16> s_const("Const_String");

//	String<10> s0("0123456789");
//	cout << s0.getSize() << endl;
//	assert(s0.getSize() == 10);

//	femtin::String<4> s1(s0, 2, 4);
//	cout << s1.c_str() << endl;
//	assert(strcmp(s1.c_str(), "2345") == 0);
//
//	femtin::String<10> s2("012345");
//	femtin::String<2> s3 = s2.substr(4);
//	cout << s3.c_str() << endl;
//	assert(strcmp(s3.c_str(), "45") == 0);

	cout << "Constructor: Pass" << endl;
}
#endif

