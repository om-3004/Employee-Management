#include "DepartmentControllerTest.h"
#include "DepartmentFixture.h"

TEST_F(DepartmentFixture, Test_insertDepartment) {
	EXPECT_TRUE(DepartmentController::insertDepartment(*department));

	std::string_view queryString = R"(SELECT * FROM Department WHERE departmentName = "Engineering" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = R"(SELECT * FROM Department;)";
	EXPECT_EQ(5, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(DepartmentController::insertDepartment(*department)); // FAIL
}

TEST_F(DepartmentFixture, Test_getDepartmentIDbyName) {
	EXPECT_EQ(DepartmentController::getDepartmentIDbyName("Engineer"), 1);
	EXPECT_EQ(DepartmentController::getDepartmentIDbyName("Finance"), 2);

	EXPECT_NE(DepartmentController::getDepartmentIDbyName("Finance"), 3); // FAIL
}

TEST_F(DepartmentFixture, Test_checkDepartmentExistence) {
	EXPECT_TRUE(DepartmentController::checkDepartmentExistence("1"));
	EXPECT_TRUE(DepartmentController::checkDepartmentExistence("2"));

	EXPECT_FALSE(DepartmentController::checkDepartmentExistence("10")); // FAIL
}

TEST_F(DepartmentFixture, Test_selectDepartment) {
	EXPECT_TRUE(DepartmentController::selectDepartment("departmentName", "Engineer"));
	EXPECT_TRUE(DepartmentController::selectDepartment("departmentID", "3"));

	EXPECT_FALSE(DepartmentController::selectDepartment("departmentttID", "10")); // FAIL
}

TEST_F(DepartmentFixture, Test_deleteDepartmentByID) {
	EXPECT_TRUE(DepartmentController::deleteDepartmentByID(1));
	EXPECT_TRUE(DepartmentController::deleteDepartmentByID(2));

	std::string_view queryStr = R"(SELECT * FROM Department WHERE departmentID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found

	queryStr = R"(SELECT * FROM Department WHERE departmentID = 2)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(DepartmentFixture, Test_updateDepartment) {
	EXPECT_TRUE(DepartmentController::updateDepartment(*department));

	std::string_view queryStr = R"(SELECT * FROM Department WHERE departmentName = "Engineer")";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Department WHERE departmentName = "Engineering")";
	EXPECT_EQ(1, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 1 row found

	department->setDepartmentName("Finance");
	EXPECT_FALSE(DepartmentController::updateDepartment(*department)); // FAIL
}

TEST_F(DepartmentFixture, Test_getUpdateQueryCondition) {
	EXPECT_STREQ(DepartmentControllerTest::getUpdateQueryCondition(*department).c_str(), R"(departmentName = "Engineering", baseSalary = 50000.000000, allowance = 24000.000000, deduction = 500.000000)");
	
	EXPECT_STRNE(DepartmentControllerTest::getUpdateQueryCondition(*department).c_str(), R"(departmentName = "Engineeringg", baseSalary = 50000.000000, allowance = 24000.000000, deduction = 500.000000)"); // FAIL
}