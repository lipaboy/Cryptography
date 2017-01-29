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

//Not interface
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
