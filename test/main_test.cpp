//============================================================================
// Name        : femtin_test.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

/// === Includes	================================================================================

#include "array/array_all_tests.hpp"
#include "buffer/buffer_all_tests.hpp"
#include "mpl/mpl_all_tests.hpp"

///	===	Namespaces	================================================================================

using namespace femtin::test;

int main()
{
	cout << "=== Start Tests	===" << endl;

	array::array_all();

	buffer::buffer_all();

	mpl::mpl_all();

	cout << "=== End Tests	===" << endl;
}

/// === END OF FILE	================================================================================
