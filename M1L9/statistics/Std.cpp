#include "Std.h"

void Std::update(double next) {
	v.push_back(next);
}

double Std::eval() const {
	double x = std::accumulate( v.begin(), v.end(), 0.0) / v.size();

	double sum = 0;
	std::for_each(v.begin(), v.end(), 
		[&sum, &x](const double& n) { 
			sum += (n - x) * (n - x); 
		}
	);
	
	return std::sqrt(sum/v.size());
}

const char * Std::name() const {
	return "Std";
}
