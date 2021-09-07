#pragma once

#include "IStatistics.h"

#include <algorithm>
#include <limits>
#include <vector>


class Pct90 : public IStatistics {
public:
	Pct90() : P(90){}

	void update(double next) override;

	double eval() const override;

	const char* name() const override;

private:
	int P;
	std::vector<double> v;
};