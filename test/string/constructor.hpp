///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef FEMTIN_TEST_STRING_CONSTRUCTOR_HPP_
#define FEMTIN_TEST_STRING_CONSTRUCTOR_HPP_

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

/// ------------------------------------------------------------------------------------------------

void default_constructor()
{
	/// Size = 0
	{
		static const size_t size = 0;
		String<size> s;

		assert(s.empty() == false);
		assert(s.full() == true);
		assert(s.size() == 0);
		assert(s.capacity() == size);
	}

	/// Size > 0
	{
		static const size_t size = 10;
		String<size> s;

		assert(s.empty() == true);
		assert(s.full() == false);
		assert(s.size() == 0);
		assert(s.capacity() == size);
	}

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------

void func(const String<10> _s)
{

}

void array_constructor()
{
	static const char str[] = "ABCDE";
	static const size_t str_size = (sizeof(str) / sizeof(char)) - 1;

	/// Same size
	{
		static const size_t size = 5;

		{
			String<size> s(str);
			assert(s.size() == str_size);
		}
	}

	/// Smaller size
	{
		static const size_t size = 4;
		String<size> s("ABCDE");
		assert(s.size() == 4);
	}

	/// Bigger size
	{
		static const size_t size = 6;
		String<size> s("ABCDE");
		assert(s.size() == 5);
	}

	/// String(const value_type (&_str)[L])
	/// explicit String(const value_type (&_str)[L])
	func("ABCDE");

	cout << __func__ << endl;
}

/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
