//
// Created by artem on 8/12/16.
//

#include "crypto.h"

using namespace CryptographyMath;



int main(void)
{
	try {
		vector<int> vec;
		vec.push_back(2);
		vec.push_back(3);
		Polynom<int> s1 = Polynom<int>(vec);
		s1.push_back(5);
		s1.push_back(3);
		cout << s1 << endl;
		Polynom<int> s2 = s1 + s1;
		Polynom<int> s3(Polynom<int>(s2 + s1));
		cout << s3 << endl;

		ElementInt<5> a(2),
				b(3);


		//A::bar();
	}
	catch (logic_error exp){
		cout << exp.what();
	}
	catch (runtime_error exp){
		cout << exp.what();
	}

	return 0;
}
