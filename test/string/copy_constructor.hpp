///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef FEMTIN_TEST_STRING_COPY_CONSTRUCTOR_HPP_
#define FEMTIN_TEST_STRING_COPY_CONSTRUCTOR_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "../femtin/string.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
namespace string
{

void copy_constructor_empty();
void copy_constructor_full();
void copy_constructor_range();

/// ------------------------------------------------------------------------------------------------

void copy_constructor()
{
	copy_constructor_empty();
	copy_constructor_full();
	copy_constructor_range();

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------

void copy_constructor_empty()
{
	static const size_t size = 10;
	String<size> s;

	/// Same size
	{
		static const size_t size_2 = size;
		String<size_2> s2(s);
		assert(s2.empty());
		assert(!s2.full());
		assert(s2.size() == 0);
		assert(s2.capacity() == size);
	}

	/// Smaller size
	{
		static const size_t size_2 = 5;
		String<size_2> s2(s);
		assert(s2.empty());
		assert(!s2.full());
		assert(s2.size() == 0);
		assert(s2.capacity() == size_2);
	}

	/// Bigger size
	{
		static const size_t size_2 = 15;
		String<size_2> s2(s);
		assert(s2.empty());
		assert(!s2.full());
		assert(s2.size() == 0);
		assert(s2.capacity() == size_2);
	}

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------

void copy_constructor_full()
{
	static const size_t size = 10;
	String<size> s("ABCDEFGHIJ");

	/// Same size
	{
		static const size_t size_2 = size;
		String<size_2> s2(s);
		assert(s2.empty() == false);
		assert(s2.full() == true);
		assert(s2.size() == size);
		assert(s2.capacity() == 0);
	}

	/// Smaller size
	{
		static const size_t size_2 = 5;
		String<size_2> s2(s);
		assert(s2.empty() == false);
		assert(s2.full() == true);
		assert(s2.size() == size_2);
		assert(s2.capacity() == 0);
	}

	/// Bigger size
	{
		static const size_t size_2 = 15;
		String<size_2> s2(s);
		assert(s2.empty() == false);
		assert(s2.full() == false);
		assert(s2.size() == size);
		assert(s2.capacity() == size_2 - size);
	}

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------

void copy_constructor_range()
{
	static const size_t size = 10;
	String<size> s("ABCDEFGHIJ");

	/// Same size
	{
		static const size_t size_2 = size;
		{
			String<size_2> s2(s, 0);
			assert(s2.size() == size);
		}
		{
			String<size_2> s2(s, 3);
			assert(s2.size() == size_2 - 3);
		}
		{
			String<size_2> s2(s, 3, 7);
			assert(s2.size() == size_2 - 3);
		}
		{
			String<size_2> s2(s, 3, 5);
			assert(s2.size() == 5);
		}
		{
			String<size_2> s2(s, 3, 10);
			assert(s2.size() == size_2 - 3);
		}
	}

	/// Smaller size
	{
		static const size_t size_2 = 5;
		{
			String<size_2> s2(s, 0);
			assert(s2.size() == size_2);
		}
		{
			String<size_2> s2(s, 3);
			assert(s2.size() == size_2);
		}
	}

	/// Bigger size
	{
		static const size_t size_2 = 15;

		{
			String<size_2> s2(s, 0);
			assert(s2.size() == size);
		}
		{
			String<size_2> s2(s, 3);
			assert(s2.size() == size - 3);
		}
	}

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
