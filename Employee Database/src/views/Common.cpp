#include "../../include/views/Common.h"
#include "../../include/controller/EmployeeController.h"
#include "../../include/controller/ManagerController.h"
#include "../../include/controller/DepartmentController.h"

void EmployeeDB::Console::inputForEnt(const std::string_view& ent) {
	while (true) {
		std::cout << "0. Quit\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "\x1B[36mPlease select operation which you want to perform on " << ent << ": \033[0m";

		char input;
		input = std::cin.get();
		if (input == '\n') {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			input = ' ';

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input in the given range(0-5)...\033[0m\n";

			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (EmployeeDB::Validator::validateInputMenu(input)) {

			system("cls");

			if (input == '0') {
				std::exit(0);
			}
			if (input == '5') {
				std::cin.clear();
				std::cin.ignore();
				return;
			}
			if (ent == "Department")
				operationOfDept(input);
			else if (ent == "Engineer")
				operationOfEng(input);
			else if (ent == "Finance")
				operationOfFin(input);
			else if(ent == "HR")
				operationOfHR(input);
			else if (ent == "Manager")
				operationOfMan(input);
			else if (ent == "QA")
				operationOfQA(input);

		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input in the given range(0-5)...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
	}
}

int EmployeeDB::Console::inputID(const std::string_view& op, const std::string_view& ent) {

	short int cnt = 0;
	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}

		std::cout << "\x1B[36mEnter 0 to GO BACK or enter the ID of the " << ent << " which you want to " << op << ": \033[0m";
		std::string in;
		std::getline(std::cin, in);
		if (in.size() == 0) {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";

			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else {
			try {
				int id = std::stoi(in);
				if (id == 0) {
					std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
					std::cin.get();
					system("cls");
					return 0;
				}
				if (EmployeeDB::Controller::EmployeeController::checkEmployeeExistence(std::to_string(id), ent)) {
					return id;
				}
				else {
					std::cerr << "\x1B[31mNo records found for the given emloyeeID...\033[0m\n";
				}
				//break;
			}
			catch (...) {
				std::cerr << "\x1B[31mPlease enter a numeric value...\033[0m\n";

				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				system("cls");
			}
		}
	}
}

void EmployeeDB::Console::printEmpFields(const std::string_view& empType) {
	if (empType == "Department") {
		std::cout << "1. departmentName*: \n";
		std::cout << "2. baseSalary*: \n";
		std::cout << "3. allowance*: \n";
		std::cout << "4. deduction*: \n";
	}
	else {
		std::cout << "1. firstName*: " << '\n';
		std::cout << "2. middleName: " << '\n';
		std::cout << "3. lastName*: " << '\n';
		std::cout << "4. dateOfBirth: " << '\n';
		std::cout << "5. mobileNo*: " << '\n';
		std::cout << "6. email*:" << '\n';
		std::cout << "7. address*:" << '\n';
		std::cout << "8. gender*:" << '\n';
		std::cout << "9. dateOfJoining*:" << '\n';
		std::cout << "10. mentorID*:" << '\n';
		std::cout << "11. performanceMetric:" << '\n';
		std::cout << "12. bonus:" << '\n';
		if (empType == "Engineer") {
			std::cout << "13. technology*:" << '\n';
		}
		else if (empType == "Finance") {
			std::cout << "13. accountingTool*:" << '\n';
		}
		else if (empType == "HR") {
			std::cout << "13. hrSpecialization*:" << '\n';
		}
		else if (empType == "QA") {
			std::cout << "13. testingTool*:" << '\n';
		}
		else if (empType == "Manager") {
			std::cout << "13. teamSize*:" << '\n';
			std::cout << "14. yearsOfExperince*:" << '\n';
			std::cout << "15. projectTitle*:" << '\n';
			std::cout << "16. role:" << '\n';
		}
	}
}

void EmployeeDB::Console::printEmpFieldsWithID(const std::string_view& empType) {
	if (empType == "Department") {
		std::cout << "1. Department ID*: \n";
		std::cout << "2. Department Name*: \n";
		std::cout << "3. Base Salaray*: \n";
		std::cout << "4. Allowance*: \n";
		std::cout << "5. Deduction*: \n";
	}
	else {
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

		if (empType == "Engineer") {
			std::cout << "15. technology*:" << '\n';
		}
		else if (empType == "Finance") {
			std::cout << "15. accountingTool*:" << '\n';
		}
		else if (empType == "HR") {
			std::cout << "15. hrSpecialization*:" << '\n';
		}
		else if (empType == "QA") {
			std::cout << "15. testingTool*:" << '\n';
		}
		else if (empType == "Manager") {
			std::cout << "15. teamSize*:" << '\n';
			std::cout << "16. yearsOfExperince*:" << '\n';
			std::cout << "17. projectTitle*:" << '\n';
			std::cout << "18. role:" << '\n';
		}
	}
}

bool EmployeeDB::Console::repeatUpdateField(bool& x) {
	if (x) {
		char in, nxt;
		while (true) {
			std::cout << "\x1B[36mDo you want to update another field?(0/1): \033[0m";
			in = std::cin.get();
			nxt = std::cin.peek();

			if (nxt != '\n') {
				in = ' ';
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "\x1B[31mPlease enter valid input...\033[0m\n";
			}

			if (Validator::validateCharInput(in)) {
				if (in == '1')
				{
					system("cls");
					std::cin.clear();
					std::cin.ignore();
				}
				break;
			}
			else {
				std::cout << "\x1B[31mPlease enter valid input...\033[0m\n";
			}
		}
		if (in == '0') {
			std::cin.clear();
			std::cin.ignore();
			return false;
		}
	}
	return true;
}

bool EmployeeDB::Console::dltConfirmation(const int& id, const std::string_view& ent)	 {
	while (true) {
		// fetch the row of the employee which is selected using the ID
		// bool DbSuccess{ false };
		//	//Logic to send an object
		//	DbSuccess = fun(int);

		std::cout << "\x1B[36mAre you sure you want to delete this employee(0/1): \033[0m";
		char confirm;
		confirm = std::cin.get();

		if (confirm == '\n') {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else if (std::cin.peek() != '\n') {
			confirm = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else if (EmployeeDB::Validator::validateCharInput(confirm)) {
			if (confirm == '1')
			{
				bool DbSuccess{ false };

				//Logic to send an object
				if (ent == "Manager")
					DbSuccess = EmployeeDB::Controller::ManagerController::deleteManagerByID(id);
				else if (ent == "Department")
					DbSuccess = EmployeeDB::Controller::DepartmentController::deleteDepartmentByID(id);
				else
					DbSuccess = EmployeeDB::Controller::EmployeeController::deleteEmployeeByID(id);

				if (DbSuccess) {
					return true;
				}
				else {
					std::cerr << "\x1B[31mCannot delete...\033[0m\n";
					return false;
				}
			}
			else {
				std::cin.ignore();
				return false;
			}

			break;
		}
		else {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
	}
	return true;
}

bool EmployeeDB::Console::repeatOperation(const std::string& op, const std::string& ent) {
	while (true) {
		char in;
		std::cout << "\x1B[36mDo you want to " + op + " another " + ent + "? (0/1): \033[0m";
		in = std::cin.get();

		if (in == '\n') {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else if (std::cin.peek() != '\n') {
			in = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else if (EmployeeDB::Validator::validateCharInput(in)) {
			if (in == '1') {
				return true;
			}
			else {
				std::cin.clear();
				std::cin.ignore();
				return false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
	}
}

std::string EmployeeDB::Console::trim(std::string str, const std::string chars) {
	if (str.size() == 0) {
		return str;
	}
	else {
		std::string tmp(str);
		tmp.erase(tmp.find_last_not_of(chars) + 1);
		tmp.erase(0, tmp.find_first_not_of(chars));

		std::string out_str;
		bool pre_space = false;
		int i = 0;
		while (i < tmp.size()) {
			if (tmp.at(i) != ' ') {
				if (pre_space) {
					out_str += ' ';
				}
				out_str += tmp.at(i);
				pre_space = false;
			}
			else {
				pre_space = true;
			}
			++i;
		}
		return out_str;
	}
}

//////////////////////
std::string EmployeeDB::Console::mandatoryWithValidation(const std::string& fieldName, const std::string& errMsg, bool (*validateField)(const std::string& validateStr)) {
	std::string inputField;
	while (true) {
		std::cout << fieldName<< "*: ";
		std::getline(std::cin, inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31m" << errMsg << "\033[0m\n";
		}
		else {
			inputField = trim(inputField);
			if (validateField(inputField)) {
				return inputField;
			}
			else {
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
			}
		}
	}
}

std::string EmployeeDB::Console::mandatoryWithoutValidation(const std::string& fieldName, const std::string& errMsg) {
	std::string inputField;
	while (true) {
		std::cout << fieldName << "*: ";
		std::getline(std::cin, inputField);
		inputField = trim(inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31m" << errMsg << "\033[0m\n";
		}
		else {
			return inputField;
		}
	}
}

std::string EmployeeDB::Console::nonMandatoryWithValidation(const std::string& fieldName, const std::string& errMsg, bool (*validateField)(const std::string& validateStr)) {
	std::string inputField;
	while (true) {
		std::cout << fieldName << ": ";
		std::getline(std::cin, inputField);
		if (inputField.size() == 0) {
			return "";
		}
		inputField = trim(inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31m" << errMsg << "\033[0m\n";
		}
		else {
			if (validateField(inputField)) {
				return inputField;
			}
			else {
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
			}
		}
	}
}

std::string EmployeeDB::Console::nonMandatoryWithoutValidation(const std::string& fieldName, const std::string& errMsg) {
	std::string inputField;
	while (true) {
		std::cout << fieldName << ": ";
		std::getline(std::cin, inputField);
		if (inputField.size() == 0) {
			return "";
		}
		inputField = trim(inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31m" << errMsg << "\033[0m\n";
		}
		else {
			return inputField;
		}
	}
}

void EmployeeDB::Console::askUserInput(EmployeeDB::Model::Employee& e) {
	std::cin.ignore();

	e.setFirstName(mandatoryWithValidation("firstName", "firstName is mandatory...Please enter again!!", EmployeeDB::Validator::validateName));
	e.setMiddleName(nonMandatoryWithValidation("middleName", "Please enter some valid input...", EmployeeDB::Validator::validateName));
	e.setLastName(mandatoryWithValidation("lastName", "lastName is mandatory...Please enter again!!", EmployeeDB::Validator::validateName));
	e.setDateOfBirth(nonMandatoryWithValidation("dateOfBirth(dd-mm-yyyy or dd/mm/yyyy or dd.mm.yyyy)", "Please enter some valid input...", EmployeeDB::Validator::validateDate));
	e.setMobileNo(std::stoll(mandatoryWithValidation("mobileNo", "mobileNo is mandatory...Please enter again!!", EmployeeDB::Validator::validateMobile)));
	e.setEmail(mandatoryWithValidation("email", "email is mandatory...Please enter again!!", EmployeeDB::Validator::validateEmail));
	e.setAddress(mandatoryWithoutValidation("address", "address is mandatory...Please enter again!!"));

	auto gen = mandatoryWithValidation("gender", "gender is mandatory...Please enter again!!", EmployeeDB::Validator::validateGender);
	if (gen == "male" || gen == "Male") {
		e.setGender(EmployeeDB::Model::Gender::Male);
	}
	else if (gen == "female" || gen == "Female") {
		e.setGender(EmployeeDB::Model::Gender::Female);
	}
	else {
		e.setGender(EmployeeDB::Model::Gender::Other);
	}

	e.setDateOfJoining(mandatoryWithValidation("dateOfJoining", "dateOfJoining is mandatory...Please enter again!!", EmployeeDB::Validator::validateDate));
	e.setMentorID(std::stoi(mandatoryWithValidation("mentorID", "mentorID is mandatory...Please enter again!!", EmployeeDB::Validator::validateNum)));
	if (nonMandatoryWithValidation("performanceMetric", "Wrong input...Please enter integer!!", EmployeeDB::Validator::validateReal).size() != 0) {
		e.setPerformanceMetric(std::stod(nonMandatoryWithValidation("performanceMetric", "Wrong input...Please enter integer!!", EmployeeDB::Validator::validateReal)));
	}
	if (nonMandatoryWithValidation("bonus", "Wrong input...Please enter integer!!", EmployeeDB::Validator::validateReal).size() != 0) {
		e.setBonus(std::stod(nonMandatoryWithValidation("bonus", "Wrong input...Please enter integer!!", EmployeeDB::Validator::validateReal)));
	}
}

///////////
std::string EmployeeDB::Console::checkInput(const std::string& s) {
	std::string inputField;
	while (true) {
		std::cout << "Enter the " + s + ": ";
		std::getline(std::cin, inputField);
		inputField = trim(inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31mThe input can not be empty...Please enter something\033[0m\n";
		}
		else {
			break;
		}
	}
	return inputField;
}

void EmployeeDB::Console::matchInpField(const std::string& inputField, std::string& arg1, std::string& arg2) {

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
				std::cerr << "\x1B[31mPlease enter integer value...\033[0m\n";
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
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
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
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
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
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
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
			if (EmployeeDB::Validator::validateGender(arg2) != false) {
				break;
			}
			else {
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
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
				std::cerr << "\x1B[31mWrong input...Please enter again!!\033[0m\n";
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
				std::cerr << "\x1B[31mPlease enter integer value...\033[0m\n";
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
				std::cerr << "\x1B[31mPlease enter integer value...\033[0m\n";
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
				std::cerr << "\x1B[31mPlease enter numeric value...\033[0m\n";
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
				std::cerr << "Please enter numeric value...\n";
			}
		}
		break;
	}
	default: {
		std::cerr << "\x1B[31mInvalid input...Please enter input in correct range!!\033[0m\n";
	}
	}
}

void EmployeeDB::Console::updateEmp(const std::string& input, EmployeeDB::Model::Employee& e) {
	switch (std::stoi(input)) {
	case 1:
	{
		e.setFirstName(mandatoryWithValidation("firstName", "firstName is mandatory...Please enter again!!", EmployeeDB::Validator::validateName));
		break;
	}
	case 2:
	{
		e.setMiddleName(mandatoryWithValidation("middleName", "Please enter some valid input...", EmployeeDB::Validator::validateName));
		break;
	}
	case 3:
	{
		e.setLastName(mandatoryWithValidation("lastName", "lastName is mandatory...Please enter again!!", EmployeeDB::Validator::validateName));
		break;
	}
	case 4:
	{
		e.setDateOfBirth(mandatoryWithValidation("dateOfBirth(dd-mm-yyyy or dd/mm/yyyy or dd.mm.yyyy)", "Please enter some valid input...", EmployeeDB::Validator::validateDate));
		break;
	}
	case 5:
	{
		e.setMobileNo(std::stoll(mandatoryWithValidation("mobileNo", "mobileNo is mandatory...Please enter again!!", EmployeeDB::Validator::validateMobile)));
		break;
	}
	case 6:
	{
		e.setEmail(mandatoryWithValidation("email", "email is mandatory...Please enter again!!", EmployeeDB::Validator::validateEmail));
		break;
	}
	case 7:
	{
		e.setAddress(mandatoryWithoutValidation("address", "address is mandatory...Please enter again!!"));
		break;
	}
	case 8:
	{
		auto gen = mandatoryWithValidation("gender", "gender is mandatory...Please enter again!!", EmployeeDB::Validator::validateGender);
		if (gen == "male" || gen == "Male") {
			e.setGender(EmployeeDB::Model::Gender::Male);
		}
		else if (gen == "female" || gen == "Female") {
			e.setGender(EmployeeDB::Model::Gender::Female);
		}
		else {
			e.setGender(EmployeeDB::Model::Gender::Other);
		}
		break;
	}
	case 9:
	{
		e.setDateOfJoining(mandatoryWithValidation("dateOfJoining", "dateOfJoining is mandatory...Please enter again!!", EmployeeDB::Validator::validateDate));
		break;
	}
	case 10:
	{
		e.setMentorID(std::stoi(mandatoryWithValidation("mentorID", "mentorID is mandatory...Please enter again!!", EmployeeDB::Validator::validateNum)));
		break;
	}
	case 11:
	{
		e.setPerformanceMetric(std::stod(mandatoryWithValidation("performanceMetric", "Wrong input...Please enter integer!!", EmployeeDB::Validator::validateReal)));
		break;
	}
	case 12: {
		e.setBonus(std::stod(mandatoryWithValidation("bonus", "Wrong input...Please enter integer!!", EmployeeDB::Validator::validateReal)));
		break;
	}
	}
}

void EmployeeDB::Console::matchInpFieldDept(const std::string& inputField, std::string& arg1, std::string& arg2) {
	switch (std::stoi(inputField)) {
	case 1: {
		while (true) {
			arg1 = "departmentID";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] int a = std::stoi(arg2);
				break;
			}
			catch (...) {
				std::cerr << "\x1B[31mPlease enter integer value...\033[0m\n";
			}
		}
		break;
	}
	case 2: {
		arg1 = "departmentName";
		arg2 = checkInput(arg1);
		break;
	}
	case 3: {
		while (true) {
			arg1 = "baseSalary";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cerr << "\x1B[31mPlease enter numeric value...\033[0m\n";
			}
		}
		break;
	}
	case 4: {
		while (true) {
			arg1 = "allowance";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cerr << "\x1B[31mPlease enter numeric value...\033[0m\n";
			}
		}
		break;
	}
	case 5: {
		while (true) {
			arg1 = "deduction";
			arg2 = checkInput(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cerr << "\x1B[31mPlease enter numeric value...\033[0m\n";
			}
		}
		break;
	}
	}
}

bool EmployeeDB::Console::viewOperation(char& input) {
	short int cnt = 0;
	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}
		std::cout << "0. Back\n";
		std::cout << "1. View whole table\n";
		std::cout << "2. View with the help of some field of the table\n";
		std::cout << "\x1B[36mEnter your choice(0-2): \033[0m";
		input = std::cin.get();

		if (input == '\n') {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.get() != '\n') {
			input = ' ';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else {
			if (EmployeeDB::Validator::validateInputView(input)) {
				if (input == '0') {
					return false;
				}
				else if (input == '1' || input == '2') {
					system("cls");
					return true;
				}
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cerr << "\x1B[31mPlease enter valid input in the given range(0-2)...\033[0m\n";
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				system("cls");
			}
		}
	}
}

bool EmployeeDB::Console::insertOperation(char& input, const std::string_view& empType) {
	short int cnt = 0;
	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}
		if (empType != "Manager")
			printEmpFields(empType);

		char a;
		std::cout << "\x1B[36mAre you sure you want to continue with the insert operation(0/1): \033[0m";
		a = std::cin.get();


		if (a == '\n') {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			a = ' ';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";

			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else {
			if (EmployeeDB::Validator::validateCharInput(a)) {
				if (a == '0') {
					std::cin.clear();
					std::cin.ignore();
					return false;
				}
				else {
					return true;
				}
				/*else if (a == '1') {
					askUserInput(e);
					while (true) {
						std::string inputField;
						std::cout << "technology*: ";
						std::getline(std::cin, inputField);
						inputField = trim(inputField);
						if (inputField.size() == 0) {
							std::cout << "technology is mandatory...Please enter again!!" << '\n';
						}
						else {
							e.setTechnology(inputField);
							break;
						}
					}
					break;
				}
				break;*/
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				system("cls");
			}
		}
	}
}
