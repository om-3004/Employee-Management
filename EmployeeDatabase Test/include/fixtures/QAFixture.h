#ifndef __QAFixture_h__
#define __QAFixture_h__

#include "pch.h"
#include "QA.h"
#include "DBManager.h"

using EmployeeDB::Model::QA;
using EmployeeDB::DBManager;

struct QAFixture : public ::testing::Test {
    std::unique_ptr<QA> qa;

    void SetUp() override {
        qa = std::make_unique<QA>();
        qa->setEmployeeID(26);
        qa->setFirstName("Johnieee");
        qa->setMiddleName("Doeyy");
        qa->setLastName("Steven");
        qa->setDateOfBirth("15/05/1995");
        qa->setMobileNo(8690785697);
        qa->setEmail("john.doe.steven@example.com");
        qa->setAddress("123 Main St");
        qa->setGender(EmployeeDB::Model::Gender::Male);
        qa->setDateOfJoining("10/07/2003");
        qa->setDepartmentID(4);
        qa->setMentorID(1);
        qa->setPerformanceMetric(8.5);
        qa->setBonus(50000);
        qa->setTestingTool("JIRA");


        DBManager::executeConfigQuery();

        std::string_view insertQuery = R"(INSERT INTO Department ("departmentID", "departmentName", "baseSalary", "allowance", "deduction") VALUES(1, 'Engineer', 65000, 7000, 3000),(3, 'HR', 55000, 4000, 1500),(4, 'QA', 59000, 4800, 1900);)";

        DBManager::instance().executeQuery(insertQuery.data());

        insertQuery = R"(INSERT INTO Employee ("employeeID", "firstName", "middleName", "lastName", "dateOfBirth", "mobileNo", "email", "address", "gender", "dateOfJoining", "departmentID", "mentorID", "performanceMetric", "bonus") VALUES(1, 'Emily', 'Anne', 'Williams', '25-10-1988', 9870723456, 'emily.williams@example.com', '101 Pine St, City, Country', 'Female', '15-02-2021', 4, 1, 0.82, 550),(2, 'Jessica', 'Marie', 'Taylor', '14-09-1987', 9878123456, 'jessica.taylor@example.com', '908 Maple St, City, Country', 'Female', '25-07-2019', 4, 2, 0.81, 500);)";

        DBManager::instance().executeQuery(insertQuery.data());

        insertQuery = R"(INSERT INTO QA ("employeeID", "testingTool") VALUES (1, 'Chai'),(2, 'Selenium');)";

        DBManager::instance().executeQuery(insertQuery.data());
    }

    void TearDown() override {
        DBManager::instance().executeTruncateQuery("Department");
        DBManager::instance().executeTruncateQuery("Employee");
        DBManager::instance().executeTruncateQuery("QA");
    }

};

#endif