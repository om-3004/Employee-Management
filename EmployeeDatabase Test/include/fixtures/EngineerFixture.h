#ifndef __EngineerFixture_h__
#define __EngineerFixture_h__

#include "pch.h"
#include "Engineer.h"
#include "DBManager.h"

using EmployeeDB::DBManager;
using EmployeeDB::Model::Engineer;

struct EngineerFixture : public testing::Test {
	std::unique_ptr<Engineer> engineer;

	void SetUp() override {
		engineer = std::make_unique<Engineer>();

		engineer->setEmployeeID(6);
		engineer->setFirstName("Alan");
		engineer->setMiddleName("");
		engineer->setLastName("Walker");
		engineer->setDateOfBirth("11-09-2002");
		engineer->setMobileNo(8756908765);
		engineer->setEmail("aln.wlkr@gmail.com");
		engineer->setAddress("88, V.K.");
		engineer->setGender(EmployeeDB::Model::Gender::Male);
		engineer->setDateOfJoining("01-01-2024");
		engineer->setDepartmentID(1);
		engineer->setMentorID(1);
		engineer->setPerformanceMetric(5.0);
		engineer->setBonus(100000);
		engineer->setTechnology("Django");

		DBManager::executeConfigQuery();

		std::string_view query = R"(INSERT INTO Department("departmentID", "departmentName", "baseSalary", "allowance", "deduction") VALUES (1, 'Engineer', 65000, 7000, 3000);)";

		DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Employee("employeeID", "firstName", "middleName", "lastName", "dateOfBirth", "mobileNo", "email", "address", "gender", "dateOfJoining", "departmentID", "mentorID", "performanceMetric", "bonus") VALUES (1, 'John', 'Doe', 'Smith', '15-05-1990', 1234567891, 'john.smith@example.com', '123 Main St, City, Country', 'Male', '10-01-2020', 1, 1, 0.85, 500), (2, 'David', 'Lee', 'Brown', '03-04-1993', 1234509876, 'david.brown@example.com', '345 Oak St, City, Country', 'Male', '12-11-2022', 1, 2, 0.78, 450);)";

		DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Engineer("employeeID", "technology") VALUES (1, 'C++'), (2, 'NodeJS');)";

		DBManager::instance().executeQuery(query.data());
	}

	void TearDown() override {
		DBManager::instance().executeTruncateQuery("Department");
		DBManager::instance().executeTruncateQuery("Employee");
		DBManager::instance().executeTruncateQuery("Engineer");
	}
};

#endif