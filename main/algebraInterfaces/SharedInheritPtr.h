//
// Created by artem on 2/2/17.
//

#ifndef CRYPTOGRAPHY_SHAREDINHERITPTR_H
#define CRYPTOGRAPHY_SHAREDINHERITPTR_H

#include <memory>

using namespace std;

namespace SharedInheritPtrSpace {

	class BadDynamicCastException : public logic_error {
	public:
		explicit
		BadDynamicCastException() : logic_error("Bad dynamic cast exception") {}
	};

//--------------wrapper around shared_ptr----------//
	template<class T>
	class SharedInheritPtr {
	protected:
		shared_ptr<T> ptr;
	public:
		SharedInheritPtr() : ptr() {}

		SharedInheritPtr(T *ptr1) : ptr(ptr1) {}

		SharedInheritPtr(shared_ptr<T> ptr1) : ptr(ptr1) {}

		template<class S>
		SharedInheritPtr(const SharedInheritPtr<S> &obj) { ptr = dynamic_pointer_cast<T>(obj.getShared()); }

		template<class S>
		const SharedInheritPtr<T> &operator=(const SharedInheritPtr<S> &obj2) {
			if (nullptr == obj2.getShared())
				ptr.reset();        //*this = nullptr
			else {
				ptr = dynamic_pointer_cast<T>(obj2.getShared());
				if (nullptr == ptr)
					throw BadDynamicCastException();
			}
			return *this;
		}

		T *get() const noexcept { return ptr.get(); }

		T &operator*() const { return *get(); }

		T *operator->() const { return get(); }

		shared_ptr<T> getShared() const noexcept { return ptr; }

	};

}

#endif //CRYPTOGRAPHY_SHAREDINHERITPTR_H
