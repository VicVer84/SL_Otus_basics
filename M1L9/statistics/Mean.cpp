#include "Mean.h"

void Mean::update(double next) {
	sum += next;
	cnt++;
}

double Mean::eval() const {
	if(cnt > 0) {
		return sum / cnt;
	} else {
		return 0;
	}
}

const char * Mean::name() const {
	return "mean";
}
