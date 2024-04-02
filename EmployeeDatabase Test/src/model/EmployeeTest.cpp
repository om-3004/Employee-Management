#include "EmployeeFixture.h"

using EmployeeDB::Model::Gender;

TEST(TestEmployee, Test_getGenderFromString) {
	EXPECT_EQ(Gender::Male, EmployeeDB::Model::getGenderFromString(std::string{ "Male" }));
	EXPECT_NE(Gender::Male, EmployeeDB::Model::getGenderFromString(std::string{ "female" }));
	EXPECT_EQ(Gender::Female, EmployeeDB::Model::getGenderFromString(std::string{ "female" }));
	EXPECT_EQ(Gender::Female, EmployeeDB::Model::getGenderFromString(std::string{ "FEMALE" }));
	EXPECT_NE(Gender::Female, EmployeeDB::Model::getGenderFromString(std::string{ "male" }));
	EXPECT_EQ(Gender::Other, EmployeeDB::Model::getGenderFromString(std::string{ "other" }));
	EXPECT_NE(Gender::Other, EmployeeDB::Model::getGenderFromString(std::string{ "male" }));
}

TEST(TestEmployee, Test_getGenderString) {
	EXPECT_STREQ("Male", EmployeeDB::Model::getGenderString(Gender::Male).c_str());
	EXPECT_STREQ("Female", EmployeeDB::Model::getGenderString(Gender::Female).c_str());
	EXPECT_STREQ("Other", EmployeeDB::Model::getGenderString(Gender::Other).c_str());
}