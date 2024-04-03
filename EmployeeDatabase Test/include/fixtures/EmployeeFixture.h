#ifndef __EmployeeFixture_h__
#define __EmployeeFixture_h__

#include "pch.h"
#include "Employee.h"
#include "DBManager.h"

using EmployeeDB::DBManager;
using EmployeeDB::Model::Employee;
using EmployeeDB::Model::Salary;

struct EmployeeFixture : public testing::Test {
	std::unique_ptr<Employee> employee;
	std::unique_ptr<Salary> salary;

	void SetUp() override {
		employee = std::make_unique<Employee>();
		salary = std::make_unique<Salary>();
		salary->setEmployeeID(1);

		employee->setEmployeeID(1);
		employee->setFirstName("Om");
		employee->setMiddleName("Nilesh");
		employee->setLastName("Thakkar");
		employee->setDateOfBirth("30-04-2003");
		employee->setMobileNo(7283902430);
		employee->setEmail("om.thakkar@zuru.com");
		employee->setAddress("82, V.P.");
		employee->setGender(EmployeeDB::Model::Gender::Male);
		employee->setDateOfJoining("01-01-2024");
		employee->setDepartmentID(1);
		employee->setMentorID(1);
		employee->setPerformanceMetric(5.0);
		employee->setBonus(100000);

		std::string_view query = R"(INSERT INTO Employee ("employeeID", "firstName", "middleName", "lastName", "dateOfBirth", "mobileNo", "email", "address", "gender", "dateOfJoining", "departmentID", "mentorID", "performanceMetric", "bonus") VALUES(1 , "John", "Doe", "Smith", "15-05-1990", 1234567891, "john.smith@example.com", "123 Main St, City, Country", "Male", "10-01-2020", 1, 1, 0.85, 500), (2, 'David', 'Lee', 'Brown', '03-04-1993', 1234509876, 'david.brown@example.com', '345 Oak St, City, Country', 'Male', '12-11-2022', 1, 2, 0.78, 450);)";
		int m_ResultCode = DBManager::instance().executeQuery(query.data());

		query = R"(INSERT INTO Department ("departmentID", "departmentName", "baseSalary", "allowance", "deduction") VALUES(1, "Engineer", 65000, 7000, 3000))";
		m_ResultCode = DBManager::instance().executeQuery(query.data());
	}

	void TearDown() override {
		DBManager::instance().executeTruncateQuery("Employee");
		DBManager::instance().executeTruncateQuery("Department");
	}
};

#endif