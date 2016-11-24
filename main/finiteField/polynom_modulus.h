//
// Created by artem on 11/16/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIALMODULUS_H
#define CRYPTOGRAPHY_POLYNOMIALMODULUS_H

#include "polynom/polynom.h"

using namespace Polynomial;

namespace FiniteField {

	//maybe I need to do wrapper to interrupt producing more and more constructors

	//maybe CastToFieldElementCustomization is unnecessary?

	//template for module (characteristic) of field
	//Is modulus prime?
	template<int modulus, class T = int>			//wrapper around Polynom
	class PolynomModulus {

	public:
		enum CastToFieldElementCustomization {
			Auto,
			ByHand
		};
	private:
		Polynom<T> polynom;
		CastToFieldElementCustomization custom;

	public:

		explicit
		PolynomModulus(CastToFieldElementCustomization cust = Auto) : polynom(), custom(cust) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}

		explicit
		PolynomModulus(const vector<T> &vec, CastToFieldElementCustomization cust = Auto) : custom(cust) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();

			for (int i = 0; i < vec.size(); i++)
				polynom.push_back(ConversionToFieldElements::getFieldElement(vec[i], modulus));
		}

		explicit
		PolynomModulus(const size_t size, CastToFieldElementCustomization cust = Auto)
				: custom(cust), polynom(size) {}

		//copy constructor
		PolynomModulus(const PolynomModulus &obj) : custom(obj.custom), polynom(obj.polynom) {}

		//move constructor
		PolynomModulus(PolynomModulus<modulus, T> &&temp) : polynom(temp.polynom) {
			custom = temp.custom;
		}

		/*---------------Operators-------------*/


		const PolynomModulus &operator=(const PolynomModulus &obj) {
			if ((*this) != obj) {
				//cout << &obj.polynom[0] << " ";
				polynom = obj.polynom;
				//cout << &polynom[0] << " ";
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
				for (int i = 0; i < shortPolynom.size(); i++)
					sum[i] = ConversionToFieldElements::getFieldElement(sum[i] + shortPolynom[i], modulus);

				//the power of polynom can decrease by addition
				size_t newSize = sum.size();
				for (size_t i = sum.size() - 1; (i >= 0) && (sum[i] % modulus == 0); i--)
					--newSize;

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

		void setCustomization(const CastToFieldElementCustomization cust) { custom = cust; }

		void resize(const size_t size) { polynom.resize(size); }

		void print(ostream &o = cout, const char delimiter = ' ') const { polynom.print(o, delimiter); }


		/*---------------Friendship-----------------*/

		template<int m, class S>
		friend ostream &operator<<(ostream &o, const PolynomModulus<m, S> &p);
	};

	template<int modulus, class S>
	ostream &operator<<(ostream &o, const PolynomModulus<modulus, S> &p) {
		p.print(o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIALMODULUS_H
