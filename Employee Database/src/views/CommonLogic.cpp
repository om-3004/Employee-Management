#include<iostream>
#include"../../include/views/ViewEngineer.h"
#include "../../include/Validator.h"

void printEmpFields() {
	std::cout << "1. firstName*: " << '\n';
	std::cout << "2. middleName: " << '\n';
	std::cout << "3. lastName*: " << '\n';
	std::cout << "4. dateOfBirth: " << '\n';
	std::cout << "5. mobileNo*: " << '\n';
	std::cout << "6. email*:" << '\n';
	std::cout << "7. address*:" << '\n';
	std::cout << "8. gender*:" << '\n';
	std::cout << "9. dateOfJoining*:" << '\n';
	/*std::cout << "10. departmentID*:" << '\n';*/
	std::cout << "10. mentorID*:" << '\n';
	std::cout << "11. performanceMetric:" << '\n';
	std::cout << "12. bonus:" << '\n';
}

void printEmpFieldsWithID() {
	std::cout << "1. employee ID*:" << '\n';
	std::cout << "2. firstName*: " << '\n';
	std::cout << "3. middleName: " << '\n';
	std::cout << "4. lastName*: " << '\n';
	std::cout << "5. dateOfBirth: " << '\n';
	std::cout << "6. mobileNo*: " << '\n';
	std::cout << "7. email*:" << '\n';
	std::cout << "8. address*:" << '\n';
	std::cout << "9. gender*:" << '\n';
	std::cout << "10. dateOfJoining*:" << '\n';
	std::cout << "11. departmentID*:" << '\n';
	std::cout << "12. mentorID*:" << '\n';
	std::cout << "13. performanceMetric:" << '\n';
	std::cout << "14. bonus:" << '\n';
}

void askUserInput(EmployeeDB::Model::Employee& e) {
	std::string inputField;

	std::cin.ignore();
	while (true) {
		std::cout << "firstName*: ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "First Name is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;

			e.setFirstName(inputField);
			break;
		}
	}

	{
		std::cout << "middleName: ";
		char a = std::cin.get();

		if (a == '\n') {}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			e.setMiddleName(inputField);
		}
	}

	while (true) {
		std::cout << "lastName*: ";
		char a = std::cin.get();

		if (a == '\n') {
			std::cout << "Last Name is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;

			e.setLastName(inputField);
			break;
		}
	}


	while (true) {
		std::cout << "dateOfBirth(dd-mm-yyyy or dd/mm/yyyy or dd.mm.yyyy): ";
		char a = std::cin.get();

		if (a == '\n') { break; }
		else
		{
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			if (EmployeeDB::Validator::validateDate(inputField)) {
				e.setDateOfBirth(inputField);
				break;
			}
			else {
				std::cerr << "Wrong input...Please enter again!!\n";
			}
		}
	}

	while (true) {
		std::cout << "mobileNo*(Starting from 6-9): ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "mobileNo is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			if (EmployeeDB::Validator::validateMobile(inputField)) {
				e.setMobileNo(std::stoll(inputField));
				break;
			}
			else {
				std::cerr << "Wrong input...Please enter again!!\n";
			}
		}
	}

	while (true) {
		std::cout << "email*: ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "email is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			if (EmployeeDB::Validator::validateEmail(inputField)) {
				e.setEmail(inputField);
				break;
			}
			else {
				std::cerr << "Wrong input...Please enter again!!\n";
			}
		}
	}

	while (true) {
		std::cout << "address*: ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "Address is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;

			e.setAddress(inputField);
			break;
		}
	}

	while (true) {
		std::cout << "gender*: ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "Gender is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;

			int x = EmployeeDB::Validator::validateGender(inputField);
			if (x == 1) {
				e.setGender(EmployeeDB::Model::Gender::Male);
				break;
			}
			else if (x == 2) {
				e.setGender(EmployeeDB::Model::Gender::Female);
				break;
			}
			else if (x == 3) {
				e.setGender(EmployeeDB::Model::Gender::Other);
				break;
			}
			else {
				std::cerr << "Wrong input...Please enter again!!\n";
			}
		}
	}

	while (true) {
		std::cout << "dateOfJoining*(dd-mm-yyyy or dd/mm/yyyy or dd.mm.yyyy): ";
		char a = std::cin.get();

		if (a == '\n') {
			std::cout << "DOJ is mandatory...Please enter again!!" << '\n';
		}
		else
		{
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			if (EmployeeDB::Validator::validateDate(inputField)) {
				e.setDateOfJoining(inputField);
				break;
			}
			else {
				std::cerr << "Wrong input...Please enter again!!\n";
			}
		}

	}

	while (true) {
		std::cout << "mentorID*: ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "mentorID is mandatory...Please enter again!!" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			try {
				e.setMentorID(std::stoi(inputField));
			}
			catch (...) {
				std::cout << "Wrong input...Please enter integer!!\n";
				continue;
			}
			break;
		}
	}

	while (true) {
		std::cout << "performanceMetric: ";
		char a = std::cin.get();
		if (a == '\n') { break; }
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			try {
				e.setPerformanceMetric(std::stod(inputField));
			}
			catch (...) {
				std::cout << "Wrong input...Please enter integer!!\n";
				continue;
			}
			break;
		}
	}

	while (true) {
		std::cout << "bonus: ";
		char a = std::cin.get();
		if (a == '\n') { break; }
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			inputField = a + ans;
			try {
				e.setBonus(std::stoi(inputField));
			}
			catch (...) {
				std::cout << "Wrong input...Please enter integer!!\n";
				continue;
			}
			break;
		}
	}

}

