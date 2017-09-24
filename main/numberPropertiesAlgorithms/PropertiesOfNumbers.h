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


	template <class T>
	SolvePair<T> useCommonEuclideanAlgorithm(T const & first, T const & second) {
		const T ZERO = T(0);	//or maybe change on T(0) ??
		const T ONE = T(1);
		const T TWO = T(2);
		const T gcd = gcdByEuclid(first, second);

		// we have three arrays
		T arr[3][3] = {
			first,	ONE,	ZERO,
			second,	ZERO,	ONE,
			ONE,	ZERO,	ZERO
		};

		int i;
		int j;
		int k;
		for (i = 0; ; i = (i + 1) % 3) {
			j = (i + 1) % 3;
			k = (i + 2) % 3;

			int coef = arr[i][0] / arr[j][0];
			arr[k][0] = arr[i][0] % arr[j][0];
			arr[k][1] = arr[i][1] - coef * arr[j][1];
			arr[k][2] = arr[i][2] - coef * arr[j][2];

			if (ZERO == arr[k][0])
				break;
		}

		// TODO: check with polynom (where maybe work constructor copy but not move-one)
		return std::make_pair(arr[j][1], arr[j][2]);
	}

	// a ^ (c * d) = 1 (mod p), where we need to find d. (! gcd(c, p - 1) == 1)
	template <class T>
	inline T getContraryDegree(T const & degree, T const & modulus) {
		T contrary = useCommonEuclideanAlgorithm<T>(modulus - T(1), degree).second;
		return std::move((contrary < 0) ? contrary + (modulus - 1) : contrary);
	}

	template <class T>
	T modulusPower(T const & value, T const & degree, T const & modulus) {
		T result = T(1);
		for (T i = T(0); i < degree; i += 1) {
			result = (result * value) % modulus;
		}
		return std::move(result);
	}



	// ---------------------- Old ----------------------------------- //

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
