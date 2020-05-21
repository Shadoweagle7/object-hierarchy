#ifndef SE7_STDIO
#define SE7_STDIO

#include <type_traits>
#include <iostream>
#include <fstream>

namespace SE7 {
	template<class T>
	auto print(T t) -> decltype(std::declval<T>().to_string(), void()) {
		std::cout << t;
	}

	void println(bool flush = false) {
		if (flush) {
			std::cout << std::endl;
		} else {
			std::cout << "\n";
		}
	}

	template<class T>
	auto println(T t, bool flush = false) -> decltype(std::declval<T>().to_string(), void()) {
		std::cout << t;

		if (flush) {
			std::cout << std::endl;
		} else {
			std::cout << "\n";
		}
	}

	template<class T>
	auto wprint(T t) -> decltype(std::declval<T>().to_wstring(), void()) {
		std::wcout << t;
	}

	void wprintln(bool flush = false) {
		if (flush) {
			std::wcout << std::endl;
		} else {
			std::wcout << "\n";
		}
	}

	template<class T>
	auto wprintln(T t, bool flush = false) -> decltype(std::declval<T>().to_wstring(), void()) {
		std::wcout << t;

		if (flush) {
			std::wcout << std::endl;
		} else {
			std::wcout << "\n";
		}
	}
}

#endif // !SE7_STDIO
