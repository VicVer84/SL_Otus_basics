#include "Mean.h"

void Mean::update(double next) {
	sum += next;
	cnt++;
}

double Mean::eval() const {
	return sum / cnt;
}

const char * Mean::name() const {
	return "mean";
}
