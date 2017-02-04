//
// Created by artem on 2/2/17.
//

#ifndef CRYPTOGRAPHY_SHAREDINHERITPTR_H
#define CRYPTOGRAPHY_SHAREDINHERITPTR_H

#include <memory>

namespace PolymorphicTypeCasting {

	class BadDynamicCastException : public std::logic_error {
	public:
		explicit
		BadDynamicCastException() : logic_error("Bad dynamic cast exception") {}
	};

		//--------------wrapper around shared_ptr----------//
	//TODO: may be do SharedInheritPtrNotNull
	template<class T>
	class SharedPolymPtr {
	protected:
		std::shared_ptr<T> ptr;

		template <class S>
		std::shared_ptr<T> dynamicSharedPtrCast(const std::shared_ptr<S>& ptrS) {
			std::shared_ptr<T> ptrT;
			if (nullptr == ptrS)
				ptrT.reset();        //*this = nullptr
			else {
				ptrT = std::dynamic_pointer_cast<T>(ptrS);

				if (nullptr == ptrT)
					throw BadDynamicCastException();
			}
			return ptrT;
		}
	public:
		//-------constructors-----//
		SharedPolymPtr() : ptr() {}

		SharedPolymPtr(T *ptr1) : ptr(ptr1) {}

		SharedPolymPtr(std::shared_ptr<T> ptr1) : ptr(ptr1) {}

		template<class S>
		SharedPolymPtr(const SharedPolymPtr<S>& obj) { ptr = dynamicSharedPtrCast(obj.getShared()); }

		//-------methods----------//
		template<class S>
		const SharedPolymPtr<T> &operator=(const SharedPolymPtr<S> &obj) {
			ptr = dynamicSharedPtrCast(obj.getShared());
			return *this;
		}

		T* get() const noexcept { return ptr.get(); }

		T& operator*() const { return *get(); }

		T* operator->() const { return get(); }

		const std::shared_ptr<T>& getShared() const noexcept { return ptr; }

	};

}

#endif //CRYPTOGRAPHY_SHAREDINHERITPTR_H
