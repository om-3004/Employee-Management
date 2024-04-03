#include "FinanceControllerTest.h"
#include "FinanceFixture.h"

TEST_F(FinanceFixture, Test_insertFinance) {
	EXPECT_TRUE(FinanceController::insertFinance(*finance));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE firstName = "Alan" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = R"(SELECT * FROM Employee;)";
	EXPECT_EQ(3, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(FinanceController::insertFinance(*finance)); // FAIL
}

TEST_F(FinanceFixture, Test_selectFinance) {
	EXPECT_TRUE(FinanceController::selectFinance("accountingTool", "Tally"));
	EXPECT_TRUE(FinanceController::selectFinance("accountingTool", "Excel"));

	EXPECT_FALSE(FinanceController::selectFinance("accountingTooool", "Excel")); // FAIL
}

TEST_F(FinanceFixture, Test_deleteFinanceByID) {
	EXPECT_TRUE(FinanceController::deleteFinanceByID(1));
	EXPECT_TRUE(FinanceController::deleteFinanceByID(2));

	std::string_view queryStr = R"(SELECT * FROM Finance WHERE employeeID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Finance WHERE employeeID = 2)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(FinanceFixture, Test_updateFinance) {
	finance->setEmployeeID(1);
	EXPECT_TRUE(FinanceController::updateFinance(*finance));

	std::string_view queryStr = R"(SELECT * FROM Finance WHERE accountingTool = "Tally")";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM Finance WHERE accountingTool = "SAP ERP")";
	EXPECT_EQ(1, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 1 row found

	finance->setEmail("sarah.wilson@example.com");
	EXPECT_FALSE(FinanceController::updateFinance(*finance)); // FAIL
}

TEST_F(FinanceFixture, Test_getUpdateQueryCondition) {
	EXPECT_STREQ(FinanceControllerTest::getUpdateQueryCondition(*finance).c_str(), R"(accountingTool = "SAP ERP")");

	EXPECT_STRNE(FinanceControllerTest::getUpdateQueryCondition(*finance).c_str(), R"(accountingTooool = "SAP ERP")"); // FAIL
}