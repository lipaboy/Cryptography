//
// Created by artem on 8/11/16.
//

#ifndef CRYPTOGRAPHY_FINITEFIELD_H
#define CRYPTOGRAPHY_FINITEFIELD_H

#include <memory>
#include <cmath>


namespace CryptographyMath {

	/*------------Exceptions------------*/
		//maybe it need to move at Arithmetics Exception or smth like that
	/*class DivisionByZeroException : public runtime_error {
	public:
		explicit
		DivisionByZeroException() : runtime_error("Runtime error: division by zero. ") {}
	};*/

	class FiniteFieldException : public std::logic_error {
	public:
		explicit
		FiniteFieldException(std::string &&str) : std::logic_error(str) {}

	};

	class WrongTemplateParameterValueException : public FiniteFieldException {
	public:
		explicit
		WrongTemplateParameterValueException() :
				FiniteFieldException("Finite Field Exception: Wrong value of field characteristic '< 2'. ") {}
	};

	/*-------------------Main functions--------------*/

	inline int sign(int num) { return (num < 0 ? -1 : 1); }
}

//template for module (characteristic) of field
#include "FieldElement.h"


#endif //CRYPTOGRAPHY_FINITEFIELD_H
