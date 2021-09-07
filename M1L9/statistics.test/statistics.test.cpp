#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

#include "IStatistics.h"
#include "Min.h"
#include "Max.h"
#include "Mean.h"
#include "Std.h"
#include "Pct90.h"
#include "Pct95.h"

TEST(statistics, Min) {
	const size_t expected = 0;
	IStatistics *stat = new Min();
	
	for(int i = 0; i <= 10; ++i) {
		stat->update(i);
	}
	ASSERT_EQ(stat->eval(), expected);
}

TEST(statistics, Max) {
	const size_t expected = 10;
	IStatistics *stat = new Max();
	
	for(int i = 0; i <= 10; ++i) {
		stat->update(i);
	}
	ASSERT_EQ(stat->eval(), expected);
}

TEST(statistics, Mean) {
	const size_t expected = 5;
	IStatistics *stat = new Mean();
	
	for(int i = 0; i <= 10; ++i) {
		stat->update(i);
	}
	ASSERT_EQ(stat->eval(), expected);
}

TEST(statistics, Std) {
	const double expected = 3.16228;
	IStatistics *stat = new Std();
	
	for(int i = 0; i <= 10; ++i) {
		stat->update(i);
	}
	ASSERT_DOUBLE_EQ(round(stat->eval() * 100000)/100000, expected);
}

TEST(statistics, Pct90) {
	const size_t expected = 9;
	IStatistics *stat = new Pct90();
	
	for(int i = 0; i <= 10; ++i) {
		stat->update(i);
	}
	ASSERT_EQ(stat->eval(), expected);
}

TEST(statistics, Pct95) {
	const double expected = 9.5;
	IStatistics *stat = new Pct95();
	
	for(int i = 0; i <= 10; ++i) {
		stat->update(i);
	}
	ASSERT_DOUBLE_EQ(stat->eval(), expected);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}