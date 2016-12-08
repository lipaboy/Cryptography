//
// Created by artem on 11/16/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIALMODULUS_H
#define CRYPTOGRAPHY_POLYNOMIALMODULUS_H

#include "polynom/polynom.h"

using namespace Polynomial;

namespace FiniteField {

	//maybe I need to do wrapper to interrupt producing more and more constructors

	//maybe CastCustom is unnecessary?

	//template for module (characteristic) of field
	//Is modulus prime?
	template<int modulus, class T = int>			//wrapper around Polynom
	class PolynomModulus {

	public:
		enum CastCustom {		//customization of casting to field elements
			Auto,
			ByHand
		};
	private:
		Polynom<T> polynom;
		CastCustom custom;

	public:

		PolynomModulus(CastCustom cust = Auto) : polynom(), custom(cust) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}

		PolynomModulus(const vector<T> &vec, CastCustom cust = Auto) : custom(cust) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();

			for (int i = 0; i < vec.size(); i++)
				polynom.push_back(ConversionToFieldElements::getFieldElement(vec[i], modulus));
		}

		PolynomModulus(const size_t size, CastCustom cust = Auto)
				: custom(cust), polynom(size) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}

		//copy constructor
		PolynomModulus(const PolynomModulus &obj) : custom(obj.custom), polynom(obj.polynom) {}

		//move constructor
		PolynomModulus(PolynomModulus<modulus, T> &&temp) : polynom(temp.polynom) {
			custom = temp.custom;
		}

		/*---------------Operators-------------*/


		const PolynomModulus &operator=(const PolynomModulus &obj) {
			if ((*this) != obj) {
				polynom = obj.polynom;
				custom = obj.custom;
			}
			return (*this);
		}

		PolynomModulus operator+(const PolynomModulus &obj) const {
			const PolynomModulus &longPolynom = (size() > obj.size()) ? (*this) : obj;
			const PolynomModulus &shortPolynom = (size() <= obj.size()) ? (*this) : obj;
			PolynomModulus sum(longPolynom);

			if (custom == ByHand)
				sum.polynom += shortPolynom.polynom;
			else {
				//the power of polynom can decrease by addition
				size_t newSize = sum.size();
				bool isCanResize = true;
				for (size_t i = sum.size() - 1; i >= 0; i--) {
					sum.polynom[i] = ConversionToFieldElements::getFieldElement(sum.polynom[i], modulus);
					if (sum.polynom[i] != 0)
						isCanResize = false;
					if (isCanResize)
						--newSize;
				}

				sum.resize(newSize);
			}

			return sum;
		};

		PolynomModulus operator-() const {        //I don't know cast To Field Elements or not
			PolynomModulus inverse(size());

			if (custom == ByHand)
				inverse.polynom = -polynom;
			else
				for (int i = 0; i < size(); i++)
					inverse[i] = ConversionToFieldElements::getFieldElement(-polynom[i], modulus);

			return inverse;
		}

		PolynomModulus operator-(const PolynomModulus &obj) const { return (*this) + (-obj); }

		PolynomModulus operator*(const PolynomModulus &obj) const {
			PolynomModulus mul((size() - 1) + (obj.size() - 1) + 1);

			for (int i = 0; i < size(); i++)
				for (int j = 0; j < obj.size(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			if (custom == Auto)
				mul.castToFieldElems();

			return mul;
		}

		const T &operator[](const int i) const {
			return polynom[i];
		}

		//code duplication - bad!!!
		T &operator[](const int i) {
			return polynom[i];
		}

		bool operator==(const PolynomModulus &obj) const {
			if (size() != obj.size())
				return false;

			for (int i = 0; i < size(); i++)
				if (static_cast<T>(0) != ConversionToFieldElements::getFieldElement(polynom[i] - obj[i], modulus))
					return false;
			return true;
		}

		bool operator!=(const PolynomModulus &obj) const {
			return (!((*this) == obj));
		}


		void castToFieldElems() {
			for (int i = 0; i < size(); i++)
				polynom[i] = ConversionToFieldElements::getFieldElement(polynom[i], modulus);
		}

		void push_back(T elem) { polynom.push_back(getFieldElement(elem, modulus)); }

		const size_t size() const { return polynom.size(); }

		void setCustomization(const CastCustom cust) { custom = cust; }

		void resize(const size_t size) { polynom.resize(size); }

		void print(ostream &o = cout, const char delimiter = ' ') const { printAlgebricForm(polynom, o, delimiter); }


		/*---------------Friendship-----------------*/

	};

	template<int modulus, class S>
	ostream &operator<<(ostream &o, const PolynomModulus<modulus, S> &p) {
		p.print(o);
		return o;
	}

	template <int modulus>
	class ElementInt {
	private:
		int elem;
	public:
		ElementInt(int val) : elem(getFieldElement(val)) {}

		ElementInt operator+(const ElementInt& obj) {
			return ElementInt(elem + obj.elem);
		}

		int getFieldElement(int val) {
			if (modulus == 2)
				return abs(val % modulus);
			return val % modulus - ((2 * std::abs(val % modulus) <= modulus) ? 0 : sign(val) * modulus);
		}

		int get() const {}

	};
}




#endif //CRYPTOGRAPHY_POLYNOMIALMODULUS_H
