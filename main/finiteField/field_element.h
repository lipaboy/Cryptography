//
// Created by artem on 11/16/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIALMODULUS_H
#define CRYPTOGRAPHY_POLYNOMIALMODULUS_H

#include "polynom/polynom.h"

using namespace MonicPolynomial;

namespace FiniteField {

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

	template <class T, int modulus>
	class FieldElement {
	protected:
		T elem;

		virtual T castToFieldElement(T val) = 0;
	public:
		virtual T get() const = 0;
	};

	template<class T, int modulus>
	ostream& operator<<(ostream& o, FieldElement<T, modulus> fieldElement) {
		return (o << fieldElement.get());
	};

//	template <class T>
//	class Algebra {
//	private:
//	public:
//		virtual Algebra operator+(const Algebra& elem);
//	};

	class Algebra;
	//TODO: typedef shared_ptr<Algebra> Algebra
	class Algebra {
	public:
		//virtual Algebra operator+(const Algebra& elem) const;
		virtual int operator+(int a) = 0;
		virtual shared_ptr<Algebra> operator+(const Algebra& alg) const = 0;
	};
	class Algebra1
		: public virtual Algebra
	{
	public:
		virtual int operator+(int a) { return a++; }
		virtual shared_ptr<Algebra> operator+(const Algebra& alg) const {
			try {
				const Algebra1 &a1 = dynamic_cast<const Algebra1 &>(alg);
				return make_shared<Algebra1>();
			} catch(bad_cast exp) {
				cout << exp.what() << endl;
			}
		}
	};

	template <int modulus>
	class FieldElement<int, modulus>
			//: public Algebra
	{
		int elem;

		//TODO: you can write specialization with modulus = 2 because returning value of this function would be easier
		virtual int castToFieldElement(int val) {
			return val % modulus - ((2 * std::abs(val % modulus) <= modulus) ? 0 : sign(val) * modulus);
		}
	public:
		FieldElement() : elem(0) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}
		FieldElement(int val) : elem(castToFieldElement(val)) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}

		const FieldElement& operator=(int val) {
			elem = castToFieldElement(val);
		}

		//selectors

		FieldElement operator+(const int val) const { return FieldElement(elem + val); }
		FieldElement operator+(const FieldElement& obj) const {	return (*this) + obj.elem; }
		const FieldElement& operator+=(const int val) {
			elem = castToFieldElement(elem + val);
			return (*this);
		}
		const FieldElement& operator+=(const FieldElement& obj) { return (*this) += obj.elem; }
		FieldElement operator*(const FieldElement& obj) const {	return FieldElement(elem * obj.elem); }
		const FieldElement& operator*=(const FieldElement& obj) {
			elem = castToFieldElement(elem * obj.elem);
			return (*this);
		}
		FieldElement operator-() const { return FieldElement(-elem); }
		FieldElement operator-(const FieldElement& obj) const {	return (*this) + (-obj); }
		const FieldElement& operator-=(const FieldElement& obj) { return (*this) -= obj; }

		//division, subtraction

		bool operator!=(const FieldElement& obj) const { return (elem != obj.elem); }
		bool operator==(const FieldElement& obj) const { return !((*this) != obj); }

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
