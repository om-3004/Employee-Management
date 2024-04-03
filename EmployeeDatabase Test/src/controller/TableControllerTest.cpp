#include "TableFixture.h"
#include "TableControllerTest.h"

TEST_F(TableFixture, Test_createTable) {
	EXPECT_TRUE(TableController::executeCreateQuery(*table, 4, 1));

	std::string_view queryString = R"(SELECT * FROM sqlite_schema WHERE name = "Salary";)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	table->setTableName("Roles");
	EXPECT_FALSE(TableController::executeCreateQuery(*table, 0, 0));

	queryString = R"(SELECT * FROM sqlite_schema WHERE name = "Roles";)";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(TableFixture, Test_deleteTable) {
	EXPECT_TRUE(TableController::executeCreateQuery(*table, 4, 1));

	std::string_view queryString = R"(SELECT * FROM sqlite_schema WHERE name = "Salary";)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_TRUE(TableController::deleteTableQuery("Salary"));

	queryString = R"(SELECT * FROM sqlite_schema WHERE name = "Salary";)";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(TableController::deleteTableQuery("Roles")); //FAIL

	queryString = R"(SELECT * FROM sqlite_schema WHERE name = "Roles";)";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data())); //FAIL
}

TEST_F(TableFixture, Test_createTableQuery) {

	EXPECT_STREQ(R"(CREATE TABLE "Salary"("ID" INT NOT NULL UNIQUE PRIMARY KEY,"baseSalary" REAL NOT NULL,"bonus" REAL NOT NULL,"allowance" REAL ,FOREIGN KEY ("ID") REFERENCES "Employee"("employeeID") ON DELETE CASCADE);)",
		TableControllerTest::createTableQuery(*table, 4, 1).c_str());

	table->setTableName("Roles");
	EXPECT_STREQ("CREATE TABLE \"Roles\"();", TableControllerTest::createTableQuery(*table, 0, 0).c_str());

}
