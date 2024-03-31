#include "../../include/views/ViewTable.h"
#include "../../include/model/Table.h"
#include "../../include/controller/TableController.h"
#include "Common.h"
#include <iostream>

void takeTableInput(std::string field, std::array<std::string, 3>& arr, int i) {
	while (true) {
		std::cout << field << ": ";
		std::string inputField;
		std::getline(std::cin, inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		inputField = EmployeeDB::Console::trim(inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else {
			if (EmployeeDB::Validator::validateName(inputField)) {
				arr[i] = inputField;
				i++;
				break;
			}
			else {
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			}
		}
	}
}
void takeTableKeyInput(std::string field, std::array<std::string, 4>& arr, int i) {
	while (true) {
		std::cout << field << ": ";
		std::string inputField;
		std::getline(std::cin, inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		inputField = EmployeeDB::Console::trim(inputField);
		if (inputField.size() == 0) {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else {
			if (EmployeeDB::Validator::validateName(inputField)) {
				arr[i] = inputField;
				i++;
				break;
			}
			else {
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			}
		}
	}
}

void EmployeeDB::Console::createTable(){
	std::cin.ignore();

	char a;
	std::cout << "\x1B[36mAre you sure you want to continue with the create table operation(0/1): \033[0m";
	a = std::cin.get();

	if (a == '\n') {
		std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
		std::cin.get();
		system("cls");
	}
	else if (std::cin.peek() != '\n') {
		a = ' ';
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";

		std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
		std::cin.get();
		system("cls");
	}
	else {
		if (EmployeeDB::Validator::validateCharInput(a)) {
			if (a == '0') {
				std::cin.clear();
				std::cin.ignore();
				system("cls");
				return ;
			}
			else {
				system("cls");
				std::cin.ignore();
				Model::Table t;
				while(true) {
					std::cout << "-------------------------------------------------- CREATE TABLE --------------------------------------------------------\n";
					std::string tableName;
					while (true) {
						std::cout << "Table Name: ";
						std::getline(std::cin, tableName);
						if (tableName.size() == 0) {
							std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
							continue;
						}
						else {
							tableName = Console::trim(tableName);
							if (tableName.size() == 0) {
								std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
							}
							else {
								if (EmployeeDB::Validator::validateName(tableName)) {
									t.setTableName(tableName);
									break;
								}
								else {
									std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
								}
							}
						}
					}

					std::vector<std::array<std::string, 3>> columns;
					std::array<std::string, 3> arr;
					int colCount = 0;

					while (true) {
						colCount++;
						std::cout << "\x1B[36mEnter details for column " << colCount << "\033[0m\n";

						takeTableInput("Column Name*", arr, 0);
						takeTableInput("Column Type*", arr, 1);
						takeTableInput("Constraints", arr, 2);

						columns.push_back(arr);

						if (repeatOperation("enter", "column")) {
							std::cin.clear();
							std::cin.ignore();
							continue;
						}
						else {
							break;
						}
					}
					t.setColumns(columns);

					char yesNo;
					int keyCount = 0;

					while (true) {
						std::cout << "\x1B[36mDo you want to make foreign key?(0/1): \033[0m";
						yesNo = std::cin.get();
						if (yesNo == '\n') {
							std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
						}
						else if (std::cin.peek() != '\n') {
							yesNo = ' ';  // Validator will return false
							std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
						}
						else if (EmployeeDB::Validator::validateCharInput(yesNo)) {
							std::cin.clear();
							std::cin.ignore();
							if (yesNo == '1') {
								std::vector<std::array<std::string, 4>> foreingkey;
								std::array<std::string, 4> array;
								while (true) {
									keyCount++;
									std::cout << "\x1B[36mEnter details for foreign key " << keyCount << "\033[0m\n";
									takeTableKeyInput("Column Name*", array, 0);
									takeTableKeyInput("Parent Table Name*", array, 1);
									takeTableKeyInput("Parent column name*", array, 2);
									takeTableKeyInput("Constraint", array, 3);

									foreingkey.push_back(array);

									if (repeatOperation("make", "foreign key")) {
										std::cin.clear();
										std::cin.ignore();
										continue;
									}
									else {
										break;
									}
								}
								t.setForeignKeyConstraint(foreingkey);
								break;
							}
							else {
								break;
							}
						}
						else {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
						}
					}

					bool DBSuccess = EmployeeDB::Controller::TableController::createTableQuery(t, colCount, keyCount);
					if (DBSuccess) {
						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
						std::cin.get();
						system("cls");
						break;
					}
					else {
						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
						std::cin.get();
						system("cls");
						continue;
					}

					/*if (repeatOperation("create", "table")) {
						continue;
					}
					else {
						break;
					}*/
				}
			}
		}
	}

}

void EmployeeDB::Console::deleteTable() {
	std::cin.clear();
	std::cin.ignore();
	std::string tableName;
	while (true) {
		std::cout << "\x1B[36mEnter 0 to GO BACK or enter the table name which you want to delete: \033[0m";
		std::getline(std::cin, tableName);
		if (tableName.size() == 0) {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
		}
		else {
			tableName = EmployeeDB::Console::trim(tableName);
			if (tableName.size() == 0) {
				std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
			}
			else {
				if (tableName == "0") {
					system("cls");
					return;
				}
				else if (EmployeeDB::Validator::validateName(tableName)) {
					bool DBSuccess = EmployeeDB::Controller::TableController::deleteTableQuery(tableName);
					if (DBSuccess) {
						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
						std::cin.get();
						system("cls");
						break;
					}
					else {
						std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
						std::cin.get();
						system("cls");
						continue;
					}
					break;
				}
				else {
					std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
				}
			}
		}
	}
}