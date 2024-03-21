#include"../../include/views/ViewManager.h"
#include "../../include/views/Common.h"

void EmployeeDB::Console::inManager() {
	while (true) {

		std::cout << "0. Quit\n";
		std::cout << "1. Make New Manager\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "Please select operation which you want to perform on Manager: ";

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

			operationOfMan(input);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Please enter valid input in the given range(0-5)\n\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
	}
}

void EmployeeDB::Console::operationOfMan(const char& input) {
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

	bool x = insertOperation(input, "manager");
	if (!x) {
		return false;
	}
	else {
		std::cin.ignore();
		while (true) {
			std::string id;
			std::cout << "Enter the Employee id whom you want to make manager: ";
			std::getline(std::cin, id);
			int ID;
			try {
				ID = std::stoi(id);
				break;
			}
			catch (...) {
				std::cout << "Please enter valid input...\n";
			}
		}
		while (true) {
			std::string inputField;
			std::cout << "teamSize*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "teamSize is mandatory...Please enter again!!" << '\n';
			}
			else {
				try {
					m.setTeamSize(std::stoi(inputField));
				}
				catch (...) {
					std::cerr << "Invalid input...Please enter integer\n";
					continue;
				}
				break;
			}
		}

		while (true) {

			std::string inputField;
			std::cout << "yearsOfExperince*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "yearsOfExperince is mandatory...Please enter again!!" << '\n';
			}
			else {
				try {
					m.setYearsOfExperience(std::stoi(inputField));
				}
				catch (...) {
					std::cerr << "Invalid input...Please enter integer\n";
					continue;
				}
				break;
			}
		}

		while (true) {
			std::string inputField;
			std::cout << "projectTitle: ";
			std::getline(std::cin, inputField);
			if (inputField.size() == 0) {
				break;
			}
			else {
				inputField = trim(inputField);
				if (inputField.size() == 0) {
					std::cout << "Please enter valid input...\n";
				}
				else {
					m.setProjectTitle(inputField);
					break;
				}
			}
		}

		while (true) {
			std::string inputField;
			std::cout << "role*: ";
			std::getline(std::cin, inputField);
			inputField = trim(inputField);
			if (inputField.size() == 0) {
				std::cout << "role is mandatory...Please enter again!!\n";
			}
			else {
				m.setProjectTitle(inputField);
				break;
			}
		}
	}

	////send to validator

	//Logic to send an object

	if (repeatOperation("insert", "manager")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::updateManager() {
	EmployeeDB::Model::Manager m{ false };
	bool x{ false };

	int id = inputID("update", "manager");

	if (id == 0) {
		return false;
	}

	while (true) {
		printEmpFields("manager");
		std::cout << "Enter the field which you want to update(1-16): ";

		while (true) {
			char a = std::cin.get();
			if (a == '\n') {
				std::cin.clear();
				std::cout << "Please enter valid input...\n";
				std::cout << "Press enter to continue...\n";
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
							while (true) {
								std::string inputField;
								std::cout << "teamSize: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									try {
										m.setTeamSize(std::stoi(inputField));
										break;
									}
									catch (...) {
										std::cout << "Invalid input...Pleas enter an integer!!\n";
									}
								}

							}
						}
						else if (std::stoi(input) == 14) {
							while (true) {
								std::string inputField;
								std::cout << "yearsOfExperince: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									try {
										m.setYearsOfExperience(std::stoi(inputField));
										break;
									}
									catch (...) {
										std::cout << "Invalid input...Please enter an integer\n";
									}
								}
							}
						}
						else if (std::stoi(input) == 15) {
							while (true) {
								std::string inputField;
								std::cout << "projectTitle: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									m.setProjectTitle(inputField);
									break;
								}
							}
						}
						else if (std::stoi(input) == 16) {
							while (true) {
								std::string inputField;
								std::cout << "role: ";
								std::getline(std::cin, inputField);
								inputField = trim(inputField);
								if (inputField.size() == 0) {
									std::cout << "Please enter some value...\n";
								}
								else {
									m.setRole(inputField);
									break;
								}
							}
						}
						else {
							updateEmp(input, m);
						}
						x = true;
						break;
					}
					else {
						std::cin.clear();
						std::cerr << "Please enter valid input in the given range(1-16)\n";
						x = false;

						std::cout << "Press enter to continue...\n";
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

	//Logic Pass object to controller 

	if (repeatOperation("update", "manager")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::deleteManager() {
	EmployeeDB::Model::Manager m;

	int id = inputID("delete", "manager");

	if (id == 0) {
		return false;
	}

	if (!dltConfirmation(id)) {
		return false;
	}

	std::cin.ignore();
	if (repeatOperation("delete", "manager")) {
		return true;
	}
	else {
		return false;
	}
}

bool EmployeeDB::Console::viewManager() {

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
				printEmpFieldsWithID("manager");
				std::cout << "Select the field using which you want to view the Employee details(1-18): ";
				char input;
				input = std::cin.get();
				if (input == '\n') {
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
						std::string inputField = input + str;
						std::cout << inputField << '\n';
						if (EmployeeDB::Validator::validateViewOfManFields(inputField)) {

							if (std::stoi(inputField) == 15) {
								arg1 = "teamSize";
								while (true) {
									std::string inputField;
									std::cout << "Enter the teamSize: ";
									std::getline(std::cin, inputField);
									inputField = trim(inputField);
									if (inputField.size() == 0) {
										std::cout << "The input can not be empty...Please enter something\n";
									}
									else {
										try {
											arg2 = inputField;
											[[maybe_unused]] int unused = std::stoi(arg2);
											break;
										}
										catch (...) {
											std::cout << "Please enter integer value...\n";
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
										std::cout << "The input can not be empty...Please enter something\n";
									}
									else {
										arg2 = inputField;
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
										std::cout << "The input can not be empty...Please enter something\n";
									}
									else {
										arg2 = inputField;
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
										std::cout << "The input can not be empty...Please enter something\n";
									}
									else {
										arg2 = inputField;
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


	if (repeatOperation("view", "manager")) {
		return true;
	}
	else {
		return false;
	}
}
