#pragma once

#include "IStatistics.h"

#include <limits>

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {}

	void update(double next) override;

	double eval() const override;

	const char* name() const override;

private:
	double m_max;
};