//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "ring_buffer.hpp"
using namespace femtin;

void basic_test();
void ring_test();
void array_test();
void read_write_count_test();
void constructor_test();

int main()
{
	basic_test();
	cout << "Basic Test: Pass" << endl;

	ring_test();
	cout << "Ring Test: Pass" << endl;

	array_test();
	cout << "Array Test: Pass" << endl;

	read_write_count_test();
	cout << "Read Write Test: Pass" << endl;

	constructor_test();
	cout << "Constructor Test: Pass" << endl;

	cout << "Ring_Buffer: Pass" << endl;

	return 0;
}

void constructor_test()
{
	/// Default constructor
	Ring_Buffer<32> rbuf;
	rbuf.fill(0xAB);

	/// Copy constructor
	Ring_Buffer<24> rbuf2(rbuf);
	assert(rbuf2.full() == true);

	Ring_Buffer<33> rbuf3(rbuf);
	assert(rbuf3.full() == false);

	rbuf3.add<uint8_t>(0xFF);
	assert(rbuf3.full() == true);
}

void read_write_count_test()
{
	const size_t rbuf_size = 512;
	Ring_Buffer<rbuf_size> rbuf;

	size_t w = 0, r = 0;

	for (uint32_t i = 0; i <= (0xFFFF / 8) + 10; i++)
	{
		w += rbuf.add(0x12345678);
		assert((w - r) == rbuf.size());

		if (w % 512 == 0)
		{
			uint32_t read32 = 0;
			for (uint16_t i = 0; i < 512 / 4; i++)
			{
				read32 = rbuf.read<uint32_t>();
				read32++;
				r += 4;
				assert((w - r) == rbuf.size());
			}
		}
	}
}

void array_test()
{
	const size_t rbuf_size = 8;
	Ring_Buffer<rbuf_size> rbuf;

	uint8_t a1[] =
	{ 0x12, 0x34 };

	uint16_t a2[] =
	{ 0x5678, 0x9ABC };

	rbuf.add(a1);
	rbuf.add(a2);
	assert(rbuf.capacity() == 2);

	uint32_t read32 = rbuf.read<uint32_t>();
	assert(read32 == 0x12345678);
	assert(rbuf.capacity() == 6);

	uint32_t a3[] =
	{ 0xDEF2468 };

	rbuf.add(a3);
	assert(rbuf.capacity() == 2);
}

void ring_test()
{
	const size_t rbuf_size = 6;
	Ring_Buffer<rbuf_size> rbuf;

	rbuf.add(0x12345678);
	rbuf.add<uint8_t>(0x9A);

	uint32_t read32 = rbuf.read<uint32_t>();
	assert(read32 == 0x12345678);

	rbuf.add(0xBCDEF123);
	assert(rbuf.capacity() == 1);
	assert(rbuf.max_size() == rbuf_size);
	assert(rbuf.size() == 5);
	assert(rbuf.empty() == false);
	assert(rbuf.full() == false);

	read32 = rbuf.read<uint32_t>();
	assert(read32 == 0x9ABCDEF1);
}

void basic_test()
{
	const size_t rbuf_size = 16;
	Ring_Buffer<rbuf_size> rbuf;

	/// Capacity
	assert(rbuf.capacity() == rbuf_size);
	assert(rbuf.max_size() == rbuf_size);
	assert(rbuf.size() == 0);
	assert(rbuf.empty() == true);
	assert(rbuf.full() == false);

	/// Write
	const size_t v1 = 4;
	rbuf.add(0x12341234);
	assert(rbuf.capacity() == rbuf_size - v1);
	assert(rbuf.max_size() == rbuf_size);
	assert(rbuf.size() == v1);
	assert(rbuf.empty() == false);
	assert(rbuf.full() == false);

	rbuf.add(0x22222222);
	rbuf.add<uint16_t>(0x3333);
	rbuf.add<uint16_t>(0x4444);
	rbuf.add<uint8_t>(0x55);
	rbuf.add<uint8_t>(0x66);
	rbuf.add<uint8_t>(0x77);
	rbuf.add<uint8_t>(0x88);
	assert(rbuf.capacity() == 0);
	assert(rbuf.max_size() == rbuf_size);
	assert(rbuf.size() == rbuf_size);
	assert(rbuf.empty() == false);
	assert(rbuf.full() == true);

	/// Read
	uint16_t read16 = rbuf.read<uint16_t>();
	assert(read16 == 0x1234);
	assert(rbuf.capacity() == 2);
	assert(rbuf.max_size() == rbuf_size);
	assert(rbuf.size() == rbuf_size - 2);
	assert(rbuf.empty() == false);
	assert(rbuf.full() == false);

	uint8_t read8 = rbuf.read<uint8_t>();
	assert(read8 == 0x12);
	assert(rbuf.capacity() == 3);

	read16 = rbuf.read<uint16_t>();
	assert(read16 == 0x3422);
	assert(rbuf.capacity() == 5);
}
