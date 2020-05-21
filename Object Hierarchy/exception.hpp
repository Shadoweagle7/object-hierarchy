#ifndef SE7_EXCEPTION
#define SE7_EXCEPTION

#include <stdexcept>

#include "object.hpp"

namespace SE7 {
	class divide_by_zero : public std::logic_error, public object {
	public:
		divide_by_zero() : std::logic_error("Division by zero"), object() {}

		GC_NEW_CONSTRUCTIBLE(divide_by_zero)
	};

	class empty_function : public std::runtime_error, public object {
	public:
		empty_function() : std::runtime_error("Function object does not represent a function"), object() {}

		GC_NEW_CONSTRUCTIBLE(empty_function)
	};
}

#endif // !SE7_EXCEPTION
