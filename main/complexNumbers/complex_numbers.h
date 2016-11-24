//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_COMPLEX_NUMBERS_H
#define CRYPTOGRAPHY_COMPLEX_NUMBERS_H

#include <iostream>

using namespace std;

template<class T = double>
class Complex {
private:
	T real;
	T imaginary;

public:
	explicit
	Complex() : real(static_cast<T>(0)), imaginary(static_cast<T>(0)) {}

	explicit
	Complex(T re) : real(re), imaginary(static_cast<T>(0)) {}

	explicit
	Complex(T re, T im) : real(re), imaginary(im) {}

	Complex conjugate() const { return Complex(real, -imaginary); }

	Complex operator+(const Complex &obj) const { return Complex(real + obj.real, imaginary + obj.imaginary); }

	Complex operator-() const { return Complex(-real, -imaginary); }

	Complex operator-(const Complex &obj) const { return Complex((*this) + (-obj)); }

	Complex operator*(const Complex &obj) const {
		return Complex(real * obj.real - imaginary * obj.imaginary,
					   real * obj.imaginary + imaginary * obj.real);
	}

	T moduleInSquare() const { return real * real + imaginary * imaginary; }

	Complex operator/(const T &value) const { return Complex(real / value, imaginary / value); }

	Complex operator/(const Complex &obj) const { return (*this) * obj.conjugate() / obj.moduleInSquare(); }

	//bad for double
	bool operator==(const Complex &obj) const {
		return (real == obj.real && imaginary == obj.imaginary);
	}

	bool operator!=(const Complex &obj) const {
		return !((*this) == obj);
	}


	T getReal() const { return real; }

	T getImaginary() const { return imaginary; }

	enum NumberRepresentation {
		Algebraic,
		Geometric
	};

	//bad for type "double"
	void print(ostream &o, NumberRepresentation type) const {
		switch (type) {
			case Geometric:
				o << '(' << real << ", " << imaginary << ')';
				break;
			case Algebraic:
				if (imaginary == static_cast<T>(0))
					o << real;
				else if (real == static_cast<T>(0))
					o << imaginary << 'i';
				else
					o << "(" << real << " + " << imaginary << 'i' << ")";
				break;
		}
	}
};

template<class T>
ostream &operator<<(ostream &o, Complex<T> complex) {
	complex.print(o, Complex<T>::NumberRepresentation::Algebraic);
	return o;
}

#endif //CRYPTOGRAPHY_COMPLEX_NUMBERS_H
