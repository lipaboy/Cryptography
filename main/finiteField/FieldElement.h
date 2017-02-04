//
// Created by artem on 11/16/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIALMODULUS_H
#define CRYPTOGRAPHY_POLYNOMIALMODULUS_H

#include "algebraInterfaces/IAlgebra.h"

//TODO: remove using namespace because impossible to use Derived name (cover with name from AlgebraInterfaces)

namespace FiniteField {

	using namespace PolymorphicTypeCasting;

	//maybe I need to do wrapper to interrupt producing more and more constructors

	//template for module (characteristic) of field
	//Is modulus prime?

	/*static int getFieldElement(int number, int modulus) {
		//you need to remove it when you will have specialization of Polynom<2>
		if (modulus == 2)
			return abs(number % modulus);
		return number % modulus - ((2 * std::abs(number % modulus) <= modulus) ? 0 : sign(number) * modulus);
	}

	//for floating point numbers
	static double getFieldElement(double number, int modulus) {
		int mod = static_cast<int>(floor(number));

		return getFieldElement(mod, modulus) + (number - mod);    //float-point
	}

	static Complex<double> getFieldElement(Complex<double> number, int modulus) {

		return Complex<double>(getFieldElement(number.getReal(), modulus),
							   getFieldElement(number.getImaginary(), modulus));
	}*/

	//IN FACT: no economy operations and memory
	template <int modulus>
	class FieldElement : public AlgebraInterfaces::IAlgebra<int> {
		int elem;

		//TODO: you can write specialization with modulus = 2 because returning value of this function would be easier
		int castToFieldElement(int val) {
			return val % modulus - ((2 * std::abs(val % modulus) <= modulus) ? 0 : sign(val) * modulus);
		}
	public:
		//, FieldElement() - I can't write it because the execution of parameter list is undefined
		FieldElement(int val) : elem(castToFieldElement(val)) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}

		const FieldElement& operator=(int val) { elem = castToFieldElement(val); }

		//selectors

		FieldElement operator+(const FieldElement& obj) const {	return FieldElement(elem + obj.elem); }
		const FieldElement& operator+=(const FieldElement& obj) {
			elem = castToFieldElement(elem + obj.elem);
			return (*this);
		}
		FieldElement operator*(const FieldElement& obj) const {	return FieldElement(elem * obj.elem); }
		const FieldElement& operator*=(const FieldElement& obj) {
			elem = castToFieldElement(elem * obj.elem);
			return (*this);
		}
		FieldElement operator-() const { return FieldElement(-elem); }
		FieldElement operator-(const FieldElement& obj) const {	return (*this) + (-obj); }
		const FieldElement& operator-=(const FieldElement& obj) { return (*this) -= obj; }

		bool operator!=(const FieldElement& obj) const { return (elem != obj.elem); }	//already casted to field elems
		bool operator==(const FieldElement& obj) const { return !((*this) != obj); }

		//implementations

		SharedPolymPtr<AlgebraInterfaces::IAddition> add(SharedPolymPtr<AlgebraInterfaces::IAddition> obj) const {
			SharedPolymPtr<FieldElement> obj2 = obj;
			SharedPolymPtr<FieldElement> sum(new FieldElement(0));
			(*sum) = (*this) + (*obj2);
			return sum;
		}
		//IGet
		int get() const { return elem; }
	};



//	template<>
//	class FieldElement<2> {
//	protected:
//		virtual int castToFieldElement(int val) {
//			return abs(val % 2);
//		}
//	};
}




#endif //CRYPTOGRAPHY_POLYNOMIALMODULUS_H
