#pragma once

#include "IStatistics.h"

#include <limits>

class Mean : public IStatistics {
public:
	Mean() : sum(0), cnt(0) {}

	void update(double next) override;

	double eval() const override;

	const char* name() const override;

private:
	double sum;
	int cnt;
};