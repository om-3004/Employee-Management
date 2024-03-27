#include"../../include/views/ViewQA.h"
#include "../../include/views/Common.h"
#include "../../include/controller/QAController.h"

void EmployeeDB::Console::inQA() noexcept {
	while (true) {

		std::cout << "0. Quit\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "Please select operation which you want to perform on QA: ";

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

			operationOfQA(input);
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

void EmployeeDB::Console::operationOfQA(const char& input) noexcept {
	bool repeat{ true };
	switch (input) {
	case '0':
		std::exit(0);
	case '1': {
		while (repeat) {
			repeat = insertInQA();
			system("cls");
		}
		break;
	}
	case '2': {
		while (repeat) {
			repeat = updateInQA();
			system("cls");
		}
		break;
	}
	case '3': {
		while (repeat) {
			repeat = deleteInQA();
			system("cls");
		}
		break;
	}
	case '4': {
		while (repeat) {
			repeat = viewInQA();
			system("cls");
		}
		break;
	}
	}
}

bool EmployeeDB::Console::insertInQA() {
	EmployeeDB::Model::QA q;

	char input;

	bool x = insertOperation(input, "QA");
	if (!x) {
		return false;
	}
	else {
		askUserInput(q);
		while (true) {

			std::string inputField;
			std::cout << "testingTool*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "testingTool is mandatory...Please enter again!!" << '\n';
			}
			else {
				q.setTestingTool(inputField);
				break;
			}
		}
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::QAController::insertQA(q);
	if (DbSuccess) {
		std::cout << "Employee Entered SuccessFull\n";
	}
	else {
		std::cout << "Please enter to continue...\n";
		std::cin.get();
		return false; //For Menu OF Enginner 
		//return true; //for again show insert option
	}


	if (repeatOperation("insert", "QA")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateInQA() {
	EmployeeDB::Model::QA q{ true };
	bool x{ true };

	int id = inputID("update", "QA");

	if (id == 0) {
		return false;
	}

	q.setEmployeeID(id);
	bool DBSuccess;
	while (true) {
		DBSuccess = EmployeeDB::Controller::QAController::selectQA("employeeID", std::to_string(id));
		printEmpFields("QA");
		std::cout << "Enter the field which you want to update(1-13): ";

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
								std::cout << "testingTool: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									q.setTestingTool(inputField);
									break;
								}
							}
						}
						else {
							updateEmp(input, q);
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

	DBSuccess = EmployeeDB::Controller::QAController::updateQA(q);

	if (DBSuccess) {
		if (repeatOperation("update", "QA")) {
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

bool EmployeeDB::Console::deleteInQA() {
	EmployeeDB::Model::QA q;

	int id = inputID("delete", "QA");

	if (id == 0) {
		return false;
	}

	bool DBSuccess;
	DBSuccess = EmployeeDB::Controller::QAController::selectQA("employeeID", std::to_string(id));

	if (!dltConfirmation(id, "QA")) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "QA")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewInQA() {

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
			DBSuccess = EmployeeDB::Controller::QAController::selectQA(arg1, arg2);
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
				printEmpFieldsWithID("QA");
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
						std::string inputField = a + str;
						if (EmployeeDB::Validator::validateViewOfFields(inputField)) {
							if (inputField == "15") {
								arg1 = "testingTool";
								while (true) {
									std::string inputField;
									std::cout << "Enter the testingTool: ";
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
								matchInpField(inputField, arg1, arg2);
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

			bool DBSuccess;
			DBSuccess = EmployeeDB::Controller::QAController::selectQA(arg1, arg2);
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

	if (repeatOperation("view", "QA")) {
		return true;
	}
	else {
		return false;
	}
}
