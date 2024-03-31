#include<iostream>
#include<string>
#include "TableController.h"
#include "DBManager.h"

bool EmployeeDB::Controller::TableController::createTableQuery(EmployeeDB::Model::Table& tab, int columnCount, int keyCount) {
	std::string query;

	query = "CREATE TABLE \"" + tab.getTableName() + "\"(";
	/*query = "CREATE TABLE ";
	query += "\"";
	query += tab.getTableName();
	query += "\"";
	query += "(";*/

	for (auto& col : tab.getColumns()) {
		auto& [columnName, columnType, columnConstraint] = col;
		query += "\"" + columnName + "\" " + columnType + " ";
		/*query += "\"";
		query += columnName;
		query += "\" ";
		query += columnType;
		query += " ";*/
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
		for (auto& key : tab.getForeignKeyConstraint()) {
			auto& [columnName, ParentTableName, ParentTablecolName, Constraints] = key;

			query += "FOREIGN KEY (\"" + columnName + "\") REFERENCES \"" + ParentTableName + "\"(\"" + ParentTablecolName + "\")\n";
			/*query += "FOREIGN KEY";
			query += " (";
			query += "\"";
			query += columnName;
			query += "\" ";
			query += ") ";
			query += "REFERENCES ";
			query += "\"";
			query += ParentTableName;
			query += "\"";
			query += "(";
			query += "\"";
			query += ParentTablecolName;
			query += "\"";
			query += ") ";*/
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
	std::cout << query << "\n";
	try {
		EmployeeDB::DBManager::instance().executeQuery(query.c_str());
		std::cout << "\x1B[32mSuccessfully created Table:" << tab.getTableName() << ".\033[0m\n";
		return true;
	}
	catch (const std::exception& e) {
		std::cerr << "\x1B[31m" << e.what() << "\033[0m\n";
		return false;
	}
}

bool EmployeeDB::Controller::TableController::deleteTableQuery(std::string& tableName) {
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