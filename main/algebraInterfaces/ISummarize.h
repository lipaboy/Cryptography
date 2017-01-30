//
// Created by artem on 1/21/17.
//

#ifndef CRYPTOGRAPHY_ISUMMARIZE_H
#define CRYPTOGRAPHY_ISUMMARIZE_H

#include <memory>

using namespace std;

class BadDynamicCastException : public logic_error {
public:
	explicit
	BadDynamicCastException() : logic_error("Bad dynamic cast exception") {}
};

class ISummarize;
class Derived;

template <class T>
class SharedCastPtr {
private:
	shared_ptr<T> ptr;
public:
	SharedCastPtr(T *ptr1) : ptr(ptr1) {}
	SharedCastPtr(shared_ptr<T> ptr1) : ptr(ptr1) {}

	template <class S>
	const SharedCastPtr<T>& operator=(const SharedCastPtr<S>& obj2)
	{
		if (nullptr == obj2.ptr)
			ptr.reset();		//*this = nullptr
		else {
			ptr = dynamic_pointer_cast<T>(obj2.ptr);
			if (nullptr == ptr)
				throw BadDynamicCastException();
		}
		return *this;
	}



	/*const SharedCastPtr<T>& operator=(const shared_ptr<T>& obj2)
	{
		//if (this->get() != obj2.get())
		shared_ptr<T> &ref = (*this);
		ref = obj2;
		return *this;
	}*/
};

/*template< class T, class U >
std::SharedCastPtr<T> dynamic_pointer_cast( const std::SharedCastPtr<U>& r ) noexcept
{
	if (auto p = dynamic_cast<typename std::SharedCastPtr<T>::element_type*>(r.get())) {
		return std::SharedCastPtr<T>(r, p);
	} else {
		return std::SharedCastPtr<T>();
	}
}*/





class ISummarize {
public:
	ISummarize() {}

	virtual ISummarize operator+ (const ISummarize& obj) const {}

	virtual int get() {}

	virtual ~ISummarize() {}
};

class Derived : public virtual ISummarize {
	int a = 4;
public:

	virtual ISummarize operator+ (const ISummarize& obj) const {
		const Derived &obj2 = dynamic_cast<const Derived&>(obj);
		Derived sum;
		sum.a = a + obj2.a;
		return sum;
	}

	virtual int get() const {
		return a;
	}
};



#endif //CRYPTOGRAPHY_ISUMMARIZE_H
