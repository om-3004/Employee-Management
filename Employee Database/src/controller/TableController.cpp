#include<iostream>
#include<string>
#include "TableController.h"
#include "DBManager.h"

std::string EmployeeDB::Controller::TableController::createTableQuery(EmployeeDB::Model::Table& tab, int columnCount, int keyCount) {
	std::string query;
	query = "CREATE TABLE ";
	query += "\"";
	query += tab.getTableName();
	query += "\"";
	query += "(";

	auto colCount = columnCount;
	auto kCount = keyCount;

	for (auto i = 0; i < colCount; i++) {
		auto& col = tab.getColumns()[i];
		auto& [columnName, columnType, columnConstraint] = col;
		query += "\"";
		query += columnName;
		query += "\" ";
		query += columnType;
		query += " ";
		if (columnConstraint.size() != 0) {
			query += columnConstraint;
			if (tab.getForeignKeyConstraint().size() != 0) {
				query += ",";
			}
			else if (columnCount > 1) {
				query += ",";
				columnCount--;
			}
		}
		else if (tab.getForeignKeyConstraint().size() != 0) {
			query += ",";
		}
		else if (columnCount > 1) {
			query += ",";
			columnCount--;
		}
	}

	if (tab.getForeignKeyConstraint().size() != 0) {
		for (auto i = 0; i < kCount; i++) {
			auto& key = tab.getForeignKeyConstraint()[i];
			auto& [columnName, ParentTableName, ParentTablecolName, Constraints] = key;
			query += "FOREIGN KEY";
			query += " (";
			query += "\"";
			query += columnName;
			query += "\"";
			query += ") ";
			query += "REFERENCES ";
			query += "\"";
			query += ParentTableName;
			query += "\"";
			query += "(";
			query += "\"";
			query += ParentTablecolName;
			query += "\"";
			query += ") ";
			if (Constraints.size() != 0) {
				query += Constraints;
			}
			if (keyCount > 1) {
				query += ",";
				keyCount--;
			}
		}
	}

	query += ");";

	return std::move(query);
}

bool EmployeeDB::Controller::TableController::deleteTableQuery(const std::string& tableName) {
	std::string query;
	query = "DROP TABLE ";
	query += "\"";
	query += tableName;
	query += "\" ;";

	try {
		EmployeeDB::DBManager::instance().executeQuery(query.c_str());
		std::cout << "\x1B[32mSuccessfully deleted Table:" << tableName << ".\033[0m\n";
		return true;
	}
	catch (const std::exception& e) {
		std::cerr << "\x1B[31m" << e.what() << "\033[0m\n";
		return false;
	}
}

bool EmployeeDB::Controller::TableController::executeCreateQuery(EmployeeDB::Model::Table& tab, int columnCount, int keyCount) {
	std::string queryString = createTableQuery(tab, columnCount, keyCount);

	try {
		DBManager::instance().executeQuery(queryString.c_str());
		std::cout << "\033[32m" << "Successfully Created Table : " << tab.getTableName() << "\033[0m\n";
	}
	catch (const std::exception& e) {
		std::cerr << "\033[31m" << e.what() << "\033[0m\n";
		std::cerr << "\033[31m" << "Table " << tab.getTableName() << " could not be created." << "\033[0m\n";
		return false;
	}
	return true;
}