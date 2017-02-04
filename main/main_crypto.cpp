//
// Created by artem on 8/12/16.
//

#include "CryptographyMath.h"

using namespace CryptographyMath;

#include "algebraInterfaces/IAlgebra.h"

using namespace std;
using namespace AlgebraInterfaces;

int main(void)
{
	try {
		typedef SharedPolymPtr<IAlgebra<int> > IAlgebraPtr;

		IAlgebraPtr a(new FieldElement<5>(1)),
			d(new FieldElement<6>(1));

		d->add(a);

	}
	catch (logic_error exp){
		cout << exp.what() << endl;
	}
	catch (runtime_error exp){
		cout << exp.what() << endl;
	}

	return 0;
}
