#ifndef SE7_FUNCTION
#define SE7_FUNCTION

#include <tuple>
#include <memory>
#include <algorithm>
#include <type_traits>

#include "object.hpp"
#include "exception.hpp"

namespace SE7 {
	template<class T>
	class function;

	template<class ret, class... argv>
	class function<ret(argv...)> : public object {
	private:
		class callable_t {
		public:
			virtual callable_t *clone() = 0;
			virtual ret invoke(argv...) = 0;
			virtual ~callable_t() {};
		};

		template<class T>
		class callable : public callable_t {
		private:
			T t;
		public:
			callable(T t) : t(t) {}

			virtual callable *clone() {
				// This will only be used internally with std::unique_ptr, which will automatically
				// manage the newly allocated memory for us.
				return new callable(this->t);
			}

			virtual ret invoke(argv... args) override {
				return this->t(args...);
			}

			virtual ~callable() override {};
		};

		std::unique_ptr<callable_t> p_callable;
	public:
		function() {}

		template<class F>
		function(F fn) {
			this->p_callable = std::make_unique<callable<F>>(fn);
		}

		function(const function &f) {
			this->p_callable = std::unique_ptr<callable_t>(f.p_callable->clone());
		}

		function(function &&f) {
			if (this != &f) {
				this->p_callable = std::move(f.p_callable);
			}
		}

		GC_NEW_CONSTRUCTIBLE(function<ret(argv...)>)

		template<class F>
		function &operator=(F fn) {
			this->p_callable = std::make_unique<callable<F>>(fn);
			return *this;
		}

		bool empty() const {
			return this->p_callable.operator bool();
		}

		ret operator()(argv... args) const {
			if (!this->p_callable) {
				throw empty_function();
			}

			return this->p_callable->invoke(args...);
		}
	};
}

#endif // !SE7_FUNCTION
