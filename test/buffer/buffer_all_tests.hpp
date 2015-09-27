//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef FEMTIN_TEST_BUFFER_ALL_TESTS_HPP_
#define FEMTIN_TEST_BUFFER_ALL_TESTS_HPP_

#include "default_constructor.hpp"
#include "operations.hpp"
#include "read.hpp"

namespace femtin
{
namespace test
{
namespace buffer
{

void buffer_all()
{
	cout <<"\n=== Buffer" << endl;

	default_constructor();
	copy_constructor();

	operations();

	read();
}

}
}
}

#endif
