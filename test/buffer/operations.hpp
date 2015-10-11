//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef FEMTIN_TEST_BUFFER_OPERATIONS_HPP_
#define FEMTIN_TEST_BUFFER_OPERATIONS_HPP_

#include <iostream>
using namespace std;

#include "../femtin/buffer.hpp"

namespace femtin
{
namespace test
{
namespace buffer
{

void operations()
{
	const size_t b_size = 7;
	Buffer<b_size> b;

	assert(b.capacity() == b_size);
	assert(b.max_size() == b_size);
	assert(b.size() == 0);
	assert(b.empty() == true);
	assert(b.full() == false);

	b.add(uint8_t(0x12));
	assert(b.size() == 1);
	assert(b.capacity() == b_size - 1);
	assert(b.empty() == false);
	assert(b.full() == false);

	b.add<uint16_t>(0x3456);
	assert(b.size() == 3);
	assert(b.capacity() == b_size - 3);
	assert(b.empty() == false);
	assert(b.full() == false);

	b.add(0x789ABCDE);
	assert(b.size() == 7);
	assert(b.capacity() == 0);
	assert(b.empty() == false);
	assert(b.full() == true);

	cout << __func__ << endl;
}

}
}
}
#endif
