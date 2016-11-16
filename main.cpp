#include "crypto.h"
//#include <gtest/gtest.h>

using namespace std;
using namespace FiniteField;

int main(int argc, char *argv[])
{
	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();

	try {

		Polynomial<5> p1,
				p2;

		p1.push_back(2);
		p2.push_back(3);
		p1[0] = p2[0] = 1;

		p2 = Polynomial<5>(3);
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

