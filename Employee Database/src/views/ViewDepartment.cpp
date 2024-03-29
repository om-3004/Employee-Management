#include"../../include/views/ViewDepartment.h"
#include "../../include/controller/DepartmentController.h"
#include "../../include/views/Common.h"

void EmployeeDB::Console::departmentMenu() noexcept {
	inputForEnt("Department");
}

void EmployeeDB::Console::operationOfDept(const char& input) noexcept {
	bool repeat{ true };
	switch (input) {
	case '0':
		std::exit(0);
	case '1': {
		while (repeat) {
			repeat = insertDept();
			system("cls");
		}
		break;
	}
	case '2': {
		while (repeat) {
			repeat = updateDept();
			system("cls");
		}
		break;
	}
	case '3': {
		while (repeat) {
			repeat = deleteDept();
			system("cls");
		}
		break;
	}
	case '4': {
		while (repeat) {
			repeat = viewDept();
			system("cls");
		}
		break;
	}
	}
}

bool EmployeeDB::Console::insertDept() {
	EmployeeDB::Model::Department d;
	char input;

	bool x = insertOperation(input, "Department");
	if (!x) {
		return false;
	}
	else {
		std::cin.ignore();
		d.setDepartmentName(mandatoryWithoutValidation("departmentName", "departmentName is mandatory...Please enter again!!"));
		d.setBaseSalary(std::stod(mandatoryWithValidation("baseSalary", "baseSalary is mandatory...Please enter again!!", EmployeeDB::Validator::validateReal)));
		d.setAllowance(std::stod(mandatoryWithValidation("allowance", "allowance is mandatory...Please enter again!!", EmployeeDB::Validator::validateReal)));
		d.setDeduction(std::stod(mandatoryWithValidation("deduction", "deduction is mandatory...Please enter again!!", EmployeeDB::Validator::validateReal)));
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::DepartmentController::insertDepartment(d);
	if (DbSuccess) {
		//std::cout << "Department Entered Successfully\n";
	}
	else {
		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
		std::cin.get();
		return false; //For Menu OF Enginner 
		//return true; //for again show insert option
	}

	if (repeatOperation("insert", "Department")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateDept() {
	EmployeeDB::Model::Department d(true);
	bool x{ true };

	int id = inputID("update", "Department");

	if (id == 0) {
		return false;
	}

	d.setDepartmentID(id);
	bool DBSuccess;

	while (true) {
		DBSuccess = EmployeeDB::Controller::DepartmentController::selectDepartment("departmentID", std::to_string(id));
		std::cout << "1. baseSalary*: \n";
		std::cout << "2. allowance*: \n";
		std::cout << "3. deduction*: \n";
		std::cout << "\x1B[36mEnter the field which you want to update(1-3): \033[0m";

		while (true) {
			char a = std::cin.get();
			if (a == '\n') {
				std::cin.clear();
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";

				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				system("cls");

				x = false;
			}
			else {
				std::string str;
				std::getline(std::cin, str);
				std::string input = a + str;

				while (true) {
					if (EmployeeDB::Validator::validateDeptUpdate(input)) {

						if (std::stoi(input) == 1) {
							d.setBaseSalary(std::stod(mandatoryWithValidation("baseSalary", "baseSalary is mandatory...Please enter again!!", EmployeeDB::Validator::validateReal)));
						}
						else if (std::stoi(input) == 2) {
							d.setAllowance(std::stod(mandatoryWithValidation("allowance", "allowance is mandatory...Please enter again!!", EmployeeDB::Validator::validateReal)));
						}
						else if (std::stoi(input) == 3) {
							d.setDeduction(std::stod(mandatoryWithValidation("deduction", "deduction is mandatory...Please enter again!!", EmployeeDB::Validator::validateReal)));
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "\x1B[31mPlease enter valid input in the given range(1-3)...\033[0m\n";
						x = false;

						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
						std::cin.get();
						system("cls");

						break;
					}
				}
				if (x)
					break;
			}
			break;
		}

		bool y = repeatUpdateField(x);
		if (!y) {
			break;
		}
	}
	DBSuccess = EmployeeDB::Controller::DepartmentController::updateDepartment(d);

	if (DBSuccess) {
		if (repeatOperation("update", "Department")) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}

bool EmployeeDB::Console::deleteDept() {
	EmployeeDB::Model::Department d;

	int id = inputID("delete", "Department");

	if (id == 0) {
		return false;
	}

	bool DBSuccess;
	DBSuccess = EmployeeDB::Controller::DepartmentController::selectDepartment("departmentID", std::to_string(id));

	if (!dltConfirmation(id, "Department")) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "Department")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewDept() {

	char input;
	bool x = viewOperation(input);
	if (!x) {
		return false;
	}
	else {
		std::string arg1, arg2;
		switch (input) {
		case '1': {
			bool DBSuccess;
			//	//Logic to send an object
			DBSuccess = EmployeeDB::Controller::DepartmentController::selectDepartment();
			if (DBSuccess) {}
			else {
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				return false; //For Menu OF Enginner 
			}
			break;
		}
		case '2': {
			while (true) {
				printEmpFieldsWithID("Department");
				std::cout << "\x1B[36mSelect the field using which you want to view the Employee details(1-5): \033[0m";
				char a;
				a = std::cin.get();
				if (a == '\n') {
					std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
					std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
					std::cin.get();
					system("cls");
				}
				else {
					bool x = true;
					while (true) {
						std::string str;
						std::getline(std::cin, str);
						std::string inputField = a + str;
						if (EmployeeDB::Validator::validateViewOfDeptFields(inputField)) {
							EmployeeDB::Console::matchInpFieldDept(inputField, arg1, arg2);
							x = true;
							break;
						}
						else {
							std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
							std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
							std::cin.get();
							system("cls");
							x = false;
							break;
						}
					}
					if (x)
						break;
				}
			}
			bool DBSuccess;
			//	//Logic to send an object
			DBSuccess = EmployeeDB::Controller::DepartmentController::selectDepartment(arg1, arg2);
			if (DBSuccess) {}
			else {
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				return false; //For Menu OF Enginner 
			}

			break;
		}
		}
	}

	if (repeatOperation("view", "Department")) {
		return true;
	}
	else {
		return false;
	}
}