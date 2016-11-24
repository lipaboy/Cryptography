//
// Created by artem on 8/8/16.
//

#include "complexNumbers/complex_numbers.h"
#include "finite_field.h"


namespace FiniteField {


		int ConversionToFieldElements::getFieldElement(int number, int modulus) {
			//you need to remove it when you will have specialization of Polynom<2>
			if (modulus == 2)
				return abs(number % modulus);
			return number % modulus - ((2 * std::abs(number % modulus) <= modulus) ? 0 : sign(number) * modulus);
		}

		//for floating point numbers
		double ConversionToFieldElements::getFieldElement(double number, int modulus) {
			int mod = static_cast<int>(floor(number));

			return getFieldElement(mod, modulus) + (number - mod);    //float-point
		}

		Complex<double> ConversionToFieldElements::getFieldElement(Complex<double> number, int modulus) {

			return Complex<double>(getFieldElement(number.getReal(), modulus),
								   getFieldElement(number.getImaginary(), modulus));
		}


}


