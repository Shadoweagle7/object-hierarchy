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
			std::cout << std::endl
		} else {
			std::cout << "\n";
		}
	}
}

#endif // !SE7_STDIO
