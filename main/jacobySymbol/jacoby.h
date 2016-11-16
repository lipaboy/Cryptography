//
// Created by artem on 8/19/16.
//

#ifndef CRYPTOGRAPHY_JACOBY_H
#define CRYPTOGRAPHY_JACOBY_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

namespace PropertiesOfNumbers{

	class InvalidArguments : public runtime_error {
		string msg = "Runtime exception: invalid arguments. ";
	public:
		explicit
		InvalidArguments() : runtime_error(msg) {}

		explicit
		InvalidArguments(string str) : runtime_error(msg + str) {}
	};

	bool isPrime(int number);

	int gcdByEuclid(int a, int b);

	//I need Exceptions
	class EratosthenesSieve {
	private:
		unique_ptr<vector<bool> > pSieve;

	public:
		EratosthenesSieve(const int SIZE);

		/* vector[i] = false   -    it means that number i isn't prime    */
		vector<bool> get() const { return *pSieve; }

		bool isPrime(int number) const { return (number < pSieve->size()) ? (*pSieve)[number] : false; }
	};
}

namespace JacobySymbol {

	//I need tests
	int getValueJacobySymbol(int squareResidue, int modulus);

}


#endif //CRYPTOGRAPHY_JACOBY_H
