#include"../../include/views/ViewQA.h"
#include "../../include/Validator.h"
#include <iostream>

void askUserInput(EmployeeDB::Model::Employee& e);
void printEmpFields();
void printEmpFieldsWithID();
void matchInpField(const std::string& inputField, std::string&, std::string&);
void updateEmp(const std::string&, EmployeeDB::Model::Employee&);

void EmployeeDB::Console::inQA() {
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
void EmployeeDB::Console::operationOfQA(const char& input) {
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

	short int cnt = 0;
	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}
		printEmpFields();
		std::cout << "13. testingTool*:" << '\n';

		char a;
		std::cout << "Are you sure you want to continue with the insert operation(0/1): ";
		a = std::cin.get();

		if (a == '\n') {
			std::cout << "Please enter valid input...\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			a = ' ';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else {
			if (EmployeeDB::Validator::validateCharInput(a)) {
				if (a == '0') {
					std::cin.clear();
					std::cin.ignore();
					return false;
				}
				else if (a == '1') {
					askUserInput(q);
					while (true) {
						std::string inputField;
						std::cout << "testingTool*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "testingTool is mandatory...Please enter again!!" << '\n';
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
							q.setTestingTool(inputField);
							break;
						}
					}
					break;
				}
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Please enter valid input...\n";
				std::cout << "Press enter to continue...\n";
				std::cin.get();
				system("cls");
			}
		}
	}

	//{
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


	while (true) {
		char in;
		std::cout << "Do you want to insert another employee?(0/1): ";
		in = std::cin.get();

		if (in == '\n') {
			std::cout << "Please enter valid input...\n";
		}
		else if (std::cin.peek() != '\n') {
			in = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
		else if (EmployeeDB::Validator::validateCharInput(in)) {
			if (in == '1') {
				return true;
			}
			else {
				std::cin.clear();
				std::cin.ignore();
				return false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
	}
}

bool EmployeeDB::Console::updateInQA() {
	EmployeeDB::Model::QA q{ true };
	bool x{ true };
	short int cnt = 0; //for cin.ignore() so it will only ignore once 

	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}

		std::cout << "Enter 0 to GO BACK or enter the ID of the employee which you want to update: ";
		std::string in;
		std::getline(std::cin, in);
		if (in.size() == 0) {
			std::cout << "Please enter valid input...\n";

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else {
			try {
				int id = std::stoi(in);
				if (id == 0) {
					std::cout << "Press enter to continue...\n";
					std::cin.get();
					system("cls");

					return false;
				}
				q.setEmployeeID(id);
				break;
			}
			catch (...) {
				std::cerr << "Please enter a numeric value...\n";

				std::cout << "Press enter to continue...\n";
				std::cin.get();
				system("cls");
			}
		}
	}

	while (true) {
		printEmpFields();
		std::cout << "13. testingTool*:" << '\n';
		std::cout << "Enter the field which you want to update(1-13): ";

		while (true) {
			char a = std::cin.get();
			if (a == '\n') {
				std::cin.clear();
				std::cout << "Please enter valid input...\n";
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
								std::cout << "testingTool: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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

		if (x) {
			char in, nxt;
			while (true) {
				std::cout << "Do you want to update another field?(0/1): ";
				in = std::cin.get();
				nxt = std::cin.peek();

				if (nxt != '\n') {
					in = ' ';
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Please enter valid input...\n";
				}

				if (Validator::validateCharInput(in)) {
					if (in == '1')
					{
						system("cls");
						std::cin.clear();
						std::cin.ignore();
					}
					break;
				}
				else {
					std::cout << "Wrong Input...\n";
				}
			}
			if (in == '0') {
				std::cin.clear();
				std::cin.ignore();
				break;
			}
		}
	}


	while (true) {
		char in;
		std::cout << "Do you want to update another employee?(0/1): ";
		in = std::cin.get();

		if (in == '\n') {
			std::cout << "Please enter valid input...\n";
		}
		else if (std::cin.peek() != '\n') {
			in = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
		else if (EmployeeDB::Validator::validateCharInput(in)) {
			if (in == '1') {
				return true;
			}
			else {
				std::cin.clear();
				std::cin.ignore();
				return false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
	}
}

bool EmployeeDB::Console::deleteInQA() {
	EmployeeDB::Model::QA q;

	std::cin.ignore();
	while (true) {
		std::cout << "Please enter 0 to GO BACK or enter ID of employee which you want to delete: ";

		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "Please enter id !!" << '\n';

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
			continue;
		}
		else if (a == '0') {
			std::cin.clear();
			std::cin.ignore();
			return false;
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			std::string inputField = a + ans;
			try {
				int id = (std::stoi(inputField));
			}
			catch (...) {
				std::cout << "Wrong input...Please enter integer!!\n";
				continue;
			}
		}
		break;
	}

	while (true) {
		std::cout << "Are you sure you want to delete that employee(0/1): ";
		char confirm;
		confirm = std::cin.get();

		if (confirm == '\n') {
			std::cout << "Please enter valid input...\n";
		}
		else if (std::cin.peek() != '\n') {
			confirm = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";

		}
		else if (EmployeeDB::Validator::validateCharInput(confirm)) {
			if (confirm == '1')
			{
				bool DbSuccess{ false };
				//	//Logic to send an object
				//	DbSuccess = fun(int);
				if (DbSuccess) {
					std::cout << "Employee Deleted SuccessFull\n";
					std::cin.clear();
					std::cin.ignore();
					break;
				}
				else {
					std::cout << "Error from DB\n";
					std::cout << "Press enter key to continue...\n";
					std::cin.clear();
					std::cin.ignore();
					std::cin.get();
					return false;
				}
			}
			else {
				std::cin.ignore();
				return false;
			}

			break;
		}
		else {
			std::cout << "Please enter valid input...\n";
		}
	}

	while (true) {
		char in;
		std::cout << "Do you want to delete another employee?(0/1): ";
		in = std::cin.get();

		if (in == '\n') {
			std::cout << "Please enter valid input...\n";
		}
		else if (std::cin.peek() != '\n') {
			in = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
		else if (EmployeeDB::Validator::validateCharInput(in)) {
			if (in == '1') {
				return true;
			}
			else {
				std::cin.clear();
				std::cin.ignore();
				return false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
	}
}

bool EmployeeDB::Console::viewInQA() {
	short int cnt = 0; //for cin.ignore() so it will only ignore once 

	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}
		char input;
		std::cout << "0. Back\n";
		std::cout << "1. View whole table\n";
		std::cout << "2. View with the help of some field of the table\n";
		std::cout << "Enter your choice(0-2): ";
		input = std::cin.get();

		if (input == '\n') {
			std::cout << "Please enter valid input...\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.get() != '\n') {
			input = ' ';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else {
			if (EmployeeDB::Validator::validateInputView(input)) {
				if (input == '0') {
					return false;
				}
				else if (input == '1' || input == '2') {
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
							printEmpFieldsWithID();
							std::cout << "15. testingTool*:" << '\n';
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
												std::cout << "Enter the testingTool: ";
												char a = std::cin.get();
												if (a == '\n') {
													std::cout << "The input can not be empty...Please enter something" << '\n';
												}
												else {
													std::string ans{ "" };
													std::getline(std::cin, ans);
													arg2 = a + ans;
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
					break;
				}
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cerr << "Please enter valid input in the given range(0-2)\n";
				std::cout << "Press enter to continue...\n";
				std::cin.get();
				system("cls");
			}
		}
	}

	while (true) {
		char in;
		std::cout << "Do you want to view another employee?(0/1): ";
		in = std::cin.get();

		if (in == '\n') {
			std::cout << "Please enter valid input...\n";
		}
		else if (std::cin.peek() != '\n') {
			in = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";
		}
		else if (EmployeeDB::Validator::validateCharInput(in)) {
			if (in == '1') {
				return true;
			}
			else {
				std::cin.clear();
				std::cin.ignore();
				return false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";

		}
	}
}