std::string checkInput(const std::string& s) {
	std::string str;
	while (true) {
		std::cout << "Enter the " + s + ": ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "The input can not be empty...Please enter something" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			str = a + ans;
			break;
		}
	}
	return str;
}

void matchInpField(const std::string& inputField, std::string& arg1, std::string& arg2) {
	switch (std::stoi(inputField)) {
	case 1: {
		while (true) {
			arg1 = "employeeID";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] int a = std::stoi(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter integer value...\n";
			}
		}
		break;
	}
	case 2: {
		arg1 = "firstName";
		arg2 = checkInput(arg1);
		break;
	}
	case 3: {
		arg1 = "middleName";
		arg2 = checkInput(arg1);
		break;
	}
	case 4: {
		arg1 = "lastName";
		arg2 = checkInput(arg1);
		break;
	}
	case 5: {
		while (true) {
			arg1 = "dateOfBirth";
			arg2 = checkInput(arg1);
			if (EmployeeDB::Validator::validateDate(arg2)) {
				break;
			}
			else {
				std::cout << "Wrong input...Please enter again!!\n";
			}
		}
		break;
	}
	case 6: {
		while (true) {
			arg1 = "mobileNo";
			arg2 = checkInput(arg1);
			if (EmployeeDB::Validator::validateMobile(arg2)) {
				break;
			}
			else {
				std::cout << "Wrong input...Please enter again!!\n";
			}
		}
		break;
	}
	case 7: {
		while (true) {
			arg1 = "email";
			arg2 = checkInput(arg1);
			if (EmployeeDB::Validator::validateEmail(arg2)) {
				break;
			}
			else {
				std::cout << "Wrong input...Please enter again!!\n";
			}
		}
		break;
	}
	case 8: {
		arg1 = "address";
		arg2 = checkInput(arg1);
		break;
	}
	case 9: {
		while (true) {
			arg1 = "gender";
			arg2 = checkInput(arg1);
			if (EmployeeDB::Validator::validateGender(arg2) != -1) {
				break;
			}
			else {
				std::cout << "Wrong input...Please enter again!!\n";
			}
		}
		break;
	}
	case 10: {
		while (true) {
			arg1 = "dateOfJoining";
			arg2 = checkInput(arg1);
			if (EmployeeDB::Validator::validateDate(arg2)) {
				break;
			}
			else {
				std::cout << "Wrong input...Please enter again!!\n";
			}
		}
		break;
	}
	case 11: {
		while (true) {
			arg1 = "departmentID";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] int a = std::stoi(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter integer value...\n";
			}
		}
		break;
	}
	case 12: {
		while (true) {
			arg1 = "mentorID";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] int a = std::stoi(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter integer value...\n";
			}
		}
		break;
	}
	case 13: {
		while (true) {
			arg1 = "performanceMetric";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter numeric value...\n";
			}
		}
		break;
	}
	case 14: {
		while (true) {
			arg1 = "bonus";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter numeric value...\n";
			}
		}
		break;
	}
	default: {
		std::cout << "Invalid input...Please enter input in correct range!!\n";
	}
	}
}

