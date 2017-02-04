//
// Created by artem on 1/21/17.
//

#ifndef CRYPTOGRAPHY_ISUMMARIZE_H
#define CRYPTOGRAPHY_ISUMMARIZE_H

#include <memory>
#include "polymorphicTypeCasting/SharedPolymPtr.h"

namespace AlgebraInterfaces {

	using namespace PolymorphicTypeCasting;

	template<class T>
	class IGet {
	public:
		virtual T get() const = 0;
	};

	//Useful or not???
//template <class T>
//class IPut {
//public:
//	virtual T put() = 0;
//};
	class IAddition {
	public:
		//WARNING:
		//I can't use "const SharedPolymPtr<IAlgebra>& obj" format to give parameters to method
		//because "dynamic_pointer_cast" won't be done.
		virtual SharedPolymPtr<IAddition> add(SharedPolymPtr<IAddition> obj) const = 0;
	};

	template<class T>
	class IAlgebra : public virtual IAddition, public virtual IGet<T>
		//, public virtual IPut<T>
	{
	};

	template<class T>
	std::ostream &operator<<(std::ostream &o, IGet<T> elem) {
		return (o << elem.get());
	};


//--------------Testing-------------//

/*
	class Derived : public virtual IAlgebra<int> {
		int a = 4;
	public:

		virtual SharedPolymPtr<IAlgebra> add(const SharedPolymPtr<IAlgebra> &obj) const {
			const SharedPolymPtr<Derived> obj2 = obj;
			SharedPolymPtr<Derived> sum(new Derived());
			sum->a = a + obj2->get();
			return sum;
		}

		virtual int get() const {
			return a;
		}
	};*/

		//-------------Problem Solution---------------//

//-----------------Constraint on template-------------//

	template<class T>
	class Opa {
	private:
		const IAddition *con = dynamic_cast<const IAddition *>(new T);
	public:
		void doSmth() {

		}
	};
}

#endif //CRYPTOGRAPHY_ISUMMARIZE_H
