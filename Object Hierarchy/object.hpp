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

	class object {
	private:
		std::mutex object_mutex;
	public:
		object() = default;
		object(const object &) = default;
		object(object &&) = default;

		GC_NEW_CONSTRUCTIBLE(object)
	};

	garbage_collector::~garbage_collector() {
		for (object *obj : this->memory_pool) {
			delete obj;
		}
	}
}

#endif // !SE7_OBJECT
