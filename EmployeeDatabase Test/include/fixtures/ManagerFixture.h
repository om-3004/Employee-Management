#ifndef __ManagerFixture_h__
#define __ManagerFixture_h__

#include "pch.h"
#include "Manager.h"
#include "DBManager.h"

struct ManagerFixture : public testing::Test {
	std::unique_ptr<EmployeeDB::Model::Manager> manager;

	void SetUp() override {
		manager = std::make_unique<EmployeeDB::Model::Manager>();

		manager->setEmployeeID(2);
		manager->setFirstName("Varun");
		manager->setMiddleName("Lee");
		manager->setLastName("Brown");
		manager->setDateOfBirth("22-06-1989");
		manager->setMobileNo(9675021123);
		manager->setEmail("dalien.garcia@example.com");
		manager->setAddress("234 Cedar St, City, Country");
		manager->setGender(EmployeeDB::Model::Gender::Male);
		manager->setDateOfJoining("30-08-2018");
		manager->setDepartmentID(1);
		manager->setMentorID(1);
		manager->setPerformanceMetric(0.85);
		manager->setBonus(550.0);
		manager->setManagerID(2);
		manager->setTeamSize(6);
		manager->setYearsOfExp(4.5);
		manager->setProjectTitle("Heartbeat Tracker");
		manager->setRole("Lead C++ developer");

		EmployeeDB::DBManager::executeConfigQuery();

		std::string_view query = R"(INSERT INTO Department ("departmentID", "departmentName", "baseSalary", "allowance", "deduction") VALUES (1, 'Engineer', 65000, 7000, 3000), (2, 'Finance', 65000, 6000, 2500), (3, 'HR', 55000, 4000, 1500), (4, 'QA', 59000, 4800, 1900);)";

		EmployeeDB::DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Employee ("employeeID", "firstName", "middleName", "lastName", "dateOfBirth", "mobileNo", "email", "address", "gender", "dateOfJoining", "departmentID", "mentorID", "performanceMetric", "bonus") VALUES (1, 'John', 'Doe', 'Smith', '15-05-1990', 1234567891, 'john.smith@example.com', '123 Main St, City, Country', 'Male', '10-01-2020', 1, 1, 0.85, 500), (2, 'David', 'Lee', 'Brown', '03-04-1993', 1234509876, 'david.brown@example.com', '345 Oak St, City, Country', 'Male', '12-11-2022', 1, 2, 0.78, 450), (3, 'Jane', 'Doe', 'Smith', '20-08-1992', 9876543211, 'jane.smith@example.com', '456 Elm St, City, Country', 'Female', '20-05-2018', 2, 3, 0.75, 400), (4, 'Sarah', 'Elizabeth', 'Wilson', '10-07-1995', 9876543212, 'sarah.wilson@example.com', '567 Elm St, City, Country', 'Female', '05-09-2023', 2, 3, 0.88, 600);)";

		EmployeeDB::DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Manager("managerID", "departmentID", "teamSize", "yearsOfExp", "projectTitle", "role") VALUES (1, 1, 15, 10, 'Project A', 'Java'), (3, 2, 18, 12, 'Project E', 'SAP');)";

		EmployeeDB::DBManager::instance().executeQuery(query.data());
	}

	void TearDown() override {
		EmployeeDB::DBManager::instance().executeTruncateQuery("Department");
		EmployeeDB::DBManager::instance().executeTruncateQuery("Employee");
		EmployeeDB::DBManager::instance().executeTruncateQuery("Manager");
	}
};

#endif