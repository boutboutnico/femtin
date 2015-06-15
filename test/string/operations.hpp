///
/// \file	operator_plus_a_b.hpp
///	\brief	
///	\date	4 juin 2015
/// \author	nboutin
///
#ifndef FEMTIN_TEST_STRING_OPERATIONS_HPP_
#define FEMTIN_TEST_STRING_OPERATIONS_HPP_

/// === Includes	================================================================================

#include <assert.h>
#include "string.hpp"

/// === Namespaces	================================================================================

using namespace std;

namespace femtin
{
namespace test
{
namespace string
{

/// ------------------------------------------------------------------------------------------------

void element_access()
{
	static const size_t size = 10;
	String<size> s("ABCDE");

	assert(s[0] == 'A');
	assert(s[4] == 'E');

	cout << __func__ << endl;
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

	cout << __func__ << endl;

}

/// ------------------------------------------------------------------------------------------------
}
}    /// test
}    /// femtin
#endif
/// === END OF FILE	================================================================================