void updateEmp(const std::string& input, EmployeeDB::Model::Employee& e) {
	switch (std::stoi(input)) {
	case 1:
	{
		while (true) {
			std::cout << "firstName: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				e.setFirstName(inputField);
				break;
			}
		}
		break;
	}
	case 2:
	{
		while (true) {
			std::cout << "middleName: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				e.setMiddleName(inputField);
				break;
			}
		}
		break;
	}
	case 3:
	{
		while (true) {
			std::cout << "lastName: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				e.setLastName(inputField);
				break;
			}
		}
		break;
	}
	case 4:
	{
		while (true) {
			std::cout << "dateOfBirth: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				if (EmployeeDB::Validator::validateDate(inputField)) {
					e.setDateOfBirth(inputField);
				}
				else {
					std::cout << "Please enter valid input...\n";
					continue;
				}

				break;
			}
		}
		break;
	}
	case 5:
	{
		while (true) {
			std::cout << "mobileNo: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				if (EmployeeDB::Validator::validateMobile(inputField)) {
					e.setMobileNo(std::stoll(inputField));
				}
				else {
					std::cout << "Please enter valid input...\n";
					continue;
				}
				break;
			}
		}
		break;
	}
	case 6:
	{
		while (true) {
			std::cout << "email: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				if (EmployeeDB::Validator::validateEmail(inputField)) {
					e.setEmail(inputField);
				}
				else {
					std::cout << "Please enter valid input...\n";
					continue;
				}
				break;
			}
		}
		break;
	}
	case 7:
	{
		while (true) {
			std::cout << "address: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				e.setAddress(inputField);
				break;
			}
		}
		break;
	}
	case 8:
	{
		while (true) {
			std::cout << "gender: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				if (EmployeeDB::Validator::validateGender(inputField) == 1) {
					e.setGender(EmployeeDB::Model::Gender::Male);
				}
				else if (EmployeeDB::Validator::validateGender(inputField) == 2) {
					e.setGender(EmployeeDB::Model::Gender::Female);
				}
				else if (EmployeeDB::Validator::validateGender(inputField) == 3) {
					e.setGender(EmployeeDB::Model::Gender::Other);
				}
				else {
					std::cout << "Please enter valid input...\n";
					continue;
				}
				break;
			}
		}
		break;
	}
	case 9:
	{
		while (true) {
			std::cout << "dateOfJoining: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				if (EmployeeDB::Validator::validateDate(inputField)) {
					e.setDateOfJoining(inputField);
				}
				else {
					std::cout << "Please enter valid input...\n";
					continue;
				}

				break;
			}
		}
		break;
	}
	case 10:
	{
		while (true) {
			std::cout << "mentorID: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				try {
					e.setMentorID(std::stoi(inputField));
				}
				catch (...) {
					std::cout << "Please enter a numeric value...\n";
					continue;
				}
				break;
			}
		}
		break;
	}
	case 11:
	{
		while (true) {
			std::cout << "performanceMetric: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				try {
					e.setPerformanceMetric(std::stod(inputField));
				}
				catch (...) {
					std::cout << "Please enter a numeric value...\n";
					continue;
				}
				break;
			}
		}
		break;
	}
	case 12: {
		while (true) {
			std::cout << "bonus: ";
			char a = std::cin.get();
			if (a == '\n') {
				std::cout << "It cannot be empty!!" << '\n';
			}
			else {
				std::string ans{ "" };
				std::getline(std::cin, ans);
				std::string inputField = a + ans;
				try {
					e.setBonus(std::stoi(inputField));
				}
				catch (...) {
					std::cout << "Please enter a numeric value...\n";
					continue;
				}
				break;
			}
		}
		break;
	}
	}
}
