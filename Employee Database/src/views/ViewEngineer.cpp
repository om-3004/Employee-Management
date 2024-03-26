#include"../../include/views/ViewEngineer.h"
#include "../../include/views/Common.h"
#include "../../include/controller/EngineerController.h"

void EmployeeDB::Console::inEngineer() {
	while (true) {
		std::cout << "0. Quit\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "Please select operation which you want to perform on Engineer: ";

		char input;
		input = std::cin.get();
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

			operationOfEng(input);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Please enter valid input in the given range(0-5)\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
	}
}

void EmployeeDB::Console::operationOfEng(const char& input) {
	bool repeat{ true };
	switch (input) {
	case '0':
		std::exit(0);
	case '1': {
		while (repeat) {
			repeat = insertEngineer();
			system("cls");
		}
		break;
	}
	case '2': {
		while (repeat) {
			repeat = updateEngineer();
			system("cls");
		}
		break;
	}
	case '3': {
		while (repeat) {
			repeat = deleteEngineer();
			system("cls");
		}
		break;
	}
	case '4': {
		while (repeat) {
			repeat = viewEngineer();
			system("cls");
		}
		break;
	}
	}
}

bool EmployeeDB::Console::insertEngineer() {
	EmployeeDB::Model::Engineer e;

	char input;

	bool x = insertOperation(input, "Engineer");
	if (!x) {
		return false;
	}
	else {
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
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::EngineerController::insertEngineer(e);
	if (DbSuccess) {
		std::cout << "Employee Entered Successfully\n";
	}
	else {
		std::cout << "Please enter to continue...\n";
		std::cin.get();
		return false; //For Menu OF Enginner 
		//return true; //for again show insert option
	}

	if (repeatOperation("insert", "Engineer")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateEngineer() {
	EmployeeDB::Model::Engineer e{ false };

	int id = inputID("update", "Engineer");

	if (id == 0) {
		return false;
	}

	e.setEmployeeID(id);
	bool DBSuccess;

	while (true) {
		DBSuccess = EmployeeDB::Controller::EngineerController::selectEngineer("employeeID", std::to_string(id));
		std::cout << "\n";
		printEmpFields("Engineer");
		std::cout << "Enter the field which you want to update(1-13): ";
		bool x{ true };
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
					if (EmployeeDB::Validator::validateUpdate(input)) {
						if (std::stoi(input) == 13) {
							while (true) {
								std::string inputField;
								std::cout << "technology: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									e.setTechnology(inputField);
									break;
								}
							}
						}
						else {
							updateEmp(input, e);
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "Please enter valid input in the given range(1-13)\n";
						x = false;

						std::cout << "Press enter to continue...\n";
						std::cin.get();
						system("cls");
						break;
					}
				}
			}
			break;
		}

		bool y = repeatUpdateField(x);
		if (!y) {
			break;
		}
	}

	DBSuccess = EmployeeDB::Controller::EngineerController::updateEngineer(e);

	if (DBSuccess) {
		if (repeatOperation("update", "Engineer")) {
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

bool EmployeeDB::Console::deleteEngineer() {

	EmployeeDB::Model::Engineer e;

	int id = inputID("delete", "Engineer");

	if (id == 0) {
		return false;
	}

	bool DBSuccess;
	DBSuccess = EmployeeDB::Controller::EngineerController::selectEngineer("employeeID", std::to_string(id));

	if (!dltConfirmation(id, "Engineer")) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "Engineer")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewEngineer() {
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
			//Logic to send an object
			DBSuccess = EmployeeDB::Controller::EngineerController::selectEngineer();
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
				printEmpFieldsWithID("Engineer");
				std::cout << "Select the field using which you want to view the Employee details(1-15): ";
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
						std::string input = a + str;
						if (EmployeeDB::Validator::validateViewOfFields(input)) {
							if (input == "15") {
								arg1 = "technology";
								while (true) {
									std::string inputField;
									std::cout << "Enter the technology: ";
									std::getline(std::cin, inputField);
									inputField = trim(inputField);
									if (inputField.size() == 0) {
										std::cout << "The input can not be empty...Please enter something\n";
									}
									else {
										arg2 = inputField;
										break;
									}
								}
							}
							else {
								matchInpField(input, arg1, arg2);
							}
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
			// logic
			bool DBSuccess;
			DBSuccess = EmployeeDB::Controller::EngineerController::selectEngineer(arg1, arg2);
			if (DBSuccess) {}
			else {
				std::cout << "Press enter to continue...";
				std::cin.get();
				return false;
			}
			break;
		}
		}
	}
	if (repeatOperation("view", "Engineer")) {
		return true;
	}
	else {
		return false;
	}
}