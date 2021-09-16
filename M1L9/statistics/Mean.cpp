#include "Mean.h"
#include <iostream>

void Mean::update(double next) {	
	mean = mean / (cnt+1) * cnt + next / (cnt+1);
	cnt++;
}

double Mean::eval() const {
	return mean;
}

const char * Mean::name() const {
	return "mean";
}
