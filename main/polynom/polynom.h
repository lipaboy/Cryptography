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
//			size_t newSize = size();
//			for (size_t i = size() - 1; (i > 0) && ((*this)[i] == ZERO_ELEMENT); i--)
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

		const Polynom& operator= (const Polynom &obj) {
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

		Polynom operator+ (const Polynom &obj) const {
			Polynom sum((size() > obj.size()) ? size() : obj.size());

			sum.polynom = polynom + obj.polynom;
			//the power of polynom can decrease by addition
			//sum.removeZeroElements();
			return sum;
		}

		const Polynom& operator+= (const Polynom &obj) {
			polynom += obj.polynom;
			return (*this);
		}

		Polynom operator- () const {
			return Polynom(-polynom);
		}

		Polynom operator- (const Polynom &obj) const { return Polynom(polynom - obj.polynom); }

		Polynom operator* (const Polynom &obj) const {
			Polynom mul((size() - 1) + (obj.size() - 1) + 1);

			for (int i = 0; i < size(); i++)
				for (int j = 0; j < obj.size(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			return mul;
		}

		const Polynom& operator*= (const Polynom &obj) { return ((*this) = ((*this) * obj)); }

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

		bool operator==(const Polynom &obj) const {
			if (size() != obj.size())
				return false;

			for (int i = 0; i < size(); i++)
				if (ZERO_ELEMENT != polynom[i] - obj[i])
					return false;
			return true;
		}

		bool operator!=(const Polynom &obj) const {
			return (!((*this) == obj));
		}

		void push_back(T elem) { if (elem != ZERO_ELEMENT) polynom.push_back(elem); }

		const size_t size() const { return polynom.size(); }

		void resize(const size_t size) throw(WrongResizeParameterException) {
			if (size < 1)
				throw WrongResizeParameterException();
			polynom.resize(size);
		}

		//		Friendship		//
		/*template<class S>
		friend void swap(Polynom<S>& first, Polynom<S>& second){
			std::swap(first.polynom, second.polynom);
			std::cout << "move swap" << endl;
		}*/

	};

	//I need different representations of polynom
	template <class T>
	void printAlgebricForm(const Polynom<T>& polynom, ostream &o = cout, const char delimiter = ' ') {
		if (polynom.size() > 1)
			cout << "(";

		for (int i = 0; i < polynom.size(); i++)	{
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

		if (polynom.size() > 1)
			cout << ")";
	}

	template <class S>
	ostream &operator<< (ostream &o, const Polynom<S> &p){
		printAlgebricForm(p, o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIAL_H
