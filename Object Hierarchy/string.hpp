#ifndef SE7_STRING
#define SE7_STRING

#include "object.hpp"
#include "primitive.hpp"

namespace SE7 {
	template<class C>
	struct character_type {
		using type = C;
		static constexpr C null = static_cast<C>(0);
	};

	template<class C>
	class string_type {
	private:
		using char_type = character_type<C>;

		C *str;
		size_t len;

		static constexpr size_t length(const C *str) {
			size_t i = 0;

			while (str[i] != char_type::null) { i++; }

			return i;
		}
	public:
		string_type() : str(nullptr), len(0U) {}

		string_type(typename const char_type::type *str) {
			this->len = string_type::length(str);
			this->str = new C[this->len];

			for (size_t i = 0; i < this->len; i++) {
				this->str[i] = str[i];
			}
		}

		template<size_t N>
		string_type(typename const char_type::type (&str)[N]) {
			this->len = N;
			this->str = new C[N];

			for (size_t i = 0; i < this->len; i++) {
				this->str[i] = str[i];
			}
		}

		C &operator[](size_t n) const {
			return this->str[n];
		}

		size_t length() const {
			return this->len;
		}

		~string_type() {
			delete[] this->str;
		}
	};

	using string = string_type<char>;
	using wide_string = string_type<wchar_t>;
}

#endif // !SE7_STRING
