#include"../../include/views/ViewDepartment.h"
#include "../../include/controller/DepartmentController.h"
#include "../../include/views/Common.h"

void EmployeeDB::Console::inDepartment() noexcept {

	while (true) {
		std::cout << "0. Quit\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "Please select operation which you want to perform on Department: ";

		char input = std::cin.get();

		if (input == '\n') {
			std::cout << "Please enter valid input...\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			input = ' ';

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Please enter valid input in the given range(0-5)...\n";

			std::cout << "Press enter to continue...\n";
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
			operationOfDept(input);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Please enter valid input in the given range(0-5)...\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
	}
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
		while (true) {
			std::string inputField;
			std::cout << "departmentName*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "departmentName is mandatory...Please enter again!!" << '\n';
			}
			else {
				d.setDepartmentName(inputField);
				break;
			}
		}
		while (true) {
			std::string inputField;
			std::cout << "baseSalary*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "baseSalary is mandatory...Please enter again!!" << '\n';
			}
			else {
				try {
					d.setBaseSalary(std::stod(inputField));
				}
				catch (...) {
					std::cerr << "Invalid input...Please enter numeric value!!\n";
					continue;
				}
				break;
			}
		}
		while (true) {
			std::string inputField;
			std::cout << "allowance*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "allowance is mandatory...Please enter again!!" << '\n';
			}
			else {
				try {
					d.setAllowance(std::stod(inputField));
				}
				catch (...) {
					std::cerr << "Invalid input...Please enter numeric value!!\n";
					continue;
				}
				break;
			}
		}
		while (true) {
			std::string inputField;
			std::cout << "deduction*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "deduction is mandatory...Please enter again!!" << '\n';
			}
			else {
				try {
					d.setDeduction(std::stod(inputField));
				}
				catch (...) {
					std::cerr << "Invalid input...Please enter numeric value!!\n";
					continue;
				}
				break;
			}
		}
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::DepartmentController::insertDepartment(d);
	if (DbSuccess) {
		std::cout << "Department Entered SuccessFull\n";
	}
	else {
		std::cout << "Please enter to continue...\n";
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
		std::cout << "Enter the field which you want to update(1-3): ";

		while (true) {
			char a = std::cin.get();
			if (a == '\n') {
				std::cin.clear();
				std::cout << "Please enter valid input...\n";

				std::cout << "Press enter to continue...\n";
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
							while (true) {
								std::string inputField;
								std::cout << "baseSalary: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									try {
										d.setBaseSalary(std::stod(inputField));
										break;
									}
									catch (...) {
										std::cout << "Wrong input...Please enter numeric value!!\n";
									}
								}
							}
						}

						else if (std::stoi(input) == 2) {
							while (true) {
								std::string inputField;
								std::cout << "allowance: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									try {
										d.setAllowance(std::stod(inputField));
										break;
									}
									catch (...) {
										std::cout << "Wrong input...Please enter numeric value!!\n";
									}
								}
							}
						}

						else if (std::stoi(input) == 3) {
							while (true) {
								std::string inputField;
								std::cout << "deduction: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									try {
										d.setDeduction(std::stod(inputField));
										break;
									}
									catch (...) {
										std::cout << "Wrong input...Please enter numeric value!!\n";
									}
								}
							}
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "Please enter valid input in the given range(1-3)\n";
						x = false;

						std::cout << "Press enter to continue...\n";
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
				std::cout << "Press enter to continue...";
				std::cin.get();
				return false; //For Menu OF Enginner 
			}
			break;
		}
		case '2': {
			while (true) {
				printEmpFieldsWithID("Department");
				std::cout << "Select the field using which you want to view the Employee details(1-5): ";
				char a;
				a = std::cin.get();
				if (a == '\n') {
					std::cout << "Please enter valid input...\n";
					std::cout << "Press enter to continue...\n";
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
							std::cout << "Please enter valid input...\n";
							std::cout << "Press enter to continue...\n";
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
				std::cout << "Press enter to continue...";
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