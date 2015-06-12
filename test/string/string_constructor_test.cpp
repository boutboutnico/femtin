/// ================================================================================================
///
/// \file	template.cpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///
/// ================================================================================================

#include "string_constructor_test.hpp"

/// === Includes	================================================================================

#include "string.hpp"

/// === Namespaces	================================================================================
/// === Constants	================================================================================
/// === Public Definitions	========================================================================

namespace femtin
{

namespace string_test
{

void copy_constructor_empty();
void copy_constructor_full();
void copy_constructor_range();

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
}

/// ------------------------------------------------------------------------------------------------
void func(const String<10> _s);
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

}

void func(const String<10> _s)
{

}

/// ------------------------------------------------------------------------------------------------

void copy_constructor()
{
	copy_constructor_empty();
	copy_constructor_full();
	copy_constructor_range();
}

/// ------------------------------------------------------------------------------------------------

void element_access()
{
	static const size_t size = 10;
	String<size> s("ABCDE");

	assert(s[0] == 'A');
	assert(s[4] == 'E');
}

/// ------------------------------------------------------------------------------------------------

void operations()
{
	static const size_t size = 10;
	String<size> s;

	/// --- operator +=

	s += 'c';
	assert(s.size() == 1);

	/// --- clear

	s.clear();
	assert(s.size() == 0);

	/// --- Count

	{
		static const size_t size = 5;
		String<size> s("ABCDA");

		assert(s.count(' ') == 0);
		assert(s.count('A') == 2);
		assert(s.count(' ', 1) == 0);
		assert(s.count('A', 1) == 1);
		assert(s.count(' ', 0, 4) == 0);
		assert(s.count('A', 0, 4) == 2);
		assert(s.count(' ', 1, 4) == 0);
		assert(s.count('A', 1, 4) == 1);
		assert(s.count(' ', 0, 5) == 0);
		assert(s.count('A', 0, 5) == 2);
		assert(s.count(' ', 0, 10) == 0);
		assert(s.count('A', 0, 10) == 2);
		assert(s.count(' ', 3, 10) == 0);
		assert(s.count('A', 3, 10) == 1);
	}
	{
		static const size_t size = 5;
		String<size> s("AAAA");

		assert(s.count('A') == 4);
	}

	/// --- Find
	{
		static const size_t size = 5;
		String<size> s("ABCDA");

		assert(s.find(' ') == s.npos);
		assert(s.find('A') == 0);
		assert(s.find(' ', 1) == s.npos);
		assert(s.find('A', 1) == 4);
		assert(s.find(' ', 0, 4) == s.npos);
		assert(s.find('A', 0, 4) == 0);
		assert(s.find(' ', 1, 4) == s.npos);
		assert(s.find('A', 1, 4) == 4);
		assert(s.find(' ', 0, 5) == s.npos);
		assert(s.find('A', 0, 5) == 0);
		assert(s.find(' ', 0, 10) == s.npos);
		assert(s.find('A', 0, 10) == 0);
	}

	/// substr

	String<8> dest;
	String<20> src("ADSC");
	assert(src.size() == 4);
	src += '\t';
	assert(src.size() == 5);
	src += "012345";
	assert(src.size() == 11);

	size_t pos = src.find('\t');
	dest = src.substr(0, pos);
	assert(dest.size() == 4);

}

/// === Private Definitions	========================================================================

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
}

/// ------------------------------------------------------------------------------------------------

}
}

/// === END OF FILE	================================================================================
