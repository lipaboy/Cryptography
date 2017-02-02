//
// Created by artem on 1/21/17.
//

#ifndef CRYPTOGRAPHY_ISUMMARIZE_H
#define CRYPTOGRAPHY_ISUMMARIZE_H

#include <memory>
#include "SharedInheritPtr.h"

using namespace std;
using namespace SharedInheritPtrSpace;

template <class T>
class IGettable {
public:
	virtual T get() const = 0;
};

class IAddition {
public:
	virtual SharedInheritPtr<IAddition> add(const SharedInheritPtr<IAddition> obj) const = 0;
};

template <class T>
class IAlgebra : public virtual IAddition, public virtual IGettable<T> {};

class Derived : public IAddition, public IGettable<int> {
	int a = 4;
public:

	virtual SharedInheritPtr<IAddition> add(const SharedInheritPtr<IAddition> obj) const {
		const SharedInheritPtr<Derived> obj2 = obj;
		SharedInheritPtr<Derived> sum(new Derived());
		sum->a = a + obj2->get();
		return sum;
	}

	virtual int get() const {
		return a;
	}
};

template <class T>
class Opa{
private:
	const IAddition * con = dynamic_cast<IAddition *>(new T);
public:
	void doSmth() {

	}
};


#endif //CRYPTOGRAPHY_ISUMMARIZE_H
