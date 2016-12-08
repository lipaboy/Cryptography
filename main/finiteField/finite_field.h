//
// Created by artem on 8/11/16.
//

#ifndef CRYPTOGRAPHY_FINITEFIELD_H
#define CRYPTOGRAPHY_FINITEFIELD_H

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include "complexNumbers/complex_numbers.h"
#include "vector_extra/iovector.h"


using namespace std;
using namespace OutputVector;

namespace FiniteField {

	/*------------Exceptions------------*/
	class DivisionByZeroException : public runtime_error {
	public:
		explicit
		DivisionByZeroException() : runtime_error("Runtime error: division by zero. ") {}
	};

	class FiniteFieldException : public logic_error {
	public:
		explicit
		FiniteFieldException(const string &str) : logic_error(str) {}

	};

	class WrongTemplateParameterValueException : public FiniteFieldException {
	public:
		explicit
		WrongTemplateParameterValueException() :
				FiniteFieldException("Finite Field Exception: Wrong value of field characteristic '< 2'. ") {}
	};

	/*-------------------Main functions--------------*/

	inline int sign(int num) { return ((signbit(num) == true) ? -1 : 1); }

	//I don't want to do extra check on exception DivisionByZero in Polynom<modulus, T>
	class ConversionToFieldElements {
	private:
		static int getFieldElement(int number, int modulus);

		static double getFieldElement(double number, int modulus);

		static Complex<double> getFieldElement(Complex<double> number, int modulus);

		template <class T>
		static Complex<T> getFieldElement(Complex<T> number, int modulus) {
			return Complex<double>(getFieldElement(number.getReal(), modulus),
								   getFieldElement(number.getImaginary(), modulus));
		}

		/*---------------Friendship-----------------*/
	public:
		template<int modulus, class T>
		friend
		class PolynomModulus;

		template<class T>
		friend  T getFieldElement(T number, int modulus) throw(DivisionByZeroException);
	};

	template<class T>
	 T getFieldElement(T number, int modulus) throw(DivisionByZeroException) {
		if (modulus == 0)
			throw DivisionByZeroException();

		ConversionToFieldElements::getFieldElement(number, modulus);
	}


}

//template for module (characteristic) of field
#include "polynom_modulus.h"
#include "polynom_mod_2.h"


#endif //CRYPTOGRAPHY_FINITEFIELD_H
