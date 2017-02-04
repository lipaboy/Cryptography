//
// Created by artem on 12/8/16.
//

#ifndef CRYPTOGRAPHY_VECTOR_ARITHMETICS_H
#define CRYPTOGRAPHY_VECTOR_ARITHMETICS_H

#include <iostream>
#include <vector>



namespace VectorArithmetics {

	using namespace std;

	//no condition on sizes of vectors (they might have different ones)

	template <class T>
	vector<T> operator+ (const vector<T>& first, const vector<T>& second) {
		const vector<T> & min = ((first.size() <= second.size()) ? first : second);
		const vector<T> & max = ((first.size() > second.size()) ? first : second);
		vector<T> sum(max.size());

		for (size_t i = 0; i < min.size(); i++)
			sum[i] = first[i] + second[i];		//save commutative property
		for (size_t i = min.size(); i < max.size(); i++)
			sum[i] = max[i];

		return sum;
	}

	template <class T>
	const vector<T>& operator+= (vector<T>& first, const vector<T>& second) {
		if (first.size() < second.size())
			first.resize(second.size());
		for (size_t i = 0; i < first.size(); i++)
			first[i] += second[i];
		return first;
	}

	template <class T>
	vector<T> operator- (const vector<T>& first) {
		vector<T> inverse(first.size());
		for (size_t i = 0; i < first.size(); i++)
			inverse[i] = -first[i];
		return inverse;
	}

	template <class T>
	vector<T> operator- (const vector<T>& first, const vector<T>& second) {
		const vector<T> & min = ((first.size() <= second.size()) ? first : second);
		const vector<T> & max = ((first.size() > second.size()) ? first : second);
		vector<T> sub(max.size());

		for (size_t i = 0; i < min.size(); i++)
			sub[i] = first[i] - second[i];		//save commutative property
		if (max == first)
			for (size_t i = min.size(); i < max.size(); i++)
				sub[i] = first[i];
		else
			for (size_t i = min.size(); i < max.size(); i++)
				sub[i] = static_cast<T>(0) - second[i];

		return sub;
	}

	template <class T>
	const vector<T>& operator-= (vector<T>& first, const vector<T>& second) {
		if (first.size() < second.size())
			first.resize(second.size());
		for (size_t i = 0; i < first.size(); i++)
			first[i] -= second[i];
		return first;
	}

	//void print(const vector<int> &vec, ostream &o = cout, const char separator = ' ');

}

#endif //CRYPTOGRAPHY_VECTOR_ARITHMETICS_H
