#include "../include/Validator.h"
using EmployeeDB::Validator;
#include <iostream>

bool Validator::validateEmail(const std::string& email) {
	return std::regex_match(email, std::regex("(^[a-zA-Z0-9\\.]+@([a-zA-Z0-9]+\\.)+[a-zA-Z0-9]{2,4}$)"));
}

bool Validator::validateMobile(const std::string& number) {
	return std::regex_match(number, std::regex("(^[6-9]{1}[0-9]{9}$)"));
}

bool Validator::validateDate(const std::string& date) {
	return std::regex_match(date, std::regex(R"(^(?:(?:31(\/|-|\.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(\/|-|\.)(?:0?[13-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{2})$|^(?:29(\/|-|\.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(\/|-|\.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{2})$)"));
}

int Validator::validateGender(const std::string& gender) {
	if (gender == "male" || gender == "Male") {
		return 1;
	}
	else if (gender == "female" || gender == "Female") {
		return 2;
	}
	else if (gender == "other" || gender == "Other") {
		return 3;
	}
	else {
		return -1;
	}
}

//--------------------------------------------------------------------------------------------------------------------------//

//this is for validation of yes or no using char 
bool Validator::validateCharInput(char& in) {
	return std::regex_match(std::to_string(in), std::regex("(^(4[8|9]{1})$)"));
}
//--------------------------------------------------------------------------------------------------------------------------//

//this is for validation of input in main menu
bool Validator::validateInputMainMenu(char& in) {
	return std::regex_match(std::to_string(in), std::regex("(^(4[8|9]{1}|5[0|1|2|3|4]{1})$)"));
}
//this is for validation of input in other menu like insert , update ,delete , view  
bool Validator::validateInputMenu(char& in) {
	return std::regex_match(std::to_string(in), std::regex("(^(4[8|9]{1}|5[0|1|2|3]{1})$)"));
}

//--------------------------------------------------------------------------------------------------------------------------//

//check input for engineer , qa , finance , hr in update function
bool Validator::validateUpdate(std::string& in) {
	return std::regex_match(in, std::regex("(^(1[0-3]|[1-9])$)"));
}
//check input for Manager in update function
bool Validator::validateManUpdate(std::string& in) {
	return std::regex_match(in, std::regex("(^(1[0-6]|[1-9])$)"));
}
//check input for department in update function
bool Validator::validateDeptUpdate(std::string& in) {
	return std::regex_match(in, std::regex("(^([1-3]{1})$)"));
}

//--------------------------------------------------------------------------------------------------------------------------//

//This is for starting view check in all view 
bool Validator::validateInputView(char& in) {
	return std::regex_match(std::to_string(in), std::regex("(^4[8-9]|50$)"));
}
//check input for engineer , qa , finance , hr view after validateInputView for selecting field vise view
bool Validator::validateViewOfFields(std::string& in) {
	return std::regex_match(in, std::regex("(^(1[0-5]|[1-9])$)"));
}
//check input for Managerview after validateInputView for selecting field vise view
bool Validator::validateViewOfManFields(std::string& in) {
	return std::regex_match(in, std::regex("(^(1[0-8]|[1-9])$)"));
}
//check input for department after validateInputView for selecting field vise view
bool Validator::validateViewOfDeptFields(std::string& in) {
	return std::regex_match(in, std::regex("(^([1-5]{1})$)"));
}