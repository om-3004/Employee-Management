#include "QAFixture.h"
#include "QAControllerTest.h"

TEST_F(QAFixture, Test_insertQASuccess) {
	EXPECT_TRUE(QAController::insertQA(*qa));

	std::string_view queryString = "SELECT * FROM QA WHERE testingTool = \"JIRA\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(QAFixture, Test_insertQAFailure) {
	emptyQA->setEmail("jessica.taylor@example.com");
	EXPECT_FALSE(QAController::insertQA(*emptyQA));

	std::string_view queryString = "SELECT * FROM QA";
	EXPECT_NE(3, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = "SELECT * FROM QA WHERE testingTool = \"Selenium\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(QAFixture, Test_selectQASuccess) {
	EXPECT_TRUE(QAController::selectQA("testingTool", "Selenium"));
}

TEST_F(QAFixture, Test_selectQAFailure) {
	EXPECT_FALSE(QAController::selectQA("mobile", "6745678980"));
}

TEST_F(QAFixture, Test_deleteQAByID) {
	EXPECT_TRUE(QAController::deleteQAByID(2));

	std::string_view queryString = "SELECT * FROM Employee WHERE employeeID = 2;";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = "SELECT * FROM QA;";
	EXPECT_EQ(1, DBManager::instance().executeSelectQuery(queryString.data()));

	EXPECT_TRUE(QAController::deleteQAByID(1));

	queryString = "SELECT * FROM Employee;";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(QAFixture, Test_updateQASuccess) {
	emptyQA->setEmployeeID(1);
	emptyQA->setEmail("emilly@example.com");
	emptyQA->setTestingTool("JUnit");

	EXPECT_TRUE(QAController::updateQA(*emptyQA));

	std::string_view queryString = "SELECT * FROM Employee WHERE email = \"emilly@example.com\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = "SELECT * FROM QA WHERE testingTool = \"Chai\" COLLATE NOCASE;";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(QAFixture, Test_updateQAFailure) {
	emptyQA->setEmployeeID(2);
	emptyQA->setMobileNo(9870723456);

	EXPECT_FALSE(QAController::updateQA(*emptyQA));
}

TEST_F(QAFixture, Test_getUpdateQueryConditionEmpty) {
	EXPECT_STREQ("", QAControllerTest::getUpdateQueryCondition(*emptyQA).c_str());
}

TEST_F(QAFixture, Test_getUpdateQueryCondition) {
	emptyQA->setTestingTool("Mocha");

	EXPECT_STREQ("testingTool = \"Mocha\"", QAControllerTest::getUpdateQueryCondition(*emptyQA).c_str());

	emptyQA->setBonus(25000.00);

	EXPECT_STREQ("testingTool = \"Mocha\"", QAControllerTest::getUpdateQueryCondition(*emptyQA).c_str());
}