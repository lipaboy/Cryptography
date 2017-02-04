//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIAL_H
#define CRYPTOGRAPHY_POLYNOMIAL_H

#include <vector>
#include <iostream>
#include "vectorExtraFuncs/VectorArithmetics.h"

namespace MonicPolynomial {

	class PolynomialException : public std::logic_error {
	public:
		explicit
		PolynomialException(std::string &&str) : logic_error("MonicPolynomial error: " + str) {}
	};

	class WrongResizeParameterException : public PolynomialException {
	public:
		explicit
		WrongResizeParameterException() : PolynomialException("resize parameter must be positive") {}
	};

	class NegativeDegreeValueException : public PolynomialException {
	public:
		explicit
		NegativeDegreeValueException() : PolynomialException("highestDegree cannot be negative") {}
	};

	//BAD 1: When I modify class Polynom<t> I always need to remember that size = highestDegree + 1
	//BAD 2: may be to many methods. Think about Collections in Java
	template <class T>
	class Polynom {
	protected:
		std::vector<T> polynom;
		const T ZERO_ELEMENT = static_cast<T>(0);
		/*
		 //I don't sure whether this method justify itself or not
		void removeZeroElements() {
			size_t newSize = highestDegree();
			for (size_t i = highestDegree() - 1; (i > 0) && ((*this)[i] == ZERO_ELEMENT); i--)
				--newSize;

			resize(newSize);
		}*/
	public:
				//one element must be in Polynom
		Polynom(){ polynom.push_back(ZERO_ELEMENT); }

		Polynom(const std::vector<T> &vec) : polynom(vec) {  }
		//TODO: I will interest by move-and-swap idiom
		Polynom(std::vector<T> &&vec) { std::swap(vec, polynom);  }

		Polynom(const Polynom &obj) : polynom(obj.polynom) {}

		/*---------------Operators-------------*/

		virtual const Polynom& operator= (const Polynom &obj) {
			if ((*this) != obj)
				polynom = obj.polynom;
			return (*this);
		}

		virtual Polynom operator+ (const Polynom &obj) const;

		virtual const Polynom& operator+= (const Polynom &obj) {
			polynom += obj.polynom;
			return (*this);
		}

		virtual Polynom operator- () const { return Polynom(-polynom); }

		virtual Polynom operator- (const Polynom &obj) const { return Polynom(polynom - obj.polynom); }

		virtual const Polynom& operator-= (const Polynom &obj) {
			polynom -= obj.polynom;
			return (*this);
		}

		virtual Polynom operator* (const Polynom &obj) const {
//			Polynom mul((highestDegree() - 1) + (obj.highestDegree() - 1) + 1);
			Polynom mul;

			for (int i = 0; i < highestDegree(); i++)
				for (int j = 0; j < obj.highestDegree(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			return mul;
		}

		//TODO: you can rewrite it for example: "copy-paste" code from operator* if you don't want to do
		//TODO: extra allocating memory and copying
		virtual const Polynom& operator*= (const Polynom &obj) { return ((*this) = ((*this) * obj)); }

				//code duplication - bad!!! (or not?)
		virtual T &operator[](const int degree) { return polynom[degree]; }

		virtual void set(int degree, int coefficient);

		virtual void push(int coefficient) { set(1 + highestDegree(), coefficient); }

		//-----------------------------Select methods-----------------------------------------------

		//we cannot get address from element monicPolynomial[i] because returning value is rvalue - nonsense
		virtual const T& operator[](const int degree) const { return polynom[degree]; }

		virtual bool operator==(const Polynom &obj) const;

		virtual bool operator!=(const Polynom &obj) const { return (!((*this) == obj)); }

		//size cannot be zero
		virtual const int highestDegree() const { return static_cast<int>(polynom.size() - 1); }

	};

	template <class T>
	void Polynom<T>::set(int degree, int coefficient) {
		if (degree > highestDegree())
			polynom.resize(static_cast<size_t>(degree + 1));
		polynom[degree] = coefficient;
	}

	template <class T>
	Polynom<T> Polynom<T>::operator+ (const Polynom &obj) const {
		Polynom sum;
		sum.polynom.resize(static_cast<size_t>(1 + (highestDegree() > obj.highestDegree())
											   ? highestDegree() : obj.highestDegree()));

		sum.polynom = polynom + obj.polynom;
		//the power of monicPolynomial can decrease by addition
		//sum.removeZeroElements();
		return sum;
	}

	template <class T>
	bool Polynom<T>::operator==(const Polynom &obj) const {
		if (highestDegree() != obj.highestDegree())
			return false;

		for (int i = 0; i <= highestDegree(); i++)
			if (ZERO_ELEMENT != (*this)[i] - obj[i])
				return false;
		return true;
	}

	//I need different representations of monicPolynomial
	template <class T>
	void printAlgebricForm(const Polynom<T>& polynom, std::ostream &o = std::cout, const char delimiter = ' ') {
		if (polynom.highestDegree() > 0)
			o << "(";

		for (int i = 0; i <= polynom.highestDegree(); i++)	{
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

		if (polynom.highestDegree() > 0)
			o << ")";
	}

	template <class S>
	std::ostream &operator<< (std::ostream &o, const Polynom<S> &p){
		printAlgebricForm(p, o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIAL_H
