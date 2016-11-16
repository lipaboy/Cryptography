//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_POLYNOMIAL_H
#define CRYPTOGRAPHY_POLYNOMIAL_H

#include <vector>
#include <iostream>

namespace CryptographyMath {

	//----------------Too many memory copying-----------------------Unique_ptr--//

	template <class T>
	class Polynomial {

	private:
		vector<T> polynom;

	public:
		void move(Polynomial &&temp) {
			polynom = move(temp.polynom);
		}

		explicit
		Polynomial(){
			polynom.push_back(0);
		}

		explicit
		Polynomial(const vector<T> &vec) {

			for (int i = 0; i < vec.size(); i++)
				polynom.push_back(vec[i]);
		}

		explicit
		Polynomial(const size_t size) : polynom(size) {}
		//copy constructor
		Polynomial(const Polynomial &obj) : polynom(obj.polynom) {}
		//move constructor
		Polynomial(Polynomial &&temp) { this->move(temp); }

		/*---------------Operators-------------*/

//why cannot do it?
		/*const Polynomial& operator= (Polynomial &&temp) {
			if ((*this) != temp) {
				cout << &temp.polynom[0] << " ";
				this->move(temp);
				cout << &polynom[0] << " ";
				//custom = temp.custom;
			}
			return (*this);
		}*/

		const Polynomial& operator= (const Polynomial &obj) {
			if ((*this) != obj) {
				cout << &obj.polynom[0] << " ";
				polynom = obj.polynom;
				cout << &polynom[0] << " ";
			}
			return (*this);
		}

		Polynomial operator+ (const Polynomial &obj) const {
			const Polynomial &longPolynom = (size() > obj.size()) ? (*this) : obj;
			const Polynomial &shortPolynom = (size() <= obj.size()) ? (*this) : obj;
			Polynomial sum(longPolynom);

			for (int i = 0; i < shortPolynom.size(); i++)
				sum[i] += shortPolynom[i];

							//the power of polynom can decrease by addition
			size_t newSize = sum.size();
			for (size_t i = sum.size() - 1; (i >= 0) && (sum[i] == 0); i--)
				--newSize;

			sum.resize(newSize);

			return sum;
		};

		const Polynomial& operator+= (const Polynomial &obj) { return ((*this) = ((*this) + obj)); }

		Polynomial operator- () const {
			Polynomial inverse(size());

			for (int i = 0; i < size(); i++)
				inverse[i] = -polynom[i];

			return inverse;
		}

		Polynomial operator- (const Polynomial &obj) const { return (*this) + (-obj); }

		Polynomial operator* (const Polynomial &obj) const {
			Polynomial mul((size() - 1) + (obj.size() - 1) + 1);

			for (int i = 0; i < size(); i++)
				for (int j = 0; j < obj.size(); j++)
					mul[i + j] += (*this)[i] * obj[j];

			return mul;
		}

		const Polynomial& operator*= (const Polynomial &obj) { return ((*this) = ((*this) * obj)); }

		const T &operator[](const int i) const {
			if (i < 0 || i >= polynom.size())
				throw out_of_range("Polynomial Exception: out of range");
			return polynom[i];
		}
				//code duplication - bad!!!
		T &operator[](const int i) {
			if (i < 0 || i >= polynom.size())
				throw out_of_range("Polynomial Exception: out of range");
			return polynom[i];
		}

		bool operator==(const Polynomial &obj) const {
			if (size() != obj.size())
				return false;

			for (int i = 0; i < size(); i++)
				if (static_cast<T>(0) != polynom[i] - obj[i])
					return false;
			return true;
		}

		bool operator!=(const Polynomial &obj) const {
			return (!((*this) == obj));
		}

		void push_back(T elem) { polynom.push_back(elem); }

		const size_t size() const { return polynom.size(); }

		void resize(const size_t size) { polynom.resize(size); }

		//I need different representaions of polynom
		void print(ostream &o = cout, const char delimiter = ' ') const {
			//OutputVector::print(polynom, o, separator);

			if (size() > 1)
				cout << "(";

			for (int i = 0; i < size(); i++)	{
				if (i == 0)
					o << polynom[i];
				else if (polynom[i] != 0) {
					o << delimiter << "+" << delimiter;
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

		template<class S>
		friend ostream &operator<< (ostream &o, const Polynomial<S> &p);
	};

	template <class S>
	ostream &operator<< (ostream &o, const Polynomial<S> &p){
		p.print(o);
		return o;
	}
}

#endif //CRYPTOGRAPHY_POLYNOMIAL_H
