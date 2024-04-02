#include "HRFixture.h"
#include "HRControllerTest.h"


TEST_F(HRFixture, Test_insertHRSuccess) {
	EXPECT_TRUE(HRController::insertHR(*hr));

	std::string_view queryString = "SELECT * FROM Employee WHERE dateOfBirth = \"15/05/1995\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(HRFixture, Test_insertHRFailure) {
	emptyHR->setEmail("chris.martinez@example.com");
	EXPECT_FALSE(HRController::insertHR(*emptyHR));

	std::string_view queryString = "SELECT * FROM HR";
	EXPECT_NE(3, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = "SELECT * FROM HR WHERE hrSpecialization = \"Training and Development\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(HRFixture, Test_selectHRSuccess) {
	EXPECT_TRUE(HRController::selectHR("hrSpecialization", "Recruitment"));
}

TEST_F(HRFixture, Test_selectHRFailure) {
	EXPECT_FALSE(HRController::selectHR("mobile", "6745678980"));
}

TEST_F(HRFixture, Test_updateHRSuccess) {
	emptyHR->setEmployeeID(1);
	emptyHR->setEmail("michael@example.com");
	emptyHR->setHRSpecialization("Senior Executive");

	EXPECT_TRUE(HRController::updateHR(*emptyHR));

	std::string_view queryString = "SELECT * FROM Employee WHERE email = \"michael@example.com\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = "SELECT * FROM HR WHERE hrSpecialization = \"Senior Executive\" COLLATE NOCASE;";
	EXPECT_EQ(1, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(HRFixture, Test_updateHRFailure) {
	emptyHR->setEmployeeID(2);
	emptyHR->setMobileNo(4567890128);

	EXPECT_FALSE(HRController::updateHR(*emptyHR));
}

TEST_F(HRFixture, Test_deleteHRByID) {
	EXPECT_TRUE(HRController::deleteHRByID(2));

	std::string_view queryString = "SELECT * FROM Employee WHERE employeeID = 2;";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));

	queryString = "SELECT * FROM HR;";
	EXPECT_EQ(1, DBManager::instance().executeSelectQuery(queryString.data()));

	EXPECT_TRUE(HRController::deleteHRByID(1));

	queryString = "SELECT * FROM Employee;";
	EXPECT_EQ(0, DBManager::instance().executeRowCountQuery(queryString.data()));
}

TEST_F(HRFixture, Test_getUpdateQueryConditionEmpty) {
	EXPECT_STREQ("", HRControllerTest::getUpdateQueryCondition(*emptyHR).c_str());
}

TEST_F(HRFixture, Test_getUpdateQueryCondition) {
	emptyHR->setHRSpecialization("Sr. HR Executive");

	EXPECT_STREQ("hrSpecialization = \"Sr. HR Executive\"", HRControllerTest::getUpdateQueryCondition(*emptyHR).c_str());

	emptyHR->setFirstName("Himanshu");

	EXPECT_STREQ("hrSpecialization = \"Sr. HR Executive\"", HRControllerTest::getUpdateQueryCondition(*emptyHR).c_str());
}