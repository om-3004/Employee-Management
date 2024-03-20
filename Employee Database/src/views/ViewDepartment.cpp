#include"../../include/views/ViewDepartment.h"
#include "../../include/Validator.h"
#include<iostream>

void EmployeeDB::Console::inDepartment() {

	while (true) {
		std::cout << "0. Quit\n";
		std::cout << "1. Insert\n";
		std::cout << "2. Update\n";
		std::cout << "3. Delete\n";
		std::cout << "4. View\n";
		std::cout << "5. Main Menu\n";
		std::cout << "Please select operation which you want to perform on Department: ";

		char input = std::cin.get();
		/*nxt = std::cin.peek();*/

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

void EmployeeDB::Console::operationOfDept(const char& input) {
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

	short int cnt = 0;
	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}
		std::cout << "1. Department Name*: \n";
		std::cout << "2. Base Salaray*: \n";
		std::cout << "3. Allowance*: \n";
		std::cout << "4. Deduction*: \n";

		char input;
		std::cout << "Are you sure you want to continue with the insert operation(0/1): ";
		input = std::cin.get();

		if (input == '\n') {
			std::cout << "Please enter valid input...\n";

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			input = ' ';  // Validator will return false

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter valid input...\n";

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else {
			if (EmployeeDB::Validator::validateCharInput(input)) {
				if (input == '0') {
					std::cin.clear();
					std::cin.ignore();
					return false;
				}
				else if (input == '1') {
					std::cin.ignore();
					while (true) {
						std::string inputField;
						std::cout << "Department Name*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "Department Name is mandatory...Please enter again!!\n";
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
							d.setDepartmentName(inputField);
							break;
						}
					}

					while (true) {
						std::string inputField;
						std::cout << "Base Salaray*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "Base Salaray is mandatory...Please enter again!!\n";
							continue;
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
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
						std::cout << "Allowance*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "Allowance is mandatory...Please enter again!!\n";
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
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
						std::cout << "Deduction*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "Deduction is mandatory...Please enter again!!\n";
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
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
	//	DbSuccess = fun(d);
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

bool EmployeeDB::Console::updateDept() {
	EmployeeDB::Model::Department d(true);
	short int cnt = 0; //for cin.ignore() so it will only ignore once 
	bool x{ true };

	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}

		std::cout << "Enter 0 to GO BACK or enter the ID of the department which you want to update: ";
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
				d.setDepartmentID(id);
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
								std::cout << "baseSalary: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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
								std::cout << "allowance: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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
								std::cout << "deduction: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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

bool EmployeeDB::Console::deleteDept() {
	EmployeeDB::Model::Department d;

	std::cin.ignore();
	while (true) {
		std::cout << "Please enter 0 to GO BACK or enter ID of department which you want to delete: ";

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
		std::cout << "Are you sure you want to delete that department(0/1): ";
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
					std::cout << "Department Deleted SuccessFull\n";
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
		std::cout << "Do you want to delete another department?(0/1): ";
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

std::string checkInputDept(const std::string& s) {
	std::string str;
	while (true) {
		std::cout << "Enter the " + s + ": ";
		char a = std::cin.get();
		if (a == '\n') {
			std::cout << "The input can not be empty...Please enter something" << '\n';
		}
		else {
			std::string ans{ "" };
			std::getline(std::cin, ans);
			str = a + ans;
			break;
		}
	}
	return str;
}

void matchInpFieldDept(const std::string& inputField, std::string& arg1, std::string& arg2) {
	switch (std::stoi(inputField)) {
	case 1: {
		while (true) {
			arg1 = "departmentID";
			arg2 = checkInputDept(arg1);
			try {
				[[maybe_unused]] int a = std::stoi(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter integer value...\n";
			}
		}
		break;
	}
	case 2: {
		arg1 = "departmentName";
		arg2 = checkInputDept(arg1);
		break;
	}
	case 3: {
		while (true) {
			arg1 = "baseSalary";
			arg2 = checkInputDept(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter numeric value...\n";
			}
		}
		break;
	}
	case 4: {
		while (true) {
			arg1 = "allowance";
			arg2 = checkInputDept(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter numeric value...\n";
			}
		}
		break;
	}
	case 5: {
		while (true) {
			arg1 = "deduction";
			arg2 = checkInputDept(arg1);
			try {
				[[maybe_unused]] double a = std::stod(arg2);
				break;
			}
			catch (...) {
				std::cout << "Please enter numeric value...\n";
			}
		}
		break;
	}
	}
}

bool EmployeeDB::Console::viewDept() {
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
							std::cout << "1. Department ID*: \n";
							std::cout << "2. Department Name*: \n";
							std::cout << "3. Base Salaray*: \n";
							std::cout << "4. Allowance*: \n";
							std::cout << "5. Deduction*: \n";
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
										matchInpFieldDept(inputField, arg1, arg2);
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
		std::cout << "Do you want to view another department?(0/1): ";
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