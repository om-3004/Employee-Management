#ifndef __HRFixture_h__
#define __HRFixture_h__

#include "pch.h"
#include "HR.h"
#include "DBManager.h"

using EmployeeDB::Model::HR;
using EmployeeDB::DBManager;

struct HRFixture : public ::testing::Test {

    std::unique_ptr<HR> hr;

    void SetUp() override {
        hr = std::make_unique<HR>();
        hr->setEmployeeID(30);
        hr->setFirstName("Johnieee");
        hr->setMiddleName("Doeyy");
        hr->setLastName("Swan");
        hr->setDateOfBirth("15/05/1995");
        hr->setMobileNo(8690785692);
        hr->setEmail("john.wan.steven234@example.com");
        hr->setAddress("123 Main St");
        hr->setGender(EmployeeDB::Model::Gender::Male);
        hr->setDateOfJoining("10/07/1994");
        hr->setDepartmentID(3);
        hr->setMentorID(2);
        hr->setPerformanceMetric(6);
        hr->setBonus(30000);
        hr->setHRSpecialization("HR Executive");

        DBManager::executeConfigQuery();

        std::string_view insertQuery = R"(INSERT INTO Department ("departmentID", "departmentName", "baseSalary", "allowance", "deduction") VALUES (1, 'Engineer', 65000, 7000, 3000),(3, 'HR', 55000, 4000, 1500);)";

        DBManager::instance().executeQuery(insertQuery.data());

        insertQuery = R"(INSERT INTO Employee ("employeeID", "firstName", "middleName", "lastName", "dateOfBirth", "mobileNo", "email", "address", "gender", "dateOfJoining", "departmentID", "mentorID", "performanceMetric", "bonus") VALUES (1, 'Michael', 'James', 'Johnson', '12-12-1985', 4567890128, 'michael.johnson@example.com', '789 Oak St, City, Country', 'Male', '05-03-2019', 3, 1, 0.9, 600), (2, 'Christopher', 'Ray', 'Martinez', '28-02-1991', 4567890129, 'chris.martinez@example.com', '789 Pine St, City, Country', 'Male', '15-03-2020', 3, 2, 0.92, 700);)";

        DBManager::instance().executeQuery(insertQuery.data());

        insertQuery = R"(INSERT INTO HR ("employeeID", "hrSpecialization") VALUES (1, 'Recruitment'),(2, 'Training and Development');)";

        DBManager::instance().executeQuery(insertQuery.data());
    }

    void TearDown() override {
        DBManager::instance().executeTruncateQuery("Department");
        DBManager::instance().executeTruncateQuery("Employee");
        DBManager::instance().executeTruncateQuery("HR");
    }

};

#endif