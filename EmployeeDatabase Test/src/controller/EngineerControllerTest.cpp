#include "EngineerControllerTest.h"
#include "EngineerFixture.h"

TEST_F(EngineerFixture, Test_insertEngineer) {
	EXPECT_TRUE(EngineerController::insertEngineer(*engineer));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE firstName = "Alan" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = R"(SELECT * FROM Employee;)";
	EXPECT_EQ(3, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(EngineerController::insertEngineer(*engineer)); // FAIL
}

TEST_F(EngineerFixture, Test_selectEngineer) {
	EXPECT_TRUE(EngineerController::selectEngineer("technology", "C++"));
	EXPECT_TRUE(EngineerController::selectEngineer("technology", "NodeJS"));

	EXPECT_FALSE(EngineerController::selectEngineer("technologyy", "NodeJS")); // FAIL
}

TEST_F(EngineerFixture, Test_deleteEngineerByID) {
	EXPECT_TRUE(EngineerController::deleteEngineerByID(1));
	EXPECT_TRUE(EngineerController::deleteEngineerByID(2));

	std::string_view queryStr = R"(SELECT * FROM Engineer WHERE employeeID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Engineer WHERE employeeID = 2)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(EngineerFixture, Test_updateEngineer) {
	engineer->setEmployeeID(1);
	EXPECT_TRUE(EngineerController::updateEngineer(*engineer));

	std::string_view queryStr = R"(SELECT * FROM Engineer WHERE technology = "C++")";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Engineer WHERE technology = "Django")";
	EXPECT_EQ(1, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 1 row found

	engineer->setEmail("david.brown@example.com");
	EXPECT_FALSE(EngineerController::updateEngineer(*engineer)); // FAIL
}

TEST_F(EngineerFixture, Test_getUpdateQueryCondition) {
	EXPECT_STREQ(EngineerControllerTest::getUpdateQueryCondition(*engineer).c_str(), R"(technology = "Django")");

	EXPECT_STRNE(EngineerControllerTest::getUpdateQueryCondition(*engineer).c_str(), R"(technology = "Djangooo")"); // FAIL
}