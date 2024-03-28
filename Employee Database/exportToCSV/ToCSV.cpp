#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include "../include/DBManager.h"

std::vector<std::string> tableName;
int callDump(void* tab, int Nocolumn, char** columnValue, char** columnName) {
	for (int i = 0; i < Nocolumn; i++) {
		tableName.push_back(columnValue[i]);
	}
	return 0;
};

std::vector<std::string> Tables() {

	const char* query = "SELECT name FROM sqlite_master WHERE type='table';";
	char* m_errorMsg{};

	EmployeeDB::DBManager::instance().dumpCSV(query, callDump, m_errorMsg);

	return tableName;
}


std::string tabledata{ "" };

int selCallback(void* arg, int argc, char** argv, char** azColName) {

	int* cnt = static_cast<int*>(arg);

	if (*cnt == 0)
	{
		for (int i = 0; i < argc; i++) {
			tabledata += azColName[i];
			tabledata += ", ";
		}
		tabledata += "\n";
		(*cnt)++;
	}

	for (int i = 0; i < argc; i++) {

		std::string str = argv[i];
		size_t idx = 0;
		while (idx != std::string::npos) {
			idx = str.find(',');
			if (idx != std::string::npos) {
				str.erase(idx, 1);
			}
		}
		tabledata += str;
		tabledata += ", ";
	}
	tabledata += "\n";

	return 0;
}

void tableToCSV() {
	std::vector tables = Tables();

	namespace f = std::filesystem;
	f::path p{ "C:/Users/ZTI/OneDrive - ZURU INC/Desktop/OM/C++ Training/Emp_Management/Employee Database/exportToCSV/DBtable.csv" };
	std::ofstream out{ p.lexically_normal() };
	std::string query;
	for (auto& table : tables) {
		query = "SELECT * FROM " + table;
		int x = 0;
		tabledata += "Table: ";
		tabledata += table;
		tabledata += "\n";
		EmployeeDB::DBManager::instance().executeDumpQuery(query.c_str(), selCallback, &x);
		tabledata += "\n";
	}
	out << tabledata;

	for (auto& t : tables) {
		std::cout << t << " table dumped\n";
	}std::cout << '\n';
	std::cout << "Exported to CSV file. Press enter to continue...";
	std::cin.get();
	system("cls");
}