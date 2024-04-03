#ifndef __DepartmentFixture_h__
#define __DepartmentFixture_h__

#include "pch.h"
#include "Department.h"
#include "DBManager.h"

using EmployeeDB::DBManager;
using EmployeeDB::Model::Department;

struct DepartmentFixture : public testing::Test {
	std::unique_ptr<Department> department;

	void SetUp() override {
		department = std::make_unique<Department>(true);
		department->setDepartmentID(1);
		department->setDepartmentName("Engineering");
		department->setBaseSalary(50000.00);
		department->setAllowance(24000.00);
		department->setDeduction(500.00);


		std::string_view query = R"(INSERT INTO Department("departmentID", "departmentName", "baseSalary", "allowance", "deduction") VALUES (1, 'Engineer', 65000, 7000, 3000), (2, 'Finance', 65000, 6000, 2500), (3, 'HR', 55000, 4000, 1500), (4, 'QA', 59000, 4800, 1900);)";

		DBManager::instance().executeQuery(query.data());
	}

	void TearDown() override {
		DBManager::instance().executeTruncateQuery("Department");
	}
};

#endif