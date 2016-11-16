//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_COMPLEX_NUMBERS_H
#define CRYPTOGRAPHY_COMPLEX_NUMBERS_H

#include <iostream>

using namespace std;

template <class T = double>
class Complex {
private:
	T real;
	T imaginary;

public:
	Complex() : real(0), imaginary(0) {}
	Complex(T re) : real(re), imaginary(0) {}
	Complex(T re, T im) : real(re), imaginary(im) {}

	Complex conjugate() const { return Complex(real, -imaginary); }

	Complex operator+(const Complex &obj) const { return Complex(real + obj.real, imaginary + obj.imaginary);	}

	Complex operator-() const { return Complex(-real, -imaginary); }

	Complex operator-(const Complex &obj) const { return Complex( (*this) + (-obj) ); }

	Complex operator*(const Complex &obj) const { return Complex(real * obj.real - imaginary * obj.imaginary,
		real * obj.imaginary + imaginary * obj.real); }

	T moduleInSquare() const { return real * real + imaginary * imaginary; }

	Complex operator/(const T &value) const { return Complex(real / value, imaginary / value); }

	Complex operator/(const Complex &obj) const { return (*this) * obj.conjugate() / obj.moduleInSquare(); }


	T getReal() const { return real; }

	T getImaginary() const { return imaginary; }

};



template <class T>
ostream &operator<< (ostream &o, Complex<T> complex)
{
	return o << '(' << complex.getReal() << ", " << complex.getImaginary() << ')';
}


#endif //CRYPTOGRAPHY_COMPLEX_NUMBERS_H
