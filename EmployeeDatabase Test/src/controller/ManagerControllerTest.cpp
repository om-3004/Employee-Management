#include "ManagerControllerTest.h"
#include "ManagerFixture.h"

TEST_F(ManagerFixture, Test_insertManager) {

	std::string_view queryString = R"(SELECT * FROM Employee WHERE firstName = "David" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_TRUE(ManagerController::insertManager(*manager));

	queryString = R"(SELECT * FROM Manager WHERE managerID = "2" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = R"(SELECT * FROM Manager;)";
	EXPECT_EQ(3, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(ManagerController::insertManager(*manager)); //FAIL
}

TEST_F(ManagerFixture, Test_selectManager) {
	EXPECT_TRUE(ManagerController::selectManager("firstName", "David"));
	EXPECT_TRUE(ManagerController::selectManager("role", "Java"));

	EXPECT_FALSE(ManagerController::selectManager("rolee", "C++")); //FAIL
}

TEST_F(ManagerFixture, Test_deleteManagerByID) {
	EXPECT_TRUE(ManagerController::deleteManagerByID(1));
	EXPECT_TRUE(ManagerController::deleteManagerByID(3));

	std::string_view queryStr = R"(SELECT * FROM Manager WHERE managerID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found

	queryStr = R"(SELECT * FROM Manager WHERE managerID = 3)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(ManagerFixture, Test_updateManager) {
	manager->setManagerID(1);

	EXPECT_TRUE(ManagerController::updateManager(*manager));
	std::string_view queryStr = R"(SELECT * FROM Manager WHERE role = "Java")";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Manager WHERE role = "Lead C++ developer")";
	EXPECT_EQ(1, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 1 row found

	//manager->setManagerID(3);
	manager->setEmail("sarah.wilson@example.com");
	EXPECT_FALSE(ManagerController::updateManager(*manager)); // FAIL
}

TEST_F(ManagerFixture, Test_checkManagerExistence) {
	EXPECT_TRUE(ManagerController::checkManagerExistence("1"));
	EXPECT_TRUE(ManagerController::checkManagerExistence("3"));

	EXPECT_FALSE(ManagerController::checkManagerExistence("2")); // FAIL
}

TEST_F(ManagerFixture, Test_getUpdateQueryCondition) {
	EXPECT_STREQ(ManagerControllerTest::getUpdateQueryCondition(*manager).c_str(), R"(teamSize = 6, yearsOfExp = 4.500000, projectTitle = "Heartbeat Tracker", role = "Lead C++ developer")");
	
	EXPECT_STRNE(ManagerControllerTest::getUpdateQueryCondition(*manager).c_str(), R"(teamSizeee = 6, yearsOfExp = 4.500000, projectTitle = "Heartbeat Tracker", role = "Lead C++ developer")");
}