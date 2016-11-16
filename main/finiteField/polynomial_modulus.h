//
// Created by artem on 11/16/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIALMODULUS_H
#define CRYPTOGRAPHY_POLYNOMIALMODULUS_H

#include "polynom/polynomial.h"
#include "polynomial_mod_2.h"

using namespace CryptographyMath;

namespace FiniteField {

	//maybe I need to do wrapper to interrupt producing more and more constructors

	//maybe Customization is unnecessary?

	//template for module (characteristic) of field
	//Is modulus prime?
	template<int modulus, class T = int>			//wrapper around Polynomial
	class PolynomialModulus {

	public:
		enum Customization {
			AutoCastToFieldElements,
			CastToFieldElementsByHand
		};
	private:
		Polynomial<T> polynom;
		Customization custom;

	public:

		explicit
		PolynomialModulus(Customization cust = AutoCastToFieldElements) : polynom(), custom(cust) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();
		}

		explicit
		PolynomialModulus(const vector<T> &vec, Customization cust = AutoCastToFieldElements) : custom(cust) {
			if (modulus < 2)
				throw WrongTemplateParameterValueException();

			for (int i = 0; i < vec.size(); i++)
				polynom.push_back(ConversionToFieldElements::getFieldElement(vec[i], modulus));
		}

		explicit
		PolynomialModulus(const size_t size, Customization cust = AutoCastToFieldElements)
				: custom(cust), polynom(size) {}

		//copy constructor
		PolynomialModulus(const PolynomialModulus &obj) : custom(obj.custom), polynom(obj.polynom) {}

		//move constructor
		//PolynomialModulus(PolynomialModulus<modulus, T> &&temp) { this->polynom.move(temp.polynom); }

		/*---------------Operators-------------*/


		/*const Polynomial& operator= (Polynomial &&temp) {
			if ((*this) != temp) {
				cout << &temp.polynom[0] << " ";
				this->move(temp);
				cout << &polynom[0] << " ";
				//custom = temp.custom;
			}
			return (*this);
		}*/

		const PolynomialModulus &operator=(const PolynomialModulus &obj) {
			if ((*this) != obj) {
				//cout << &obj.polynom[0] << " ";
				polynom = obj.polynom;
				//cout << &polynom[0] << " ";
				custom = obj.custom;
			}
			return (*this);
		}

		PolynomialModulus operator+(const PolynomialModulus &obj) const {
			const PolynomialModulus &longPolynom = (size() > obj.size()) ? (*this) : obj;
			const PolynomialModulus &shortPolynom = (size() <= obj.size()) ? (*this) : obj;
			PolynomialModulus sum(longPolynom);

			if (custom == CastToFieldElementsByHand)
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

		PolynomialModulus operator-() const {        //I don't know cast To Field Elements or not
			PolynomialModulus inverse(size());

			if (custom == CastToFieldElementsByHand)
				inverse.polynom = -polynom;
			else
				for (int i = 0; i < size(); i++)
					inverse[i] = ConversionToFieldElements::getFieldElement(-polynom[i], modulus);

			return inverse;
		}

		PolynomialModulus operator-(const PolynomialModulus &obj) const { return (*this) + (-obj); }

		PolynomialModulus operator*(const PolynomialModulus &obj) const {
			PolynomialModulus mul((size() - 1) + (obj.size() - 1) + 1);

			for (int i = 0; i < size(); i++)
				for (int j = 0; j < obj.size(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			if (custom == AutoCastToFieldElements)
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

		bool operator==(const PolynomialModulus &obj) const {
			if (size() != obj.size())
				return false;

			for (int i = 0; i < size(); i++)
				if (static_cast<T>(0) != ConversionToFieldElements::getFieldElement(polynom[i] - obj[i], modulus))
					return false;
			return true;
		}

		bool operator!=(const PolynomialModulus &obj) const {
			return (!((*this) == obj));
		}


		void castToFieldElems() {
			for (int i = 0; i < size(); i++)
				polynom[i] = ConversionToFieldElements::getFieldElement(polynom[i], modulus);
		}

		void push_back(T elem) { polynom.push_back(ConversionToFieldElements::getFieldElement(elem, modulus)); }

		const size_t size() const { return polynom.size(); }

		void setCustomization(const Customization cust) { custom = cust; }

		void resize(const size_t size) { polynom.resize(size); }

		void print(ostream &o = cout, const char delimiter = ' ') const { polynom.print(o, delimiter); }


		/*---------------Friendship-----------------*/

		template<int m, class S>
		friend ostream &operator<<(ostream &o, const PolynomialModulus<m, S> &p);
	};

	template<int modulus, class S>
	ostream &operator<<(ostream &o, const PolynomialModulus<modulus, S> &p) {
		p.print(o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIALMODULUS_H
