#include "ViewQA.h"
#include "Common.h"
#include "QAController.h"

void EmployeeDB::Console::QAMenu() noexcept {
	inputForEnt("QA");
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
		q.setTestingTool(mandatoryWithoutValidation("testingTool", "testingTool is mandatory...Please enter again!!"));
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::QAController::insertQA(q);
	if (DbSuccess) {}
	else {
		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
		std::cin.get();
		return false;
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
		std::cout << "\x1B[36mEnter the field which you want to update(1-13): \033[0m";

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
					if (EmployeeDB::Validator::validateUpdate(input)) {
						if (std::stoi(input) == 13) {
							q.setTestingTool(mandatoryWithoutValidation("testingTool", "testingTool is mandatory...Please enter again!!"));
						}
						else {
							updateEmp(input, q);
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "\x1B[31mPlease enter valid input in the given range(1-13)...\033[0m\n";
						x = false;

						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
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
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				return false; //For Menu OF Enginner 			
			}
			break;
		}
		case '2': {
			while (true) {
				printEmpFieldsWithID("QA");
				std::cout << "\x1B[36mSelect the field using which you want to view the Employee details(1-15): \033[0m";
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
						if (EmployeeDB::Validator::validateViewOfFields(inputField)) {
							if (inputField == "15") {
								arg1 = "testingTool";
								while (true) {
									std::string inputField;
									std::cout << "Enter the testingTool: ";
									std::getline(std::cin, inputField);
									inputField = trim(inputField);
									if (inputField.size() == 0) {
										std::cerr << "\x1B[31mThe input can not be empty...Please enter something\033[0m\n";
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
			DBSuccess = EmployeeDB::Controller::QAController::selectQA(arg1, arg2);
			if (DBSuccess) {}
			else {
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
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
