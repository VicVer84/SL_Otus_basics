#pragma once

#include "IStatistics.h"

#include <algorithm>
#include <limits>
#include <vector>


class Pct95 : public IStatistics {
public:
	Pct95() : P(95){}

	void update(double next) override;

	double eval() const override;

	const char* name() const override;

private:
	int P;
	std::vector<double> v;
};