//
// Created by artem on 8/8/16.
//

#include <cmath>
#include "PropertiesOfNumbers.h"

namespace PropertiesOfNumbers {


	int gcdByEuclid(int a, int b)  {
		int gcd = 1;

		if (a < 1 || b < 1) {
			throw InvalidArguments();
		}
		else if (a != 1 && b != 1) {

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

	bool isPrime(int number) {
		int radical = static_cast<int>(std::sqrt(static_cast<double>(number)));

		if (radical < 2)
			throw InvalidArguments();

		for (int i = 2; i <= radical; i++)
			if (number % i == 0)
				return false;

		return true;
	}

	//Other functions

	//--------------class EratosthenesSieve--------------//

	//create sieve
	EratosthenesSieve::EratosthenesSieve(const int SIZE) : pSieve(new vector<bool>(SIZE, true))
	{
		vector<bool> &sieve = *pSieve;
		const size_t &size = sieve.size();

		for (int i = 2; i < size; i++)
			if (sieve[i] == true)	//is prime
				for (int j = i; i * j < size; j++)
					sieve[i * j] = false;

		switch (size) {
			default:
			case 2:	sieve[1] = false;			//notice, that here no break!
			case 1: sieve[0] = false; break;
		}
	}

}