#ifndef SE7_OBJECT
#define SE7_OBJECT

#include <mutex>
#include <vector>

// Because GC and object depend on each other, gc is defined here.

namespace SE7 {
	class object;

	class garbage_collector {
	private:
		std::vector<object *> memory_pool;

		friend object;
	public:
		garbage_collector() {}

		void allocate(object *ptr) {
			if (ptr != nullptr) {
				this->memory_pool.push_back(ptr);
			}
		}

		~garbage_collector();
	};

	garbage_collector gc;

#define GC_NEW_CONSTRUCTIBLE(type)\
static void *operator new(size_t n) {\
type *ptr = new type();\
\
gc.allocate(ptr);\
\
return ptr;\
}\
\
static void *operator new(size_t n, garbage_collector &optional_gc) {\
	type *ptr = new type();\
\
	optional_gc.allocate(ptr);\
\
	return ptr;\
}

	class lock;

	template<class C>	
	class string_type;

	class object {
	private:
		friend lock;
	protected:
		std::mutex object_mutex;
	public:
		object() = default;
		object(const object &) = default;
		object(object &&) = default;

		// I feel like this is bad practice, but this will be defined in string.hpp.
		// There must be a better way of doing this (without C++20 import)...
		virtual string_type<char> to_string();
		virtual string_type<wchar_t> to_wstring();

		GC_NEW_CONSTRUCTIBLE(object)
	};

	garbage_collector::~garbage_collector() {
		for (object *obj : this->memory_pool) {
			delete obj;
		}
	}
}

#endif // !SE7_OBJECT
