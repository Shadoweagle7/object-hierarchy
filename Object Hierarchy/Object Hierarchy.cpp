// Object Hierarchy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "core.hpp"

int main() {
	SE7::primitive<int> a;
	//SE7::primitive<std::ios_base> b;

	SE7::integer i = 27;
	SE7::character c = 'c';
	SE7::long_long_integer lli = 0ll;

	SE7::function<int(int, const char *[])> f = [](int a, const char *b[]) {
		return a;
	};

	SE7::function f2 = f;

	SE7::array<int, 0> arr;
	SE7::array<char, 1> arr2;

	SE7::object obj;

	SE7::divide_by_zero dv0;
	SE7::empty_function ef;

	const char *const_char_str = "const char *";
	const wchar_t *const_wide_char_str = L"const wchar_t *";

	SE7::string str = "SE7::string";
	SE7::string str2 = const_char_str;

	SE7::wide_string wstr = L"SE7::string";
	SE7::wide_string wstr2 = const_wide_char_str;

	std::cout << f(27, nullptr) << " " << std::boolalpha << f.empty() << std::endl;	

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
