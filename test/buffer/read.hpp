//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef FEMTIN_TEST_BUFFER_READE_HPP_
#define FEMTIN_TEST_BUFFER_READ_HPP_

#include <iostream>
using namespace std;

#include "buffer.hpp"

namespace femtin
{
namespace test
{
namespace buffer
{

void read()
{
	const size_t b_size = 7;
	Buffer<b_size> b;
	b.add(uint8_t(0x12));
	b.add<uint16_t>(0x3456);
	b.add(0x789ABCDE);

	uint8_t read8;
	uint16_t read16;
	uint32_t read32;

	read32 = b.read<uint32_t>();
	assert(read32 == 0x12345678);

	assert(b.end() == 0xDE);

	read16 = b.read<uint16_t>();
	assert(read16 == 0x9ABC);

	read8 = b.read<uint8_t>();
	assert(read8 == 0xDE);

	cout << "read\t\t\tPASS" << endl;
}

}
}
}
#endif
