#include "ViewFinance.h"
#include "Common.h"
#include "FinanceController.h"

void EmployeeDB::Console::financeMenu() noexcept {
	inputForEnt("Finance");
}

void EmployeeDB::Console::operationOfFin(const char& input) noexcept {
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

	bool x = insertOperation(input, "Finance");
	if (!x) {
		return false;
	}
	else {
		askUserInput(f);
		f.setAccountingTool(mandatoryWithoutValidation("accountingTool", "accountingTool is mandatory...Please enter again!!"));
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::FinanceController::insertFinance(f);
	if (DbSuccess) {
		//std::cout << "Employee Entered SuccessFull\n";
	}
	else {
		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
		std::cin.get();
		return false; //For Menu OF Enginner 
		//return true; //for again show insert option
	}


	if (repeatOperation("insert", "Finance")) {
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

	int id = inputID("Update", "Finance");

	if (id == 0) {
		return false;
	}
	f.setEmployeeID(id);
	bool DBSuccess;

	while (true) {
		DBSuccess = EmployeeDB::Controller::FinanceController::selectFinance("employeeID", std::to_string(id));
		printEmpFields("Finance");
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
							f.setAccountingTool(mandatoryWithoutValidation("accountingTool", "accountingTool is mandatory...Please enter again!!"));
						}
						else {
							updateEmp(input, f);
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

	DBSuccess = EmployeeDB::Controller::FinanceController::updateFinance(f);

	if (DBSuccess) {
		if (repeatOperation("update", "Finance")) {
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

bool EmployeeDB::Console::deleteInFinance() {
	EmployeeDB::Model::Finance f;

	int id = inputID("Delete", "Finance");

	if (id == 0) {
		return false;
	}

	bool DBSuccess;
	DBSuccess = EmployeeDB::Controller::FinanceController::selectFinance("employeeID", std::to_string(id));

	if (!dltConfirmation(id, "Finance")) {
		return false;
	}


	std::cin.ignore();
	if (repeatOperation("delete", "Finance")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewInFinance() {

	char input;
	bool x = viewOperation(input, "Finance");
	if (!x) {
		return false;
	}
	else {
		std::string arg1, arg2;
		switch (input) {
		case '1': {
			bool DBSuccess;
			//	//Logic to send an object
			DBSuccess = EmployeeDB::Controller::FinanceController::selectFinance();
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
				printEmpFieldsWithID("Finance");
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
								arg1 = "accountingTool";
								//std::cin.ignore();
								while (true) {
									std::string inputField;
									std::cout << "Enter the accountingTool: ";
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
			//	//Logic to send an object
			DBSuccess = EmployeeDB::Controller::FinanceController::selectFinance(arg1, arg2);
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

	if (repeatOperation("view", "Finance")) {
		return true;
	}
	else {
		return false;
	}
}
