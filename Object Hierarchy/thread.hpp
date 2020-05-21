#ifndef SE7_THREAD
#define SE7_THREAD

#include <thread>

#include "function.hpp"

namespace SE7 {
	using thread = std::thread;

	class lock {
	private:
		object &obj;
	public:
		lock(object &obj) : obj(obj) {
			obj.object_mutex.lock();
		}

		~lock() {
			this->obj.object_mutex.unlock();
		}
	};
}

#endif // !SE7_THREAD
