#include "Pct95.h"

void Pct95::update(double next) {
	v.push_back(next);
	std::sort(v.begin(), v.end());
}

double Pct95::eval() const {
	size_t size = v.size();
	size_t idxK = P * (size - 1) / 100;
	size_t idxAlphaN = P * size / 100;
	double K = v[idxK];
	double AlphaN = v[idxAlphaN];
	
	if(K + 1 < AlphaN) {
		return v[idxK + 1];
	} else if (K + 1 == AlphaN) {
		return (v[idxAlphaN] + v[idxK]) / 2;
	} else {
		return v[idxK];
	}
}

const char * Pct95::name() const {
	return "Pct95";
}
