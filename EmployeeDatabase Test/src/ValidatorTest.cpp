#include "pch.h"
#include "include/Validator.h"

using EmployeeDB::Validator;

TEST(ValidatorTest, Test_validateName) {
	ASSERT_TRUE(Validator::validateName("Om"));
	ASSERT_TRUE(Validator::validateName("abc"));
	ASSERT_FALSE(Validator::validateName("Om Thakkar"));
	ASSERT_FALSE(Validator::validateName("1"));
	ASSERT_FALSE(Validator::validateName("012"));
	ASSERT_FALSE(Validator::validateName("[]"));
	ASSERT_FALSE(Validator::validateName("@"));
	ASSERT_FALSE(Validator::validateName("012"));
}

TEST(TestValidator, Test_validateEmail) {
	ASSERT_TRUE(Validator::validateEmail("Om.Thakkar@gmail.com"));
	ASSERT_TRUE(Validator::validateEmail("Om.Thakkar@zuru.com"));
	ASSERT_FALSE(Validator::validateEmail("Om.Thakkar@zu$ru.com"));
	ASSERT_FALSE(Validator::validateEmail("Om.Thakkarhizu$ru.com"));
	ASSERT_FALSE(Validator::validateEmail("Om.Thakkar@@zuru.com"));
	ASSERT_FALSE(Validator::validateEmail("Om.Thakkar@.com"));
	ASSERT_FALSE(Validator::validateEmail("Om.Thakkar@"));
	ASSERT_FALSE(Validator::validateEmail("Om.com"));
}

TEST(TestValidator, Test_validateMobile) {
	ASSERT_TRUE(Validator::validateMobile("8467298340"));
	ASSERT_FALSE(Validator::validateMobile("3467298340"));
	ASSERT_FALSE(Validator::validateMobile("34672983"));
	ASSERT_FALSE(Validator::validateMobile("34672983456"));
	ASSERT_FALSE(Validator::validateMobile("84672@5634"));
}

TEST(TestValidator, Test_validateDate) {
	ASSERT_TRUE(Validator::validateDate("11/09/2002"));
	ASSERT_TRUE(Validator::validateDate("29/2/2024"));
	ASSERT_TRUE(Validator::validateDate("2.2.2023"));
	ASSERT_TRUE(Validator::validateDate("2-2-2023"));
	ASSERT_FALSE(Validator::validateDate("00/9/1902"));
	ASSERT_FALSE(Validator::validateDate("29/2/2023"));
}

TEST(TestValidator, Test_validateGender) {
	ASSERT_TRUE(Validator::validateGender(std::string("male")));
	ASSERT_TRUE(Validator::validateGender(std::string("female")));
	ASSERT_TRUE(Validator::validateGender(std::string("other")));
	ASSERT_FALSE(Validator::validateGender(std::string("Male")));
	ASSERT_FALSE(Validator::validateGender(std::string("Female")));
	ASSERT_FALSE(Validator::validateGender(std::string("FemALe")));
	ASSERT_FALSE(Validator::validateGender(std::string("emale")));
	ASSERT_FALSE(Validator::validateGender(std::string("OTHEr")));
}

TEST(TestValidator, Test_validateNum) {
	ASSERT_TRUE(Validator::validateNum("1"));
	ASSERT_TRUE(Validator::validateNum("8"));
	ASSERT_TRUE(Validator::validateNum("16"));
	ASSERT_FALSE(Validator::validateNum("Om"));
	ASSERT_FALSE(Validator::validateNum("@@"));
}

TEST(TestValidator, Test_validateReal) {
	ASSERT_TRUE(Validator::validateReal("1.00"));
	ASSERT_TRUE(Validator::validateReal("8.32"));
	ASSERT_TRUE(Validator::validateReal("16"));
	ASSERT_FALSE(Validator::validateReal("Om"));
	ASSERT_FALSE(Validator::validateReal("@@"));
}

TEST(TestValidator, Test_validateCharInput) {
	ASSERT_TRUE(Validator::validateCharInput('1'));
	ASSERT_TRUE(Validator::validateCharInput('0'));
	ASSERT_FALSE(Validator::validateCharInput('2'));
	ASSERT_FALSE(Validator::validateCharInput('a'));
	ASSERT_FALSE(Validator::validateCharInput('@'));
}
TEST(TestValidator, Test_validateInputMenu) {
	ASSERT_TRUE(Validator::validateInputMenu('1'));
	ASSERT_TRUE(Validator::validateInputMenu('5'));
	ASSERT_TRUE(Validator::validateInputMenu('0'));
	ASSERT_FALSE(Validator::validateInputMenu('7'));
	ASSERT_FALSE(Validator::validateInputMenu('6'));
	ASSERT_FALSE(Validator::validateInputMenu('8'));
	ASSERT_FALSE(Validator::validateInputMenu('9'));
	ASSERT_FALSE(Validator::validateInputMenu('a'));
	ASSERT_FALSE(Validator::validateInputMenu('@'));
}
TEST(TestValidator, Test_validateInputMainMenu) {
	ASSERT_TRUE(Validator::validateInputMainMenu('1'));
	ASSERT_TRUE(Validator::validateInputMainMenu('8'));
	ASSERT_TRUE(Validator::validateInputMainMenu('0'));
	ASSERT_FALSE(Validator::validateInputMainMenu('9'));
	ASSERT_FALSE(Validator::validateInputMainMenu('a'));
	ASSERT_FALSE(Validator::validateInputMainMenu('@'));
}
TEST(TestValidator, Test_validateInputView) {
	ASSERT_TRUE(Validator::validateInputView('1'));
	ASSERT_TRUE(Validator::validateInputView('0'));
	ASSERT_TRUE(Validator::validateInputView('2'));
	ASSERT_FALSE(Validator::validateInputView('3'));
	ASSERT_FALSE(Validator::validateInputView('a'));
	ASSERT_FALSE(Validator::validateInputView('@'));
}

