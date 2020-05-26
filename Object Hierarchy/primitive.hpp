#ifndef SE7_PRIMITIVE
#define SE7_PRIMITIVE

#include <type_traits>
#include <cstring>

#include "object.hpp"
#include "exception.hpp"

namespace SE7 {
	template<class T, class = typename std::enable_if<!std::is_class<T>::value, void>::type>
	class primitive : public object {
	private:
		T val;
	public:
		primitive() {
			std::memset(&this->val, 0, sizeof(T));
		}

		primitive(T val) {
			this->val = val;
		}

		primitive(const primitive<T> &p) : val(p.val) {}

		primitive(primitive<T> &&p) : val(p.val) {
			std::memset(&p.val, 0, sizeof(T));
		}

		GC_NEW_CONSTRUCTIBLE(primitive<T>)

		primitive<T> operator=(primitive<T> t) {
			this->val = t.val;
			return *this;
		}

		primitive<T> operator+(primitive<T> t) {
			return primitive<T>(this->val + t.val);
		}

		primitive<T> operator-(primitive<T> t) {
			return primitive<T>(this->val - t.val);
		}

		primitive<T> operator*(primitive<T> t) {
			return primitive<T>(this->val * t.val);
		}

		primitive<T> operator/(primitive<T> t) {
			if (t.val == 0) {
				throw divide_by_zero();
			}

			return primitive<T>(this->val / t.val);
		}

		// TODO: How to do this?
		primitive<T> operator+() {
			return *this;
		}

		primitive<T> operator-() {
			return primitive<T>(-1 * this->val);
		}

		primitive<T> operator%(primitive<T> t) {
			return primitive<T>(this->val % t.val);
		}

		primitive<T> &operator++() {
			++this->val;
			return *this;
		}

		primitive<T> operator++(int) {
			primitive<T> temp(*this);
			this->val++;
			return temp;
		}

		primitive<T> &operator--() {
			--this->val;
			return *this;
		}

		primitive<T> operator--(int) {
			primitive<T> temp(*this);
			this->val--;
			return temp;
		}

		bool operator==(primitive<T> t) const {
			return this->val == t.val;
		}

		bool operator!=(primitive<T> t) const {
			return this->val != t.val;
		}

		bool operator>(primitive<T> t) const {
			return this->val > t.val;
		}

		bool operator<(primitive<T> t) const {
			return this->val < t.val;
		}

		bool operator>=(primitive<T> t) const {
			return this->val >= t.val;
		}

		bool operator<=(primitive<T> t) const {
			return this->val <= t.val;
		}

		// Three - way comparison here when available

		bool operator!() const {
			return !this->val;
		}

		bool operator&&(primitive<T> t) const {
			return this->val && t.val;
		}

		bool operator||(primitive<T> t) const {
			return this->val || t.val;
		}

		primitive<T> operator~() const {
			return primitive<T>(~this->val);
		}

		primitive<T> operator&(primitive<T> t) const {
			return primitive<T>(this->val & t.val);
		}

		primitive<T> operator|(primitive<T> t) const {
			return primitive<T>(this->val | t.val);
		}

		primitive<T> operator^(primitive<T> t) const {
			return primitive<T>(this->val ^ t.val);
		}

		primitive<T> operator<<(primitive<T> t) const {
			return primitive<T>(this->val << t.val);
		}

		primitive<T> operator>>(primitive<T> t) const {
			return primitive<T>(this->val >> t.val);
		}

		primitive<T> &operator+=(primitive<T> t) {
			this->val += t.val;
			return *this;
		}

		primitive<T> &operator-=(primitive<T> t) {
			this->val -= t.val;
			return *this;
		}

		primitive<T> &operator*=(primitive<T> t) {
			this->val *= t.val;
			return *this;
		}

		primitive<T> &operator/=(primitive<T> t) {
			if (t.val == 0) {
				throw divide_by_zero();
			}

			this->val /= t.val;
			return *this;
		}

		primitive<T> &operator%=(primitive<T> t) {
			this->val %= t.val;
			return *this;
		}

		primitive<T> &operator&=(primitive<T> t) {
			this->val &= t.val;
			return *this;
		}

		primitive<T> &operator|=(primitive<T> t) {
			this->val |= t.val;
			return *this;
		}

		primitive<T> &operator^=(primitive<T> t) {
			this->val ^= t.val;
			return *this;
		}

		primitive<T> &operator<<=(primitive<T> t) {
			this->val <<= t.val;
			return *this;
		}

		primitive<T> &operator>>=(primitive<T> t) {
			this->val >>= t.val;
			return *this;
		}

		operator T() const {
			return this->val;
		}
	};

	using character = primitive<char>;
	using boolean = primitive<bool>;
	using unsigned_character = primitive<unsigned char>;
	using wide_character = primitive<wchar_t>;
	using short_integer = primitive<short>;
	using unsigned_short_integer = primitive<unsigned short>;
	using integer = primitive<int>;
	using unsigned_integer = primitive<unsigned int>;
	using long_integer = primitive<long int>;
	using unsigned_long_integer = primitive<unsigned long int>;
	using long_long_integer = primitive<long long int>;
	using unsigned_long_long_integer = primitive<unsigned long long int>;
	using single_precision_floating_point = primitive<float>;
	using double_precision_floating_point = primitive<double>;
}

#endif // !SE7_PRIMITIVE
