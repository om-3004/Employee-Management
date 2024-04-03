#include "HRFixture.h"
#include "HRControllerTest.h"

TEST_F(HRFixture, Test_insertHR) {
	EXPECT_TRUE(HRController::insertHR(*hr));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE firstName = "Johnieee" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	EXPECT_FALSE(HRController::insertHR(*hr)); // FAIL

	queryString = R"(SELECT * FROM HR;)";
	EXPECT_EQ(3, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(HRFixture, Test_selectHR) {
	EXPECT_TRUE(HRController::selectHR("hrSpecialization", "Recruitment"));

	EXPECT_FALSE(HRController::selectHR("mobilee", "6745678980")); //FAIL
}


TEST_F(HRFixture, Test_updateHR) {
	hr->setEmployeeID(1);

	EXPECT_TRUE(HRController::updateHR(*hr));

	std::string_view queryString = R"(SELECT * FROM Employee WHERE email = "michael.johnson@example.com" COLLATE NOCASE;)";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data())); // 0 rows found

	queryString = R"(SELECT * FROM Employee WHERE email = "john.wan.steven234@example.com" COLLATE NOCASE;)";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data())); // 1 row found

	hr->setEmail("chris.martinez@example.com");

	EXPECT_FALSE(HRController::updateHR(*hr)); //FAIL
}

TEST_F(HRFixture, Test_deleteHRByID) {
	EXPECT_TRUE(HRController::deleteHRByID(1));
	EXPECT_TRUE(HRController::deleteHRByID(2));

	std::string_view queryStr = R"(SELECT * FROM HR WHERE employeeID = 1)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
	queryStr = R"(SELECT * FROM HR WHERE employeeID = 2)";
	EXPECT_EQ(0, EmployeeDB::DBManager::instance().executeRowCountQuery(queryStr.data())); // 0 rows found
}

TEST_F(HRFixture, Test_getUpdateQueryCondition) {

	EXPECT_STREQ(R"(hrSpecialization = "HR Executive")", HRControllerTest::getUpdateQueryCondition(*hr).c_str());
	EXPECT_STRNE(R"(hrSpecializaon = "HR Executive")", HRControllerTest::getUpdateQueryCondition(*hr).c_str());

}