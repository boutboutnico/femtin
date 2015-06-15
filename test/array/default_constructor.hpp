//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef FEMTIN_TEST_ARRAY_DEFAULT_CONSTRUCTOR_HPP_
#define FEMTIN_TEST_ARRAY_DEFAULT_CONSTRUCTOR_HPP_

#include <iostream>
using namespace std;

#include "array.hpp"

namespace femtin
{
namespace test
{
namespace array
{

void default_constructor()
{
	Array<uint8_t, 10> a;

	assert(a.max_size() == 10);

	cout << "Array\tdefault_constructor\tPASS" << endl;
}

}
}
}

#endif
