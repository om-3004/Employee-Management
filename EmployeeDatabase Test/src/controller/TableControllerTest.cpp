#include "TableFixture.h"
#include "TableControllerTest.h"

TEST_F(TableFixture, Test_createTableSuccess) {
	EXPECT_TRUE(TableController::executeCreateQuery(*table, 4, 1));

	std::string_view queryString = "SELECT * FROM sqlite_schema WHERE name = \"Salary\";";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(TableFixture, Test_createTableFailure) {
	EXPECT_FALSE(TableController::executeCreateQuery(*emptyTable, 0, 0));

	std::string_view queryString = "SELECT * FROM sqlite_schema WHERE name = \"Roles\";";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(TableFixture, Test_deleteTableSuccess) {
	EXPECT_TRUE(TableController::executeCreateQuery(*table, 4, 1));

	std::string_view queryString = "SELECT * FROM sqlite_schema WHERE name = \"Salary\";";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_TRUE(TableController::deleteTableQuery("Salary"));

	queryString = "SELECT * FROM sqlite_schema WHERE name = \"Salary\";";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(TableFixture, Test_deleteTableFailure) {
	EXPECT_FALSE(TableController::deleteTableQuery("Roles"));

	std::string_view queryString = "SELECT * FROM sqlite_schema WHERE name = \"Roles\";";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(TableFixture, Test_getCreateTableQueryEmpty) {
	EXPECT_STREQ("CREATE TABLE \"Roles\"();", TableControllerTest::createTableQuery(*emptyTable, 0, 0).c_str());
}

TEST_F(TableFixture, Test_getCreateTableQuery) {
	EXPECT_STREQ("CREATE TABLE \"Salary\"(\"ID\" INT NOT NULL UNIQUE PRIMARY KEY,\"baseSalary\" REAL NOT NULL,\"bonus\" REAL NOT NULL,\"allowance\" REAL ,FOREIGN KEY (\"ID\") REFERENCES \"Employee\"(\"employeeID\") ON DELETE CASCADE);",
		TableControllerTest::createTableQuery(*table, 4, 1).c_str());
}