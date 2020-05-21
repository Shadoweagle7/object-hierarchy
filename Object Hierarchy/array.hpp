#ifndef SE7_ARRAY
#define SE7_ARRAY

#include "object.hpp"

#include <initializer_list>
#include <algorithm>
#include <cstring>
#include <type_traits>

namespace SE7 {
	template<class T, size_t N>
	class array : public object {
	private:
		T arr[N];
	public:
		array() {
			std::memset(this->arr, 0, sizeof(this->arr));
		}

		array(std::initializer_list<T> list) {
			for (size_t i = 0; i < N; i++) {
				this->arr[i] = std::move(*(list.begin() + i));
			}
		}

		T &operator[](size_t n) const {
			return this->arr[n];
		}

		GC_NEW_CONSTRUCTIBLE(array)
	};

	template<class T>
	class array<T, 0> {
	private:
		T *arr;
	public:
		array() {
			this->arr = new T[0];
		}

		GC_NEW_CONSTRUCTIBLE(array)

		~array() {
			delete[] this->arr;
		}
	};
}

#endif // !SE7_ARRAY
