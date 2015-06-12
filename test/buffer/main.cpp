//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "buffer.hpp"
using namespace femtin;

void basic_test();
void read_test();
void constructor_test();

int main()
{
	basic_test();
	read_test();
	constructor_test();

	cout << "Buffer: Pass" << endl;

	return 0;
}

void constructor_test()
{
	/// Default constructor
	Buffer<32> b;
	b.fill(0xAB);

	/// Copy constructor
	Buffer<24> b2(b);
	assert(b2.full() == true);

	Buffer<33> b3(b);
	assert(b3.full() == false);

	b3.add<uint8_t>(0xFF);
	assert(b3.full() == true);

	cout << "Constructor Test: Pass" << endl;
}

void read_test()
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

	cout << "Read Test: Pass" << endl;
}

void basic_test()
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

	cout << "Basic Test: Pass" << endl;
}
