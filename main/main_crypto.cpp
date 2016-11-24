//
// Created by artem on 8/12/16.
//

#include "crypto.h"

using namespace CryptographyMath;

int main(void)
{
	try {
getFieldElement(5, 0);
		PolynomModulus<5> p1,
					p2;

		p1.push_back(2);
		p2.push_back(3);
		p1[0] = p2[0] = 1;

		p2 = PolynomModulus<5>(3);
		p2 = p1;
		cout << p2 << endl;
		//cout << p1 << " + " << p2 << " = " << p1 + p2 << endl;

		PolynomModulus<3, Complex<double> > p3;
		p3.push_back(Complex<double>(5));
		p3.push_back(Complex<double>(0, 3));
		cout << p3 << endl;

		//no Complex<int>
	}
	catch (logic_error exp){
		cout << exp.what();
	}
	catch (runtime_error exp){
		cout << exp.what();
	}

	return 0;
}
