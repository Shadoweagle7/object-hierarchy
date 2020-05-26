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
type *ptr = ::new type();\
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
	class string_base {
	public:
		virtual size_t length() const = 0;
		virtual const C *c_str() const = 0;
		virtual C &operator[](const size_t) = 0;
		virtual const C &operator[](const size_t) const = 0;
		virtual string_base *substring(size_t, size_t) const = 0;



		virtual bool empty() const = 0;
	};

	class object {
	private:
		friend lock;
	protected:
		std::mutex object_mutex;
	public:
		object() = default;
		object(const object &) = default;
		object(object &&) = default;

		GC_NEW_CONSTRUCTIBLE(object)

		virtual string_base<char> *to_string() {
			return nullptr; // TODO: STUB
		}

		virtual string_base<wchar_t> *to_wstring() {
			return nullptr; // TODO: STUB
		}
	};

	garbage_collector::~garbage_collector() {
		for (object *obj : this->memory_pool) {
			delete obj;
		}
	}
}

#endif // !SE7_OBJECT
