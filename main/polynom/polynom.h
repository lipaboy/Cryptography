//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIAL_H
#define CRYPTOGRAPHY_POLYNOMIAL_H

#include <vector>
#include <iostream>
#include "vector_extra/vector_arithmetics.h"

using namespace VectorArithmetics;

namespace Polynomial {

	class WrongResizeParameterException : public logic_error {
	public:
		explicit
		WrongResizeParameterException() : logic_error("Polynomial error: resize parameter must be positive.") {}
	};

	template <class T>
	class Polynom {
	protected:
		vector<T> polynom;
		const T ZERO_ELEMENT = static_cast<T>(0);

		//I don't sure whether this method justify itself or not
//		void removeZeroElements() {
//			size_t newSize = degree();
//			for (size_t i = degree() - 1; (i > 0) && ((*this)[i] == ZERO_ELEMENT); i--)
//				--newSize;
//
//			resize(newSize);
//		}

	public:
				//one element must be in Polynom
		Polynom(){ polynom.push_back(ZERO_ELEMENT); }

		Polynom(const vector<T> &vec) : polynom(vec) {  }

		Polynom(vector<T> &&vec) { std::swap(vec, polynom);  }

		Polynom(const size_t size) : polynom(size) {}
		//copy constructor
		Polynom(const Polynom &obj) : polynom(obj.polynom) {}
		//move constructor
		/*Polynom(Polynom &&temp) : Polynom() {
			swap(*this, temp);
			std::cout << "bad move" << endl;
		}*/

		/*---------------Operators-------------*/

//why cannot do it?			- 	because such occasion cannot happen
		/*const Polynom& operator= (Polynom &&temp) {
			if ((*this) != temp) {
				cout << &temp.polynom[0] << " ";
				this->move(temp);
				cout << &polynom[0] << " ";
				//custom = temp.custom;
			}
			return (*this);
		}*/

		virtual const Polynom& operator= (const Polynom &obj) {
			if ((*this) != obj)
				polynom = obj.polynom;
			return (*this);
		}

		/*const Polynom& operator= (Polynom &&obj) {
			swap(*this, obj);
			std::cout << "bad move" << endl;
			//(*this).polynom = obj.polynom;
			return (*this);
		}*/

		virtual Polynom operator+ (const Polynom &obj) const {
			Polynom sum((degree() > obj.degree()) ? degree() : obj.degree());

			sum.polynom = polynom + obj.polynom;
			//the power of polynom can decrease by addition
			//sum.removeZeroElements();
			return sum;
		}

		virtual const Polynom& operator+= (const Polynom &obj) {
			polynom += obj.polynom;
			return (*this);
		}

		virtual Polynom operator- () const {
			return Polynom(-polynom);
		}

		virtual Polynom operator- (const Polynom &obj) const { return Polynom(polynom - obj.polynom); }

		virtual Polynom operator* (const Polynom &obj) const {
			Polynom mul((degree() - 1) + (obj.degree() - 1) + 1);

			for (int i = 0; i < degree(); i++)
				for (int j = 0; j < obj.degree(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			return mul;
		}

		virtual const Polynom& operator*= (const Polynom &obj) { return ((*this) = ((*this) * obj)); }

		const T &operator[](const int i) const {
			if (i < 0 || i >= polynom.size())
				throw out_of_range("Polynom Exception: out of range");
			return polynom[i];
		}
				//code duplication - bad!!!
		T &operator[](const int i) {
			if (i < 0 || i >= polynom.size())
				throw out_of_range("Polynom Exception: out of range");
			return polynom[i];
		}

		virtual bool operator==(const Polynom &obj) const {
			if (degree() != obj.degree())
				return false;

			for (int i = 0; i < degree(); i++)
				if (ZERO_ELEMENT != polynom[i] - obj[i])
					return false;
			return true;
		}

		virtual bool operator!=(const Polynom &obj) const {
			return (!((*this) == obj));
		}

		void push_back(T elem) { if (elem != ZERO_ELEMENT) polynom.push_back(elem); }

		const size_t degree() const { return polynom.size(); }

		void resize(const size_t size) throw(WrongResizeParameterException);

	};

	template<class T>
	void Polynom<T>::resize(const size_t size) throw(WrongResizeParameterException) {
		if (size < 1)
			throw WrongResizeParameterException();
		polynom.resize(size);
	}

	//I need different representations of polynom
	template <class T>
	void printAlgebricForm(const Polynom<T>& polynom, ostream &o = cout, const char delimiter = ' ') {
		if (polynom.degree() > 1)
			cout << "(";

		for (int i = 0; i < polynom.degree(); i++)	{
			if (i == 0)
				o << polynom[i];
			else if (polynom[i] != static_cast<T>(0)) {
				o << delimiter << "+" << delimiter;
				if (polynom[i] != static_cast<T>(1))
					o << polynom[i];
				o << "x";
				if (i != 1)
					o << "^" << i;
			}
		}

		if (polynom.degree() > 1)
			cout << ")";
	}

	template <class S>
	ostream &operator<< (ostream &o, const Polynom<S> &p){
		printAlgebricForm(p, o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIAL_H
