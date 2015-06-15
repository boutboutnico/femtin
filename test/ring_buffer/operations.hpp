///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef FEMTIN_TEST_RING_BUFFER_OPERATIONS_HPP_
#define FEMTIN_TEST_RING_BUFFER_OPERATIONS_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "ring_buffer.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
namespace ring_buffer
{

/// ------------------------------------------------------------------------------------------------

void operations()
{
	{
		const size_t rbuf_size = 8;
		Ring_Buffer<rbuf_size> rbuf;

		uint8_t a1[] = { 0x12, 0x34 };

		uint16_t a2[] = { 0x5678, 0x9ABC };

		rbuf.add(a1);
		rbuf.add(a2);
		assert(rbuf.capacity() == 2);

		uint32_t read32 = rbuf.read<uint32_t>();
		assert(read32 == 0x12345678);
		assert(rbuf.capacity() == 6);

		uint32_t a3[] = { 0xDEF2468 };

		rbuf.add(a3);
		assert(rbuf.capacity() == 2);
	}

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
}

/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
