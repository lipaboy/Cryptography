//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_IOVECTOR_H
#define CRYPTOGRAPHY_IOVECTOR_H

#include <iostream>
#include <vector>

using namespace std;

namespace OutputVector {

	template <class T>
	void print(const vector<T> &vec, ostream &o = cout, const char separator = ' ') {
		for (int i = 0; i < vec.size(); i++)
			o << vec[i] << separator;
	}

	template <class T>
	ostream &operator<< (ostream &o, const vector<T> &vec){
		print(vec, o);
		return o;
	}

}

#endif //CRYPTOGRAPHY_IOVECTOR_H
