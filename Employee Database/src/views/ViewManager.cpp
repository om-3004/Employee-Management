#include "ViewManager.h"
#include "Common.h"
#include "ManagerController.h"
#include "EmployeeController.h"

void EmployeeDB::Console::managerMenu() noexcept {
	inputForEnt("Manager");
}

void EmployeeDB::Console::operationOfMan(const char& input) noexcept {
	bool repeat{ true };
	switch (input) {
	case '0':
		std::exit(0);
	case '1': {
		while (repeat) {
			repeat = makeManager();
			system("cls");
		}
		break;
	}
	case '2': {
		while (repeat) {
			repeat = updateManager();
			system("cls");
		}
		break;
	}
	case '3': {
		while (repeat) {
			repeat = deleteManager();
			system("cls");
		}
		break;
	}
	case '4': {
		while (repeat) {
			repeat = viewManager();
			system("cls");
		}
		break;
	}
	}
}

bool EmployeeDB::Console::makeManager() {
	EmployeeDB::Model::Manager m;
	char input;

	bool x = insertOperation(input, "Manager");
	if (!x) {
		return false;
	}
	else {
		std::cin.ignore();
		while (true) {
			std::string id;
			std::cout << "\x1B[36mEnter the Employee id whom you want to make manager: \033[0m";
			std::getline(std::cin, id);
			int ID;
			try {
				ID = std::stoi(id);

				m.setManagerID(ID);

				int DepartmentID;
				DepartmentID = EmployeeDB::Controller::EmployeeController::getDepartmentIDbyEmployeeID(m.getManagerID());

				if (DepartmentID == -1) {
					std::cerr << "\x1B[31mNo employee was not found for provided managerID...\033[0m\n";
					continue;
				}

				m.setDepartmentID(DepartmentID);

				break;
			}
			catch (...) {
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			}
		}
		m.setTeamSize(std::stoi(mandatoryWithValidation("teamSize", "teamSize is mandatory...Please enter again!!", EmployeeDB::Validator::validateNum)));
		m.setYearsOfExp(std::stoi(mandatoryWithValidation("yearsOfExperince", "yearsOfExperince is mandatory...Please enter again!!", EmployeeDB::Validator::validateNum)));
		m.setProjectTitle(nonMandatoryWithoutValidation("projectTitle", "Please enter valid input..."));
		m.setRole(mandatoryWithoutValidation("role", "role is mandatory...Please enter again!!"));
	}

	// ------------------LOGIC----------------------
	bool DbSuccess;
	DbSuccess = EmployeeDB::Controller::ManagerController::insertManager(m);
	if (DbSuccess) {}
	else {
		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";

		std::cin.get();
		return false; //For Menu OF Enginner 
	}


	if (repeatOperation("insert", "Manager")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateManager() {
	EmployeeDB::Model::Manager m{ false };
	bool x{ false };

	int id = inputID("Update", "Manager");

	if (id == 0) {
		return false;
	}

	m.setManagerID(id);
	m.setEmployeeID(id);
	bool DBSuccess;

	while (true) {
		DBSuccess = EmployeeDB::Controller::ManagerController::selectManager("employeeID", std::to_string(id));
		printEmpFields("Manager");
		std::cout << "\x1B[36mEnter the field which you want to update(1-16): \033[0m";

		while (true) {
			char a = std::cin.get();
			if (a == '\n') {
				std::cin.clear();
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				system("cls");
				x = false;
				break;
			}
			else {
				std::string str;
				std::getline(std::cin, str);
				std::string input = a + str;

				while (true) {
					if (EmployeeDB::Validator::validateManUpdate(input)) {
						if (std::stoi(input) == 13) {
							m.setTeamSize(std::stoi(mandatoryWithValidation("teamSize", "teamSize is mandatory...Please enter again!!", EmployeeDB::Validator::validateNum)));
						}
						else if (std::stoi(input) == 14) {
							m.setYearsOfExp(std::stoi(mandatoryWithValidation("yearsOfExperince", "yearsOfExperince is mandatory...Please enter again!!", EmployeeDB::Validator::validateNum)));
						}
						else if (std::stoi(input) == 15) {
							m.setProjectTitle(mandatoryWithoutValidation("projectTitle", "Please enter valid input..."));
						}
						else if (std::stoi(input) == 16) {
							m.setRole(mandatoryWithoutValidation("role", "role is mandatory...Please enter again!!"));
						}
						else {
							updateEmp(input, m);
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "\x1B[31mPlease enter valid input in the given range(1-16)...\033[0m\n";
						x = false;

						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
						std::cin.get();
						system("cls");
						break;
					}
				}
				break;
			}
		}

		bool y = repeatUpdateField(x);
		if (!y) {
			break;
		}
	}

	DBSuccess = EmployeeDB::Controller::ManagerController::updateManager(m);

	if (DBSuccess) {
		if (repeatOperation("update", "Manager")) {
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

bool EmployeeDB::Console::deleteManager() {
	EmployeeDB::Model::Manager m;

	int id = inputID("Delete", "Manager");

	if (id == 0) {
		return false;
	}

	bool DBSuccess;
	DBSuccess = EmployeeDB::Controller::ManagerController::selectManager("employeeID", std::to_string(id));

	if (!dltConfirmation(id, "Manager")) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "Manager")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewManager() {

	char input;
	bool x = viewOperation(input, "Manager");
	if (!x) {
		return false;
	}
	else {
		std::string arg1, arg2;
		switch (input) {
		case '1': {
			bool DBSuccess;
			//	//Logic to send an object
			DBSuccess = EmployeeDB::Controller::ManagerController::selectManager();
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
				printEmpFieldsWithID("Manager");
				std::cout << "\x1B[36mSelect the field using which you want to view the Employee details(1-18): \033[0m";
				char input;
				input = std::cin.get();
				if (input == '\n') {
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
						std::string inputField = input + str;
						if (EmployeeDB::Validator::validateViewOfManFields(inputField)) {

							if (std::stoi(inputField) == 15) {
								arg1 = "teamSize";
								while (true) {
									std::string inputField;
									std::cout << "Enter the teamSize: ";
									std::getline(std::cin, inputField);
									inputField = trim(inputField);
									if (inputField.size() == 0) {
										std::cerr << "\x1B[31mThe input can not be empty...Please enter something\033[0m\n";
									}
									else {
										try {
											arg2 = inputField;
											[[maybe_unused]] int unused = std::stoi(arg2);
											break;
										}
										catch (...) {
											std::cerr << "\x1B[31mPlease enter integer value...\033[0m\n";
										}
									}

								}
							}
							else if (std::stoi(inputField) == 16) {
								arg1 = "yearsOfExperince";
								while (true) {
									std::string inputField;
									std::cout << "Enter the yearsOfExperince: ";
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
							else if (std::stoi(inputField) == 17) {
								arg1 = "projectTitle";
								while (true) {
									std::string inputField;
									std::cout << "Enter the projectTitle: ";
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
							else if (std::stoi(inputField) == 18) {
								arg1 = "role";
								while (true) {
									std::string inputField;
									std::cout << "Enter the role: ";
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
			DBSuccess = EmployeeDB::Controller::ManagerController::selectManager(arg1, arg2);
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


	if (repeatOperation("view", "manager")) {
		return true;
	}
	else {
		return false;
	}
}
