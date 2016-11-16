//
// Created by artem on 8/11/16.
//

#ifndef CRYPTOGRAPHY_FINITEFIELD_H
#define CRYPTOGRAPHY_FINITEFIELD_H

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <complex>
#include "../iovector/iovector.h"


using namespace std;
using namespace OutputVector;

namespace FiniteField {

	/*------------Exceptions------------*/
	class DivisionByZeroException: public runtime_error {
	public:
		explicit
		DivisionByZeroException() : runtime_error("Runtime error: division by zero. ") {}
	};

	class FiniteFieldException: public logic_error {
	public:
		explicit
		FiniteFieldException(const string& str) : logic_error(str) { }

	};

	class WrongTemplateParameterValueException: public FiniteFieldException {
	public:
		explicit
		WrongTemplateParameterValueException() :
				FiniteFieldException("Finite Field Exception: Wrong value of field characteristic '< 2'. ") {}
	};

	/*-------------------Main functions--------------*/

	inline int sign(int num) { return ((signbit(num) == true) ? -1 : 1); }

	//I don't want to do extra check on exception DivisionByZero in Polynomial<modulus, T>
	class ConversionToFieldElements {
	private:
		static int getFieldElement(int number, int modulus);

		static double getFieldElement(double number, int modulus);

		static complex<double> getFieldElement(complex<double> number, int modulus);

		/*---------------Friendship-----------------*/

		template <int modulus, class T>
		friend class Polynomial;

		template <class T>
		friend T getFieldElement(T number, int modulus) throw(DivisionByZeroException);
	};

	template <class T>
	T getFieldElement(T number, int modulus) throw(DivisionByZeroException) {
		if (modulus == 0)
			throw DivisionByZeroException();

		getFieldElement(number, modulus);
	}


}

//template for module (characteristic) of field
#include "polynom/polynomial.h"
#include "polynomial_mod_2.h"


#endif //CRYPTOGRAPHY_FINITEFIELD_H
