#include "views/ViewExportCSV.h"
#include "controller/ExportCSVController.h"
#include "Validator.h"

#include <iostream>
using EmployeeDB::Controller::ExportController;


void EmployeeDB::Console::ExportCSVMenu() {
	while (true) {
		std::cout << "-------------------------------------------------- Export CSV ----------------------------------------------------------\n";
		std::cout << "0. Quit\n";
		std::cout << "1. Export All Tables\n";
		std::cout << "2. Export Department Table\n";
		std::cout << "3. Export Employee Table\n";
		std::cout << "4. Export Engineer Table\n";
		std::cout << "5. Export Finance Table\n";
		std::cout << "6. Export HR Table\n";
		std::cout << "7. Export Manager Table\n";
		std::cout << "8. Export QA Table\n";
		std::cout << "9. EmployeeDB Menu\n";
		std::cout << "\x1B[36mSelect the table which you want to export as CSV(0-9): \033[0m";

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
			std::cerr << "\x1B[31mPlease enter valid input in the given range(0-9)...\033[0m\n";

			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
		else if (EmployeeDB::Validator::validatecsvInput(input)) {
			bool result{ false };
			switch (input) {
			case '0':
				std::exit(0);
				break;
			case '1':
				result = ExportController::exportAll();
				break;
			case '2':
				result = ExportController::exportToCSV("Department", "DepartmentBackup");
				break;
			case '3':
				result = ExportController::exportToCSV("Employee", "EmployeeBackup");
				break;
			case '4':
				result = ExportController::exportToCSV("Engineer", "EngineerBackup");
				break;
			case '5':
				result = ExportController::exportToCSV("Finance", "FinanceBackup");
				break;
			case '6':
				result = ExportController::exportToCSV("HR", "HRBackup");
				break;
			case '7':
				result = ExportController::exportToCSV("Manager", "ManagerBackup");
				break;
			case '8':
				result = ExportController::exportToCSV("QA", "QABackup");
				break;
			case '9':
				std::cin.ignore();
				system("cls");
				return;
				break;
			}
			if (result) {
				std::cin.ignore();
				char in;
				std::cout << "\x1B[36mDo you want to export another table?(0/1): \033[0m";
				in = std::cin.get();
				if (EmployeeDB::Validator::validateCharInput(in)) {
					if (in == '0') {
						std::cin.clear();
						std::cin.ignore();
						system("cls");
						return;
					}
					else {
						std::cin.clear();
						std::cin.ignore();
						system("cls");
					}
				}
				else {
					std::cerr << "\x1B[31mPlease enter valid input...\033[0m\n";
					std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
					std::cin.get();
					system("cls");
				}
			}
			else {
				std::cin.ignore();
				std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
				std::cin.get();
				system("cls");
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			
			std::cerr << "\x1B[31mPlease enter valid input in the given range(0-9)...\033[0m\n";
			std::cout << "\x1B[33mPress enter to continue...\033[0m\n";
			std::cin.get();
			system("cls");
		}
	}
}