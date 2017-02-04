//
// Created by artem on 8/9/16.
//

#ifndef CRYPTOGRAPHY_IOVECTOR_H
#define CRYPTOGRAPHY_IOVECTOR_H

#include <iostream>
#include <vector>


namespace OutputVector {

	//using namespace std;

	template <class T>
	void print(const std::vector<T> &vec, std::ostream &o = std::cout, const char separator = ' ') {
		for (int i = 0; i < vec.size(); i++)
			o << vec[i] << separator;
	}

	template <class T>
	std::ostream &operator<< (std::ostream &o, const std::vector<T> &vec){
		print(vec, o);
		return o;
	}

}

#endif //CRYPTOGRAPHY_IOVECTOR_H
