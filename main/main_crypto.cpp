//
// Created by artem on 8/12/16.
//

#include "crypto.h"

using namespace CryptographyMath;

#include "algebraInterfaces/ISummarize.h"


int main(void)
{
	try {
/*Polynom<Complex<double>> p;
		Algebra1 a;
		cout << (((a + a).operator*()) + 5) << endl;
		(a + a);
		cout << (a + 5) << endl;
		shared_ptr<Derived> b(new Derived());
		shared_ptr<ISummarize> ref(b->sum(b));
		shared_ptr<Derived> ref2(b->sum(b));
		ref.ISummarize&().
		ISummarize & sum = ref;*/
		SharedCastPtr<Derived> ptr(new Derived()),
			ptr2 = ptr,
			ptr3 = ptr2;

		SharedCastPtr<ISummarize> sum;
		sum = ptr;
		//ptr2 = sum;
		cout << (sum->get()) << " " << ptr2->get() << endl;

		//cout << ptr.use_count() << " " << ptr2.use_count() << " " << ptr3.use_count() << endl;
shared_ptr<int> p(new int(5));
		p.

	}
	catch (logic_error exp){
		cout << exp.what() << endl;
	}
	catch (runtime_error exp){
		cout << exp.what() << endl;
	}

	return 0;
}
