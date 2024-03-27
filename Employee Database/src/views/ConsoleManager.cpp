#include "ConsoleManager.h"
#include "ViewEngineer.h"
#include "ViewFinance.h"
#include "ViewHR.h"
#include "ViewManager.h"
#include "ViewQA.h"
#include "ViewDepartment.h"
#include "Validator.h"
#include"../../include/DBManager.h"
#include<iostream>

using EmployeeDB::DBManager;

void tableToCSV();

void EmployeeDB::Console::viewMenu() noexcept {
	DBManager::executeConfigQuery();
	system("cls");
	while (true) {
		std::cout << "------------------------------------------Welcome to Database Managment-------------------------------------------------\n";
		std::cout << "0. Quit\n";
		std::cout << "1. Engineer\n";
		std::cout << "2. Finance\n";
		std::cout << "3. HR\n";
		std::cout << "4. QA\n";
		std::cout << "5. Manager\n";
		std::cout << "6. Department\n";
		std::cout << "Please select entity on which you want to perform operation: ";

		char input;
		input = std::cin.get();
		if (input == '\n') {
			std::cerr << "Please enter valid input...\n";

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			input = ' ';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Please enter valid input in the given range(0-6)\n";
			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
		else if (EmployeeDB::Validator::validateInputMainMenu(input)) {
			system("cls");
			if (input == '0') {
				std::exit(0);
			}

			viewFields(input);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cerr << "Please enter valid input in the given range(0-6)\n";

			std::cout << "Press enter to continue...\n";
			std::cin.get();
			system("cls");
		}
	}
}  

void EmployeeDB::Console::viewFields(const char& input) noexcept {
	std::cin.clear();
	std::cin.ignore();
	switch (input) {
	case 0:
		break;
	case '1':
		inEngineer();
		break;
	case '2':
		inFinance();
		break;
	case '3':
		inHR();
		break;
	case '4':
		inQA();
		break;
	case '5':
		inManager();
		break;
	case '6':
		inDepartment();
		//tableToCSV();
		break;
	}
	return;
}
