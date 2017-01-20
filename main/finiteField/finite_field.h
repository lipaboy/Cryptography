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
		//maybe it need to move at Arithmetics Exception or smth like that
	/*class DivisionByZeroException : public runtime_error {
	public:
		explicit
		DivisionByZeroException() : runtime_error("Runtime error: division by zero. ") {}
	};*/

	class FiniteFieldException : public logic_error {
	public:
		explicit
		FiniteFieldException(string &&str) : logic_error(str) {}

	};

	class WrongTemplateParameterValueException : public FiniteFieldException {
	public:
		explicit
		WrongTemplateParameterValueException() :
				FiniteFieldException("Finite Field Exception: Wrong value of field characteristic '< 2'. ") {}
	};

	/*-------------------Main functions--------------*/

	inline int sign(int num) { return ((signbit(num) == true) ? -1 : 1); }

}

//template for module (characteristic) of field
#include "field_element.h"


#endif //CRYPTOGRAPHY_FINITEFIELD_H
