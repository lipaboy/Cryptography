//
// Created by artem on 8/12/16.
//

#include "crypto.h"

using namespace CryptographyMath;

#include "algebraInterfaces/ISummarize.h"


int main(void)
{
	try {
//Polynom<Complex<double>> p;
		Algebra1 a;
		cout << (((a + a).operator*()) + 5) << endl;
		//(a + a);
//		cout << (a + 5) << endl;
		shared_ptr<Derived> b(new Derived());
		shared_ptr<ISummarize> ref(b->sum(b));
		shared_ptr<Derived> ref2(b->sum(b));
		//ref.ISummarize&().
		//ISummarize & sum = ref;

		cout << ref->get() << endl;

	}
	catch (logic_error exp){
		cout << exp.what() << endl;
	}
	catch (runtime_error exp){
		cout << exp.what() << endl;
	}

	return 0;
}
