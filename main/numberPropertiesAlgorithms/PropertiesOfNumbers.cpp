//
// Created by artem on 8/8/16.
//

#include <cmath>
#include "PropertiesOfNumbers.h"

namespace CryptographyMath {


	bool isPrime(int number) {
		int radical = static_cast<int>(std::sqrt(static_cast<double>(number)));

		/*if (radical < 2)
			throw InvalidArguments();*/

		for (int i = 2; i <= radical; i++)
			if (number % i == 0)
				return false;

		return true;
	}

	//Other functions

	//--------------class EratosthenesSieve--------------//

	//create sieve
	EratosthenesSieve::EratosthenesSieve(const int SIZE) : pSieve(new std::vector<bool>(SIZE, true))
	{
		std::vector<bool> &sieve = *pSieve;
		const size_t &size = sieve.size();

		for (int i = 2; size_t(i) < size; i++)
			if (sieve[i] == true)	//is prime
				for (int j = i; size_t(i * j) < size; j++)
					sieve[i * j] = false;

		switch (size) {
			default:
			case 2:	sieve[1] = false;			//notice, that here no break!
			case 1: sieve[0] = false; break;
		}
	}

}