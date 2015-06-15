//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef FEMTIN_TEST_BUFFER_DEFAULT_CONSTRUCTOR_HPP_
#define FEMTIN_TEST_BUFFER_DEFAULT_CONSTRUCTOR_HPP_

#include <iostream>
using namespace std;

#include "buffer.hpp"

namespace femtin
{
namespace test
{
namespace buffer
{

void default_constructor()
{
	/// Default constructor
	Buffer<32> b;
	b.fill(0xAB);

	cout << "default_constructor\tPASS" << endl;
}

void copy_constructor()
{
	Buffer<32> b;
	b.fill(0xAB);

	Buffer<24> b2(b);
	assert(b2.full() == true);

	Buffer<33> b3(b);
	assert(b3.full() == false);

	b3.add<uint8_t>(0xFF);
	assert(b3.full() == true);

	cout << "copy_constructor\tPASS" << endl;
}

}
}
}
#endif
