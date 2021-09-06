#pragma once

#include "IStatistics.h"

#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

class Std : public IStatistics {
public:
	Std(){}

	void update(double next) override;

	double eval() const override;

	const char* name() const override;

private:
	std::vector<double> v;
};