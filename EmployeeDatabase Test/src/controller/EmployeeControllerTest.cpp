#include "EmployeeControllerTest.h"
#include "EmployeeFixture.h"


TEST_F(EmployeeFixture, Test_getEmployeeIDbyEmail) {
	EXPECT_EQ(EmployeeController::getEmployeeIDbyEmail("john.smith@example.com"), 1);

	EXPECT_EQ(EmployeeController::getEmployeeIDbyEmail("johnnn.smith@example.com"), -1); // FAIL
	EXPECT_NE(EmployeeController::getEmployeeIDbyEmail("johnnn.smith@example.com"), 3); // FAIL
}

TEST_F(EmployeeFixture, Test_insertEmployee) {
	EXPECT_TRUE(EmployeeController::insertEmployee(*employee));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE firstName = "Om" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = R"(SELECT * FROM Employee;)";
	EXPECT_EQ(3, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(EmployeeController::insertEmployee(*employee)); // FAIL
}

TEST_F(EmployeeFixture, Test_getDepartmentIDbyEmployeeID) {
	EXPECT_EQ(EmployeeController::getDepartmentIDbyEmployeeID(1), 1);

	EXPECT_NE(EmployeeController::getDepartmentIDbyEmployeeID(1000), 1); // FAIL
	EXPECT_NE(EmployeeController::getDepartmentIDbyEmployeeID(1), 5); // FAIL
}

TEST_F(EmployeeFixture, Test_checkEmployeeExistence) {
	EXPECT_TRUE(EmployeeController::checkEmployeeExistence("1", "Engineer"));

	EXPECT_FALSE(EmployeeController::checkEmployeeExistence("5", "Engineer")); // FAIL
	EXPECT_FALSE(EmployeeController::checkEmployeeExistence("1", "HR")); // FAIL
}


TEST_F(EmployeeFixture, Test_updateEmployee) {
	employee->setEmployeeID(1);

	EXPECT_TRUE(EmployeeController::updateEmployee(*employee));

	std::string_view queryStr = R"(SELECT * FROM Employee WHERE lastName = "Smith")";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Employee WHERE lastName ="Thakkar")";
	EXPECT_EQ(1, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data()));

	employee->setEmail("david.brown@example.com");
	EXPECT_FALSE(EmployeeController::updateEmployee(*employee)); // FAIL
}

TEST_F(EmployeeFixture, Test_getSalaryDetails) {
	EXPECT_TRUE(EmployeeController::getSalaryDetails(*salary));

	EXPECT_TRUE(EmployeeController::getSalaryDetails(*salary));
	EXPECT_DOUBLE_EQ(500.0, salary->getBonus());
	EXPECT_DOUBLE_EQ(0.85, salary->getPerformanceMetric());
	EXPECT_DOUBLE_EQ(3000.0, salary->getDeduction());
	EXPECT_DOUBLE_EQ(65000.0, salary->getBaseSalary());
	EXPECT_DOUBLE_EQ(7000.0, salary->getAllowance());
}

TEST_F(EmployeeFixture, Test_deleteEmployeeByID) {
	EXPECT_TRUE(EmployeeController::deleteEmployeeByID(1));

	std::string_view queryStr = R"(SELECT * FROM Employee WHERE employeeID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(EmployeeFixture, Test_getUpdateQueryCondition) {
	EXPECT_EQ(EmployeeControllerTest::getUpdateQueryCondition(*employee), R"(firstName = "Om", middleName = "Nilesh", lastName = "Thakkar", dateOfBirth = "30-04-2003", mobileNo = 7283902430, email = "om.thakkar@zuru.com", address = "82, V.P.", gender = "Male", dateOfJoining = "01-01-2024", mentorID = 1, performanceMetric = 5.000000, bonus = 100000.000000)");

	EXPECT_NE(EmployeeControllerTest::getUpdateQueryCondition(*employee), R"(firstName = "Omm", middleName = "Nilesh", lastName = "Thakkar", dateOfBirth = "30-04-2003", mobileNo = 7283902430, email = "om.thakkar@zuru.com", address = "88, V.K.", gender = "Male", dateOfJoining = "01 - 01 - 2024", mentorID = 1, performanceMetric = 5.000000, bonus = 100000.000000)"); // FAIL
}