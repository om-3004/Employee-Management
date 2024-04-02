#ifndef __SalaryFixture_h__
#define __SalaryFixture_h__

#include "pch.h"
#include "Salary.h"

using EmployeeDB::Model::Salary;

class SalaryFixture : public ::testing::Test {
protected:
	void SetUp() override {
		salary = std::make_unique<Salary>();
		salary->setDepartmentID(1);
		salary->setEmployeeID(1);
		salary->setAllowance(6000.0);
		salary->setBaseSalary(65000.0);
		salary->setDeduction(2500.00);
		salary->setBonus(5000.0);
		salary->setPerformanceMetric(0.84);

		emptySalary = std::make_unique<Salary>();
	}

	std::unique_ptr<Salary> salary;
	std::unique_ptr<Salary> emptySalary;
};

#endif