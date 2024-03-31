#include "ConsoleManager.h"
#include "ViewExportCSV.h"
#include "ViewEngineer.h"
#include "ViewFinance.h"
#include "ViewHR.h"
#include "ViewManager.h"
#include "ViewQA.h"
#include "ViewDepartment.h"
#include "Validator.h"
#include "DBManager.h"
#include<iostream>

using EmployeeDB::DBManager;

void EmployeeDB::Console::viewDBMenu() noexcept {
	std::cin.ignore();
	DBManager::executeConfigQuery();
	system("cls");
	while (true) {
		std::cout << "------------------------------------- Welcome to Employee Database Managment -------------------------------------------\n";
		std::cout << "0. Quit\n";
		std::cout << "1. Engineer\n";
		std::cout << "2. Finance\n";
		std::cout << "3. HR\n";
		std::cout << "4. QA\n";
		std::cout << "5. Manager\n";
		std::cout << "6. Department\n";
		std::cout << "7. Export Table as CSV\n";
		std::cout << "8. Main Menu\n";
		std::cout << "\x1B[36mPlease select entity on which you want to perform operation: \033[0m";

		char input;
		input = std::cin.get();
		if (input == '\n') {
			std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";

			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (std::cin.peek() != '\n') {
			input = ' ';
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\x1B[31mPlease enter valid input in the given range(0-8)...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (EmployeeDB::Validator::validateInputMainMenu(input)) {
			system("cls");
			if (input == '0') {
				std::exit(0);
			}
			else if (input == '8') {
				std::cin.clear();
				std::cin.ignore();
				return;
			}

			viewFields(input);
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cerr << "\x1B[31mPlease enter valid input in the given range(0-8)...\033[0m\n";

			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
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
		engineerMenu();
		break;
	case '2':
		financeMenu();
		break;
	case '3':
		HRMenu();
		break;
	case '4':
		QAMenu();
		break;
	case '5':
		managerMenu();
		break;
	case '6':
		departmentMenu();
		break;
	case '7':
		ExportCSVMenu();
		break;
	}
	return;
}