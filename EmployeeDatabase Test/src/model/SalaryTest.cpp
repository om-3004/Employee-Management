#include "SalaryFixture.h"

TEST_F(SalaryFixture, Test_computeSalaryEmpty) {
	double computedSalary = emptySalary->computeSalary();
	double actualSalary = 0.0;

	EXPECT_DOUBLE_EQ(computedSalary, actualSalary);
}

TEST_F(SalaryFixture, Test_computeSalary) {
	double computedSalary = salary->computeSalary();
	double actualSalary = 74046;

	EXPECT_DOUBLE_EQ(computedSalary, actualSalary);
}
