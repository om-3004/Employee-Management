#include "FinanceControllerTest.h"
#include "FinanceFixture.h"

using EmployeeDB::Controller::FinanceController;

TEST_F(FinanceFixture, Test_insertFinance) {
	EXPECT_TRUE(FinanceController::insertFinance(*finance));

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
	EXPECT_EQ(FinanceControllerTest::getUpdateQueryCondition(*finance), R"(accountingTool = "SAP ERP")");

	EXPECT_NE(FinanceControllerTest::getUpdateQueryCondition(*finance), R"(accountingTooool = "SAP ERP")"); // FAIL
}