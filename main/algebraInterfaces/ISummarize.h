//
// Created by artem on 1/21/17.
//

#ifndef CRYPTOGRAPHY_ISUMMARIZE_H
#define CRYPTOGRAPHY_ISUMMARIZE_H

#include <memory>

using namespace std;

class ISummarize;

class Refer {
public:
	shared_ptr<ISummarize> ptr;

//	operator ISummarize&() {
//		return *ptr;
//	}

	const Refer& operator=(const shared_ptr<ISummarize> &obj) {
		if (ptr != obj)
			ptr = obj;
		return *this;
	}


};

/*template <ISummarize T>
shared_ptr*/


class ISummarize {
public:
	//virtual const ISummarize& operator+= (const ISummarize& obj) = 0;
	//virtual ISummarize&& operator+(ISummarize& obj) const = 0;
	virtual shared_ptr<ISummarize> sum(shared_ptr<ISummarize> obj) const = 0;
	//virtual Refer& operator+(ISummarize& obj) const = 0;
	//virtual void sum(ISummarize &, ISummarize &, ISummarize &) = 0;
	virtual int get() const = 0;

	//virtual ~ISumm
};

class Derived : public virtual ISummarize {
	int a =4;
public:
	/*virtual Refer& operator+(ISummarize& obj) const {
		Refer ref;
		ref.ptr = shared_ptr<ISummarize>(new Derived());
		return ref;
	}*/

	virtual const ISummarize& operator+= (const ISummarize& obj) {
		a += obj.get();
		return *this;
	}

	//TODO: do bad dynamic_cast exception
	virtual shared_ptr<ISummarize> sum(shared_ptr<ISummarize> obj) const {
		try {
			shared_ptr<Derived> sum(new Derived());
			shared_ptr<Derived> obj2(dynamic_cast<Derived *>(obj.get()));	//bad
			if (nullptr == obj2)
				throw bad_alloc();
			sum->a = a + obj2->a;
			return sum;
		} catch(bad_alloc exp) {
			cout << exp.what() << endl;
		}
	}

	virtual int get() const {
		return a;
	}
};

#endif //CRYPTOGRAPHY_ISUMMARIZE_H
