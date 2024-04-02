#ifndef __FinanceFixture_h__
#define __FinanceFixture_h__

#include "pch.h"
#include "Finance.h"
#include "DBManager.h"

struct FinanceFixture : public testing::Test {
	std::unique_ptr<EmployeeDB::Model::Finance> finance;
	void SetUp() override {
		finance = std::make_unique<EmployeeDB::Model::Finance>();

		finance->setEmployeeID(32);
		finance->setFirstName("Alan");
		finance->setMiddleName("Alex");
		finance->setLastName("Walker");
		finance->setDateOfBirth("23-05-1998");
		finance->setMobileNo(8756245903);
		finance->setEmail("aln23kr@gmail.com");
		finance->setAddress("88, V.K.");
		finance->setGender(EmployeeDB::Model::Gender::Male);
		finance->setDateOfJoining("01-01-2024");
		finance->setDepartmentID(2);
		finance->setMentorID(1);
		finance->setPerformanceMetric(7);
		finance->setBonus(30000);
		finance->setAccountingTool("SAP ERP");

		EmployeeDB::DBManager::executeConfigQuery();

		std::string_view query = R"(INSERT INTO Department("departmentID", "departmentName", "baseSalary", "allowance", "deduction")VALUES (1, 'Engineer', 65000, 7000, 3000), (2, 'Finance', 65000, 6000, 2500);)";

		EmployeeDB::DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Employee ("employeeID", "firstName", "middleName", "lastName", "dateOfBirth", "mobileNo", "email","address", "gender", "dateOfJoining", "departmentID", "mentorID", "performanceMetric", "bonus") VALUES (1, 'Jane', 'Doe', 'Smith', '20-08-1992', 9876543211, 'jane.smith@example.com', '456 Elm St, City, Country', 'Female', '20-05-2018', 2, 1, 0.75, 400), (2, 'Sarah', 'Elizabeth', 'Wilson', '10-07-1995', 9876543212, 'sarah.wilson@example.com', '567 Elm St, City, Country', 'Female','05-09-2023', 2, 1, 0.88, 600);)";

		EmployeeDB::DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Finance ("employeeID", "accountingTool") VALUES (1, 'Tally'), (2, 'Excel');)";

		EmployeeDB::DBManager::instance().executeQuery(query.data());
	}

	void TearDown() override {
		EmployeeDB::DBManager::instance().executeTruncateQuery("Department");
		EmployeeDB::DBManager::instance().executeTruncateQuery("Employee");
		EmployeeDB::DBManager::instance().executeTruncateQuery("Finance");
	}

};

#endif