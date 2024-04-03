#include "QAFixture.h"
#include "QAControllerTest.h"

TEST_F(QAFixture, Test_insertQA) {
	EXPECT_TRUE(QAController::insertQA(*qa));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE firstName = "Johnieee" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(QAController::insertQA(*qa)); // FAIL

	queryString = R"(SELECT * FROM QA;)";
	EXPECT_EQ(3, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(QAFixture, Test_selectQA) {
	EXPECT_TRUE(QAController::selectQA("testingTool", "JIRA"));

	EXPECT_FALSE(QAController::selectQA("mobilee", "8690785697")); //FAIL
}


TEST_F(QAFixture, Test_updateQA) {
	qa->setEmployeeID(1);

	EXPECT_TRUE(QAController::updateQA(*qa));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE email = "emily.williams@example.com" COLLATE NOCASE;)";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data())); // 0 rows found

	queryString = R"(SELECT * FROM Employee WHERE email = "john.doe.steven@example.com" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data())); // 1 row found

	qa->setEmail("jessica.taylor@example.com");

	EXPECT_FALSE(QAController::updateQA(*qa)); //FAIL
}

TEST_F(QAFixture, Test_deleteQAByID) {
	EXPECT_TRUE(QAController::deleteQAByID(1));
	EXPECT_TRUE(QAController::deleteQAByID(2));

	std::string_view queryStr = R"(SELECT * FROM QA WHERE employeeID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM QA WHERE employeeID = 2)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(QAFixture, Test_getUpdateQueryCondition) {

	EXPECT_STREQ(R"(testingTool = "JIRA")", QAControllerTest::getUpdateQueryCondition(*qa).c_str());
	EXPECT_STRNE(R"(testingToool = "JIRA")", QAControllerTest::getUpdateQueryCondition(*qa).c_str());

}
