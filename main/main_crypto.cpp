//
// Created by artem on 8/12/16.
//

#include "numberPropertiesAlgorithms\PropertiesOfNumbers.h"

namespace CryptographyMath {

	int mainCrypto(int argc, char * argv[]) {
		using std::cout;
		using std::endl;

		cout << (gcdByEuclid<int>(18, 6) == 6) << " ";

		cout << (SolvePair<int>(2, -7) == useCommonEuclideanAlgorithm<int>(18, 5)) << " ";

		cout << (getContraryDegree<int>(5, 19) == 11) << " ";

		cout << (modulusPower<int>(2, 55, 19) == 2) << " ";


		cout << endl;

		return 0;
	}

}
