//
// Created by artem on 11/16/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIALMODULUS_H
#define CRYPTOGRAPHY_POLYNOMIALMODULUS_H

#include "polynom/polynomial.h"

namespace FiniteField {

	//template for module (characteristic) of field
	template<int modulus>
	class Polynomial : public Polynomial {

	public:
		enum Customization {
			AutoCastToFieldElements,
			CastToFieldElementsByHand
		};
	private:
		vector<T> polynom;
		Customization custom;

	public:
		void move(Polynomial &&temp) {
			polynom = move(temp.polynom);
			custom = temp.custom;
		}

		explicit
		Polynomial(Customization cust = AutoCastToFieldElements) : custom(cust) {
			if (modulus< 2)
			throw WrongTemplateParameterValueException();

			polynom.push_back(0);
		}

		explicit
		Polynomial(const vector<T> &vec, Customization cust = AutoCastToFieldElements) : custom(cust) {
			if (modulus< 2)
			throw WrongTemplateParameterValueException();

			for (int i = 0; i < vec.size(); i++)
				polynom.push_back(ConversionToFieldElements::getFieldElement(vec[i], modulus));
		}

		explicit
		Polynomial(const size_t size, Customization cust = AutoCastToFieldElements)
				: custom(cust), polynom(size) {}

		//copy constructor
		Polynomial(const Polynomial &obj) : custom(obj.custom), polynom(obj.polynom) {}

		//move constructor
		Polynomial(Polynomial &&temp) { this->move(temp); }

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

		const Polynomial &operator=(const Polynomial &obj) {
			if ((*this) != obj) {
				cout << &obj.polynom[0] << " ";
				polynom = obj.polynom;
				cout << &polynom[0] << " ";
				custom = obj.custom;
			}
			return (*this);
		}

		Polynomial operator+(const Polynomial &obj) const {
			const Polynomial &longPolynom = (size() > obj.size()) ? (*this) : obj;
			const Polynomial &shortPolynom = (size() <= obj.size()) ? (*this) : obj;
			Polynomial sum(longPolynom);

			if (custom == AutoCastToFieldElements)
				for (int i = 0; i < shortPolynom.size(); i++)
					sum[i] = ConversionToFieldElements::getFieldElement(sum[i] + shortPolynom[i], modulus);
			else
				for (int i = 0; i < shortPolynom.size(); i++)
					sum[i] += shortPolynom[i];

			//the power of polynom can decrease by addition
			size_t newSize = sum.size();
			for (size_t i = sum.size() - 1; (i >= 0) && (sum[i] % modulus == 0); i--)
				--newSize;

			sum.resize(newSize);

			return sum;
		};

		Polynomial operator-() const {        //I don't know cast To Field Elements or not
			Polynomial inverse(size());

			for (int i = 0; i < size(); i++)
				inverse[i] = -polynom[i];

			return inverse;
		}

		Polynomial operator-(const Polynomial &obj) const { return (*this) + (-obj); }

		Polynomial operator*(const Polynomial &obj) const {
			Polynomial mul((size() - 1) + (obj.size() - 1) + 1);

			for (int i = 0; i < size(); i++)
				for (int j = 0; j < obj.size(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			if (custom == AutoCastToFieldElements)
				mul.castToFieldElems();

			return mul;
		}

		const T &operator[](const int i) const {
			if (i < 0 || i >= polynom.size())
				throw out_of_range("Polynomial Exception: out of range");
			return polynom[i];
		}

		//double code - bad!!!
		T &operator[](const int i) {
			if (i < 0 || i >= polynom.size())
				throw out_of_range("Polynomial Exception: out of range");
			return polynom[i];
		}

		bool operator==(const Polynomial &obj) const {
			if (size() != obj.size())
				return false;

			for (int i = 0; i < size(); i++)
				if (static_cast<T>(0) != ConversionToFieldElements::getFieldElement(polynom[i] - obj[i], modulus))
					return false;
			return true;
		}

		bool operator!=(const Polynomial &obj) const {
			return (!((*this) == obj));
		}


		void castToFieldElems() {
			for (int i = 0; i < size(); i++)
				polynom[i] = ConversionToFieldElements::getFieldElement(polynom[i], modulus);
		}

		void push_back(T elem) { polynom.push_back(ConversionToFieldElements::getFieldElement(elem, modulus)); }

		const size_t size() const { return polynom.size(); }

		void changeCustom(const Customization cust) { custom = cust; }

		void resize(const size_t size) { polynom.resize(size); }

		void print(ostream &o = cout, const char separator = ' ') const {
			//OutputVector::print(polynom, o, separator);

			if (size() > 1)
				cout << "(";

			for (int i = 0; i < size(); i++) {
				if (i == 0)
					o << polynom[i];
				else if (polynom[i] != 0) {
					o << separator << "+" << separator;
					if (polynom[i] != 1)
						o << polynom[i];
					o << "x";
					if (i != 1)
						o << "^" << i;
				}
			}

			if (size() > 1)
				cout << ")";
		}


		/*---------------Friendship-----------------*/

		template<int m, class S>
		friend ostream &operator<<(ostream &o, const Polynomial<m, S> &p);
	};

	template<int modulus, class S>
	ostream &operator<<(ostream &o, const Polynomial<modulus, S> &p) {
		p.print(o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIALMODULUS_H
