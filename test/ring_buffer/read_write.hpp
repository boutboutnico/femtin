///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef FEMTIN_TEST_RING_BUFFER_READ_WRITE_HPP_
#define FEMTIN_TEST_RING_BUFFER_READ_WRITE_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "../femtin/ring_buffer.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
namespace ring_buffer
{

/// ------------------------------------------------------------------------------------------------

void read_write()
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

/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
