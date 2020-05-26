#ifndef SE7_STDIO
#define SE7_STDIO

#include <type_traits>
#include <iostream>
#include <fstream>

// TODO: Add support for primitives (calls to println(0) or println("") will NOT work as of now)

namespace SE7 {
	template<class T>
	auto print(const T &t) -> decltype(std::declval<T>().to_string(), void()) {
		std::cout << t;
	}

	template<class T> 
	auto print(const T &t) -> decltype(std::enable_if<std::is_fundamental<T>::value>::type, void()) {
		std::cout << t;
	}

	void println(SE7::boolean flush = false) {
		if (flush) {
			std::cout << std::endl;
		} else {
			std::cout << "\n";
		}
	}

	template<class T>
	auto println(const T &t, bool flush = false) -> decltype(std::declval<T>().to_string(), void()) {
		std::cout << t;

		if (flush) {
			std::cout << std::endl;
		} else {
			std::cout << "\n";
		}
	}

	template<class T>
	auto wprint(const T &t) -> decltype(std::enable_if<std::is_fundamental<T>::value>::type, void()) {
		std::wcout << t;
	}

	template<class T>
	auto wprint(const T &t) -> decltype(std::declval<T>().to_wstring(), void()) {
		std::wcout << t;
	}

	void wprintln(SE7::boolean flush = false) {
		if (flush) {
			std::wcout << std::endl;
		} else {
			std::wcout << L"\n";
		}
	}

	template<class T>
	auto wprintln(const T &t, bool flush = false) -> decltype(std::declval<T>().to_wstring(), void()) {
		std::wcout << t;

		if (flush) {
			std::wcout << std::endl;
		} else {
			std::wcout << "\n";
		}
	}
}

#endif // !SE7_STDIO
