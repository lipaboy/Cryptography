//
// Created by artem on 8/12/16.
//

#include "CryptographyMath.h"

using namespace CryptographyMath;

#include "algebraInterfaces/IAddition.h"


int main(void)
{
	try {
/*Polynom<Complex<double>> p;
		Algebra1 a;
		cout << (((a + a).operator*()) + 5) << endl;
		(a + a);
		cout << (a + 5) << endl;
		shared_ptr<Derived> b(new Derived());
		shared_ptr<IAddition> ref(b->sum(b));
		shared_ptr<Derived> ref2(b->sum(b));
		ref.IAddition&().
		IAddition & sum = ref;*/
		SharedInheritPtr<Derived> ptr(new Derived());
		SharedInheritPtr<IAlgebra<int> > ptr1 = ptr, ptr2 = ptr;

		//cout << (ptr1 + ptr2)->get() << endl;
		ptr1 = ptr1->add(ptr2);
		cout << ptr1->get() << endl;

		Opa<Derived> opa;
		opa.doSmth();
		//Opa<int> opp;
		//opp.doSmth();

		//cout << ptr.use_count() << " " << ptr2.use_count() << " " << ptr3.use_count() << endl;
//shared_ptr<int> p(new int(5));
	//	p.

	}
	catch (logic_error exp){
		cout << exp.what() << endl;
	}
	catch (runtime_error exp){
		cout << exp.what() << endl;
	}

	return 0;
}
