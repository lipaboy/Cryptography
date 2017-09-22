//
// Created by artem on 8/19/16.
//

#ifndef CRYPTOGRAPHY_JACOBY_H
#define CRYPTOGRAPHY_JACOBY_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>


namespace CryptographyMath {

	template <class T>
	using SolvePair = std::pair<T, T>;

	template <class T>
	T gcdByEuclid(T a, T b) noexcept {
		// TODO: replace all the constants on real constants
		const T ZERO = static_cast<T>(0);
		const T ONE = static_cast<T>(1);
		const T TWO = static_cast<T>(2);
		T gcd = ONE;

		/*if (a < 1 || b < 1)
		throw InvalidArguments();*/
		if (a != 1 && b != 1)
		{
			while (a % 2 == 0 && b % 2 == 0) {
				a >>= 1;
				b >>= 1;
				gcd <<= 1;
			}
			while (a % 2 == 0)
				a >>= 1;
			while (b % 2 == 0)
				b >>= 1;
			while (a != b) {
				if (a > b) {
					a = (a - b) >> 1;
					while (a % 2 == 0)
						a >>= 1;
				}
				else {
					b = (b - a) >> 1;
					while (b % 2 == 0)
						b >>= 1;
				}
			}

			gcd *= a;
		}

		return gcd;
	}


	/*template <class T>
	SolvePair<T> useEuclideanAlgorithm(T const & first, T const & second) {

	}*/

	bool isPrime(int number);

	//I need Exceptions
	class EratosthenesSieve {
	public:
		EratosthenesSieve(const int SIZE);
		/* vector[i] = false   -    it means that number i isn't prime    */
		std::vector<bool> get() const { return *pSieve; }
		bool isPrime(int number) const { 
			return (size_t(number) < pSieve->size()) ? (*pSieve)[number] : false; }
	private:
		std::unique_ptr<std::vector<bool> > pSieve;
	};
}

namespace JacobySymbol {

	//I need tests
	int getValueJacobySymbol(int squareResidue, int modulus);

}


#endif //CRYPTOGRAPHY_JACOBY_H
