///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef FEMTIN_TEST_RING_BUFFER_CONSTRUCTOR_HPP_
#define FEMTIN_TEST_RING_BUFFER_CONSTRUCTOR_HPP_

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

void default_constructor()
{
	/// Default constructor
	Ring_Buffer<32> rbuf;
	rbuf.fill(0xAB);

	cout << __func__ << endl;
}

void copy_constructor()
{
	Ring_Buffer<32> rbuf;
	rbuf.fill(0xAB);

	/// Copy constructor
	Ring_Buffer<24> rbuf2(rbuf);
	assert(rbuf2.full() == true);

	Ring_Buffer<33> rbuf3(rbuf);
	assert(rbuf3.full() == false);

	rbuf3.add<uint8_t>(0xFF);
	assert(rbuf3.full() == true);

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