TEST(TestValidator, Test_validateViewOfFields) {
	ASSERT_TRUE(Validator::validateViewOfFields("1"));
	ASSERT_TRUE(Validator::validateViewOfFields("7"));
	ASSERT_TRUE(Validator::validateViewOfFields("15"));
	ASSERT_FALSE(Validator::validateViewOfFields("0"));
	ASSERT_FALSE(Validator::validateViewOfFields("18"));
	ASSERT_FALSE(Validator::validateViewOfFields("ab"));
	ASSERT_FALSE(Validator::validateViewOfFields("1235"));
	ASSERT_FALSE(Validator::validateViewOfFields("@$"));
}

TEST(TestValidator, Test_validateUpdate) {
	ASSERT_TRUE(Validator::validateUpdate("1"));
	ASSERT_TRUE(Validator::validateUpdate("6"));
	ASSERT_TRUE(Validator::validateUpdate("13"));
	ASSERT_FALSE(Validator::validateUpdate("0"));
	ASSERT_FALSE(Validator::validateUpdate("16"));
	ASSERT_FALSE(Validator::validateUpdate("abc"));
	ASSERT_FALSE(Validator::validateUpdate("745"));
	ASSERT_FALSE(Validator::validateUpdate("$@"));
}

TEST(TestValidator, Test_validateDeptUpdate) {
	ASSERT_TRUE(Validator::validateDeptUpdate("1"));
	ASSERT_TRUE(Validator::validateDeptUpdate("2"));
	ASSERT_TRUE(Validator::validateDeptUpdate("3"));
	ASSERT_FALSE(Validator::validateDeptUpdate("0"));
	ASSERT_FALSE(Validator::validateDeptUpdate("5"));
	ASSERT_FALSE(Validator::validateDeptUpdate("abcd"));
	ASSERT_FALSE(Validator::validateDeptUpdate("412"));
	ASSERT_FALSE(Validator::validateDeptUpdate("@$"));
}

TEST(TestValidator, Test_validateViewOfDeptFields) {
	ASSERT_TRUE(Validator::validateViewOfDeptFields("1"));
	ASSERT_TRUE(Validator::validateViewOfDeptFields("3"));
	ASSERT_TRUE(Validator::validateViewOfDeptFields("5"));
	ASSERT_FALSE(Validator::validateViewOfDeptFields("0"));
	ASSERT_FALSE(Validator::validateViewOfDeptFields("7"));
	ASSERT_FALSE(Validator::validateViewOfDeptFields("abcd"));
	ASSERT_FALSE(Validator::validateViewOfDeptFields("515"));
	ASSERT_FALSE(Validator::validateViewOfDeptFields("$@"));
}

TEST(TestValidator, Test_validateManUpdate) {
	ASSERT_TRUE(Validator::validateManUpdate("1"));
	ASSERT_TRUE(Validator::validateManUpdate("8"));
	ASSERT_TRUE(Validator::validateManUpdate("16"));
	ASSERT_FALSE(Validator::validateManUpdate("0"));
	ASSERT_FALSE(Validator::validateManUpdate("18"));
	ASSERT_FALSE(Validator::validateManUpdate("abcd"));
	ASSERT_FALSE(Validator::validateManUpdate("7852"));
	ASSERT_FALSE(Validator::validateManUpdate("@$"));
}

TEST(TestValidator, Test_validateViewOfManFields) {
	ASSERT_TRUE(Validator::validateViewOfManFields("1"));
	ASSERT_TRUE(Validator::validateViewOfManFields("9"));
	ASSERT_TRUE(Validator::validateViewOfManFields("18"));
	ASSERT_FALSE(Validator::validateViewOfManFields("0"));
	ASSERT_FALSE(Validator::validateViewOfManFields("20"));
	ASSERT_FALSE(Validator::validateViewOfManFields("abcd"));
	ASSERT_FALSE(Validator::validateViewOfManFields("7541"));
	ASSERT_FALSE(Validator::validateViewOfManFields("@$"));
}

TEST(TestValidator, Test_validatecsvInput) {
	ASSERT_TRUE(Validator::validatecsvInput('0'));
	ASSERT_TRUE(Validator::validatecsvInput('5'));
	ASSERT_TRUE(Validator::validatecsvInput('9'));
	ASSERT_FALSE(Validator::validatecsvInput('h'));
	ASSERT_FALSE(Validator::validatecsvInput('@'));
}

TEST(TestValidator, Test_validateCreateMenu) {
	ASSERT_TRUE(Validator::validateCreateMenu('0'));
	ASSERT_TRUE(Validator::validateCreateMenu('2'));
	ASSERT_TRUE(Validator::validateCreateMenu('3'));
	ASSERT_FALSE(Validator::validateCreateMenu('5'));
	ASSERT_FALSE(Validator::validateCreateMenu('9'));
	ASSERT_FALSE(Validator::validateCreateMenu('a'));
	ASSERT_FALSE(Validator::validateCreateMenu('@'));
}