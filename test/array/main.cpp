//============================================================================
// Name        : femtin_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "array.hpp"
using namespace femtin;

void test_constructor();

int main()
{
	test_constructor();

	cout << "String: Pass" << endl;
}

void test_constructor()
{
	Array<uint8_t, 10> a10;
}
