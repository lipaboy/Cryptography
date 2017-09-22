//
// Created by artem on 8/12/16.
//

#include "numberPropertiesAlgorithms\PropertiesOfNumbers.h"

namespace CryptographyMath {

	int mainCrypto(int argc, char * argv[]) {
		using std::cout;
		using std::endl;

		if (gcdByEuclid<int>(18, 6) == 6)
			cout << "true" << endl;

		if (SolvePair<int>(2, -7) == useEuclideanAlgorithm<int>(18, 5))
			cout << "true" << endl;

		return 0;
	}

}
