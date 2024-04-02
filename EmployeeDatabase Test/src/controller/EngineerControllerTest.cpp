#include "EngineerControllerTest.h"
#include "EngineerFixture.h"

using EmployeeDB::Controller::EngineerController;

TEST_F(EngineerFixture, Test_insertEngineer) {
	EXPECT_TRUE(EngineerController::insertEngineer(*engineer));

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
	EXPECT_EQ(EngineerControllerTest::getUpdateQueryCondition(*engineer), R"(technology = "Django")");

	EXPECT_NE(EngineerControllerTest::getUpdateQueryCondition(*engineer), R"(technology = "Djangooo")"); // FAIL
}