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
	class string_type : public object {
	private:
		using char_type = character_type<C>;

		C *str;
		size_t len;

		static constexpr size_t length(const C *str) {
			size_t i = 0;

			while (str[i] != char_type::null) { i++; }

			return i;
		}

		string_type(size_t len) {
			this->str = new C[len];
			this->len = len;
		}
	public:
		string_type() : str(new C[1]), len(0U) {}

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

		GC_NEW_CONSTRUCTIBLE(string_type);

		string_type operator+(string_type s) {
			string_type str(this->len + s.len);

			size_t i = 0;

			for (; i < this->len; i++) {
				str[i] = this->str[i];
			}

			for (; i < this->len + s.len; i++) {
				str[i] = s.str[i];
			}

			return str;
		}

		C &operator[](size_t n) const {
			return this->str[n];
		}

		size_t length() const {
			return this->len;
		}

		virtual string_type<char> to_string() {
			return *this;
		}

		virtual string_type<wchar_t> to_wstring() {
			return L"";
		}

		~string_type() {
			delete[] this->str;
		}
	};

	using string = string_type<char>;
	using wide_string = string_type<wchar_t>;

	string object::to_string() {
		return "object";
	}

	string object::to_wstring() {
		return L"object";
	}
}

#endif // !SE7_STRING
