#include"../../include/views/ViewManager.h"
#include "../../include/Validator.h"
#include<iostream>

void askUserInput(EmployeeDB::Model::Employee& e);
void printEmpFields();
void printEmpFieldsWithID();
void matchInpField(const std::string& inputField, std::string&, std::string&);
void updateEmp(const std::string&, EmployeeDB::Model::Employee&);

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

	short int cnt = 0;
	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}

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
					while (true) {
						std::string id;
						std::cout << "Enter the Employee id whom you want to make manager: ";
						std::cin >> id;
						int ID;
						try {
							ID = std::stoi(id);
							break;
						}
						catch (...) {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Please enter valid input...\n";
						}
					}

					std::cin.ignore();
					while (true) {
						std::string inputField;
						std::cout << "teamSize*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "teamSize is mandatory...Please enter again!!\n";
							continue;
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
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
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "Years Of Experince is mandatory...Please enter again!!\n";
							continue;
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
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
					{
						std::string inputField;
						std::cout << "projectTitle: ";
						char a = std::cin.get();
						if (a == '\n') {}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
							m.setProjectTitle(inputField);
						}
					}

					while (true) {
						std::string inputField;
						std::cout << "role*: ";
						char a = std::cin.get();
						if (a == '\n') {
							std::cout << "role is mandatory...Please enter again!!\n";
							continue;
						}
						else {
							std::string ans{ "" };
							std::getline(std::cin, ans);
							inputField = a + ans;
							m.setRole(inputField);
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




	////send to validator



	//Logic to send an object


	while (true) {
		char in;
		std::cout << "Do you want to make another manager?(0/1): ";
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

bool EmployeeDB::Console::updateManager() {
	EmployeeDB::Model::Manager m{ false };
	bool x{ false };
	short int cnt = 0; //for cin.ignore() so it will only ignore once 

	while (true) {
		if (cnt == 0) {
			std::cin.ignore();
			cnt++;
		}

		std::cout << "Enter 0 to GO BACK or enter the ID of the manager which you want to update: ";
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
				m.setManagerID(id);
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
		std::cout << "13. teamSize*:" << '\n';
		std::cout << "14. yearsOfExperince*:" << '\n';
		std::cout << "15. projectTitle*:" << '\n';
		std::cout << "16. role*:" << '\n';
		std::cout << "Enter the field which you want to update(1-16): ";

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
					if (EmployeeDB::Validator::validateManUpdate(input)) {
						if (std::stoi(input) == 13) {
							while (true) {
								std::cout << "teamSize: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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
								std::cout << "yearsOfExperince: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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
								std::cout << "projectTitle: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
									m.setProjectTitle(inputField);
									break;
								}
							}
						}
						else if (std::stoi(input) == 16) {
							while (true) {
								std::cout << "role: ";
								char a = std::cin.get();
								if (a == '\n') {
									std::cout << "Please enter some value!!" << '\n';
								}
								else {
									std::string ans{ "" };
									std::getline(std::cin, ans);
									std::string inputField = a + ans;
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

	//Logic Pass object to controller 

	while (true) {
		char in;
		std::cout << "Do you want to update another manager?(0/1): ";
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

bool EmployeeDB::Console::deleteManager() {
	EmployeeDB::Model::Manager m;

	std::cin.ignore();
	while (true) {
		std::cout << "Please enter 0 to GO BACK or enter ID of manager which you want to delete: ";

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
		std::cout << "Are you sure you want to delete that manager(0/1): ";
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
					std::cout << "Manager Deleted SuccessFull\n";
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
		std::cout << "Do you want to delete another manager?(0/1): ";
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

bool EmployeeDB::Console::viewManager() {
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
		else if (std::cin.peek() != '\n') {
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

							std::cout << "15. teamSize*:" << '\n';
							std::cout << "16. yearsOfExperince*:" << '\n';
							std::cout << "17. projectTitle*:" << '\n';
							std::cout << "18. role*:" << '\n';
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
												std::cout << "Enter the teamSize: ";
												char a = std::cin.get();
												if (a == '\n') {
													std::cout << "The input can not be empty...Please enter something\n";
												}
												else {
													std::string ans{ "" };
													std::getline(std::cin, ans);
													arg2 = a + ans;
													try {
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
												std::cout << "Enter the yearsOfExperince: ";
												char a = std::cin.get();
												if (a == '\n') {
													std::cout << "The input can not be empty...Please enter something\n";
												}
												else {
													std::string ans{ "" };
													std::getline(std::cin, ans);
													arg2 = a + ans;
													break;
												}
											}
										}
										else if (std::stoi(inputField) == 17) {
											arg1 = "projectTitle";
											while (true) {
												std::cout << "Enter the projectTitle: ";
												char a = std::cin.get();
												if (a == '\n') {
													std::cout << "The input can not be empty...Please enter something\n";
												}
												else {
													std::string ans{ "" };
													std::getline(std::cin, ans);
													arg2 = a + ans;
													break;
												}
											}
										}
										else if (std::stoi(inputField) == 18) {
											arg1 = "role";
											while (true) {
												std::cout << "Enter the role: ";
												char a = std::cin.get();
												if (a == '\n') {
													std::cout << "The input can not be empty...Please enter something\n";
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
