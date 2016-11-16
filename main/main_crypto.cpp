//
// Created by artem on 8/12/16.
//

#include "crypto.h"

using namespace CryptographyMath;
using namespace FiniteField;

int main(void)
{
	try {

		PolynomialModulus<5> p1,
					p2;

		p1.push_back(2);
		p2.push_back(3);
		p1[0] = p2[0] = 1;

		p2 = PolynomialModulus<5>(3);
		p2 = p1;
		cout << p2 << endl;
		//cout << p1 << " + " << p2 << " = " << p1 + p2 << endl;

	}
	catch (logic_error exp){
		cout << exp.what();
	}
	catch (runtime_error exp){
		cout << exp.what();
	}

	return 0;
}
