//
// Created by artem on 8/12/16.
//

#include "numberPropertiesAlgorithms\PropertiesOfNumbers.h"

namespace CryptographyMath {

	int mainCrypto(int argc, char * argv[]) {
		using std::cout;
		using std::endl;

		cout << (gcdByEuclid<int>(18, 6) == 6) << endl;

		cout << (SolvePair<int>(2, -7) == useCommonEuclideanAlgorithm<int>(18, 5)) << endl;

		cout << (getContraryDegree<int>(5, 19) == 11) << endl;

		return 0;
	}

}
