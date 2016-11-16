#include "crypto.h"

ostream & operator<< (ostream &o, const vector<int> &vec) {
	const size_t & size = vec.size();
	for (int i = 0; i < size; i++)
		o << vec[i] << " ";
	return o;
}

vector<int> operator- (const vector<int> vec1, const vector<int> vec2) {
	const size_t size = (vec1.size() < vec2.size()) ? vec1.size() : vec2.size();
	vector<int> res;

	for (int i = 0; i < size; i++)
		res.push_back(vec1[i] - vec2[i]);

	return res;
}

