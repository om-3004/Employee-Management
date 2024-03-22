#include"../../include/views/ViewFinance.h"
#include "../../include/views/Common.h"

void EmployeeDB::Console::inFinance() {
	while (true) {

		std::cout << "0. Quit\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "Please select operation which you want to perform on Finance: ";

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

			operationOfFin(input);
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
void EmployeeDB::Console::operationOfFin(const char& input) {
	bool repeat{ true };
	switch (input) {
	case '0':
		std::exit(0);
	case '1': {
		while (repeat) {
			repeat = insertInFinance();
			system("cls");
		}
		break;
	}
	case '2': {
		while (repeat) {
			repeat = updateInFinance();
			system("cls");
		}
		break;
	}
	case '3': {
		while (repeat) {
			repeat = deleteInFinance();
			system("cls");
		}
		break;
	}
	case '4': {
		while (repeat) {
			repeat = viewInFinance();
			system("cls");
		}
		break;
	}
	}
}
bool EmployeeDB::Console::insertInFinance() {
	EmployeeDB::Model::Finance f;

	char input;

	bool x = insertOperation(input, "finance");
	if (!x) {
		return false;
	}
	else {
		askUserInput(f);
		while (true) {
			std::string inputField;
			std::cout << "accountingTool*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "accountingTool is mandatory...Please enter again!!" << '\n';
			}
			else {
				f.setAccountingTool(inputField);
				break;
			}
		}
	}
	////{ ------------------LOGIC----------------------
	//	bool DbSuccess;
	//	//Logic to send an object
	//	DbSuccess = fun(e);
	//	if (DbSuccess) {
	//		std::cout << "Employee Entered SuccessFull\n";
	//	}
	//	else {
	//		return false; //For Menu OF Enginner 
	//		return true; //for again show insert option
	//	}
	//}


	if (repeatOperation("insert", "finance")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateInFinance() {
	EmployeeDB::Model::Finance f{ true };
	bool x{ true };
	// short int cnt = 0; //for cin.ignore() so it will only ignore once 

	int id = inputID("update", "employee");

	if (id == 0) {
		return false;
	}

	while (true) {
		printEmpFields("finance");
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
								std::cout << "accountingTool: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									f.setAccountingTool(inputField);
									break;
								}
							}
						}
						else {
							updateEmp(input, f);
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

	if (repeatOperation("update", "finance")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::deleteInFinance() {
	EmployeeDB::Model::Finance f;

	int id = inputID("delete", "finance");

	if (id == 0) {
		return false;
	}

	if (!dltConfirmation(id)) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "finance")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewInFinance() {

	char input;
	bool x = viewOperation(input);
	if (!x) {
		return false;
	}
	else {
		std::string arg1, arg2;
		switch (input) {
		case '1': {
			//	bool DbSuccess;
			//	//Logic to send an object
			//	DbSuccess = fun(int);
			//	if (DbSuccess) {
			//		std::cout << "Employee Entered SuccessFull\n";
			//	}
			//	else {
			//		return false; //For Menu OF Enginner 
			//		return true; //for again show insert option
			//	}
			break;
		}
		case '2': {
			while (true) {
				printEmpFieldsWithID("finance");
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
								arg1 = "accountingTool";
								//std::cin.ignore();
								while (true) {
									std::string inputField;
									std::cout << "Enter the accountingTool: ";
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
			// logic
			// bool success ;
			// success = fun(arg1,arg2);
			// if(success){
			// std::cout << "Successfull\n";
			// std::cin.clear();
			// std::cin.ignore();
			// break;
			//}
			//else{
			//  std::cout << "Database Error\n";
			//  std::cin.clear();
			//  std::cin.ignore();
			//  std::cout << "Press enter to continue...";
			//  std::cin.get();
			//  return false ;
			//}

			break;
		}
		}
	}

	if (repeatOperation("view", "finance")) {
		return true;
	}
	else {
		return false;
	}
}