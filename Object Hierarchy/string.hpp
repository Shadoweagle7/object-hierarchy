#ifndef SE7_STRING
#define SE7_STRING

#include <iostream>
#include <string>
#include <string_view>

#include "object.hpp"
#include "primitive.hpp"

namespace SE7 {
	template<class C>
	class string_type : public string_base<C>, public object {
	private:
		std::basic_string<C> internal_str;

		friend std::ostream &operator<<(std::ostream &os, const string_type<C> &s) {
			os << s.operator std::basic_string_view<C, std::char_traits<C>>();

			return os;
		}

		friend std::istream &operator>>(std::istream &is, string_type<C> &s) {
			std::basic_string<C> str = s.operator std::basic_string<C, std::char_traits<C>, std::allocator<C>> &();

			is >> str;

			return is;
		}

		friend std::wostream &operator<<(std::wostream &wos, const string_type<C> &s) {
			wos << s.operator std::basic_string_view<C, std::char_traits<C>>();

			return wos;
		}

		friend std::wistream &operator>>(std::wistream &wis, string_type<C> &s) {
			std::basic_string<C> &str = s.operator std::basic_string<C, std::char_traits<C>, std::allocator<C>> & ();

			wis >> str;

			return wis;
		}
	public:
		static constexpr size_t npos = -1;

		string_type() {}

		string_type(std::basic_string_view<C> str) : internal_str(str) {}

		template<size_t N>
		string_type(const C (&str)[N]) : internal_str(str) {}

		string_type(const C *str) : internal_str(str) {}

		size_t length() const {
			return this->internal_str.length();
		}

		const C *c_str() const {
			return this->internal_str.c_str();
		}

		C &operator[](const size_t n) {
			return this->internal_str[n];
		}

		const C &operator[](const size_t n) const {
			return this->internal_str[n];
		}

		string_type *substring(size_t offset, size_t count) const {
			return new string_type(this->internal_str.substr(offset, count));
		}

		typename std::basic_string<C>::iterator begin() const {
			return this->internal_str.begin();
		}

		typename std::basic_string<C>::const_iterator begin() {
			return this->internal_str.begin();
		}

		typename std::basic_string<C>::iterator end() const {
			return this->internal_str.end();
		}

		typename std::basic_string<C>::const_iterator end() {
			return this->internal_str.end();
		}

		bool empty() const {
			return this->internal_str.empty();
		}

		operator std::basic_string<C> &() const {
			return this->internal_str;
		}

		operator std::basic_string_view<C>() const {
			return this->internal_str;
		}

		GC_NEW_CONSTRUCTIBLE(string_type)
	};

	using string = string_type<char>;
	using wide_string = string_type<wchar_t>;
}

#endif // !SE7_STRING
