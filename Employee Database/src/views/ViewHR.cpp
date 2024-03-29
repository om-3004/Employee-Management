#include"../../include/views/ViewHR.h"
#include "../../include/views/Common.h"
#include "../../include/controller/HRController.h"

void EmployeeDB::Console::HRMenu() noexcept {
	inputForEnt("HR");
}

void EmployeeDB::Console::operationOfHR(const char& input) noexcept {
	bool repeat{ true };
	switch (input) {
	case '0':
		std::exit(0);
	case '1': {
		while (repeat) {
			repeat = insertHR();
			system("cls");
		}
		break;
	}
	case '2': {
		while (repeat) {
			repeat = updateHR();
			system("cls");
		}
		break;
	}
	case '3': {
		while (repeat) {
			repeat = deleteHR();
			system("cls");
		}
		break;
	}
	case '4': {
		while (repeat) {
			repeat = viewHR();
			system("cls");
		}
		break;
	}
	}
}

bool EmployeeDB::Console::insertHR() {
	EmployeeDB::Model::HR h;

	char input;

	bool x = insertOperation(input, "HR");
	if (!x) {
		return false;
	}
	else {
		askUserInput(h);
		h.setHRSpecialization(mandatoryWithoutValidation("hrSpecialization", "hrSpecialization is mandatory...Please enter again!!"));
	}


	// ------------------LOGIC----------------------
	bool DbSuccess;
	//Logic to send an object
	DbSuccess = EmployeeDB::Controller::HRController::insertHR(h);
	if (DbSuccess) {}
	else {
		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
		std::cin.get();
		return false; //For Menu OF Enginner 
		//return true; //for again show insert option
	}


	if (repeatOperation("insert", "HR")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateHR() {
	EmployeeDB::Model::HR h{ true };
	bool x{ false };

	int id = inputID("update", "HR");

	if (id == 0) {
		return false;
	}
	h.setEmployeeID(id);
	bool DBSuccess;

	while (true) {
		DBSuccess = EmployeeDB::Controller::HRController::selectHR("employeeID", std::to_string(id));
		printEmpFields("HR");
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
							h.setHRSpecialization(mandatoryWithoutValidation("hrSpecialization", "hrSpecialization is mandatory...Please enter again!!"));
						}
						else {
							updateEmp(input, h);
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "\x1B[31mPlease enter valid input in the given range(1-6)...\033[0m\n";
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

	DBSuccess = EmployeeDB::Controller::HRController::updateHR(h);

	if (DBSuccess) {
		if (repeatOperation("update", "HR")) {
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

bool EmployeeDB::Console::deleteHR() {
	EmployeeDB::Model::HR h;

	int id = inputID("delete", "HR");

	if (id == 0) {
		return false;
	}

	bool DBSuccess;
	DBSuccess = EmployeeDB::Controller::HRController::selectHR("employeeID", std::to_string(id));

	if (!dltConfirmation(id, "HR")) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "HR")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewHR() {

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
			DBSuccess = EmployeeDB::Controller::HRController::selectHR();
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
				printEmpFieldsWithID("HR");
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
								arg1 = "hrSpecialization";
								while (true) {
									std::string inputField;
									std::cout << "Enter the hrSpecialization: ";
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
			DBSuccess = EmployeeDB::Controller::HRController::selectHR(arg1, arg2);
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

	if (repeatOperation("view", "HR")) {
		return true;
	}
	else {
		return false;
	}
}