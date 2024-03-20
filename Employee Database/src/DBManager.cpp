#include "../../include/DBManager.h"
#include "../../include/Config.h"
#include "exception"
#include <iostream>
#include <iomanip>

using EmployeeDB::DBManager;

DBManager& DBManager::instance() {
	static DBManager DB;
	return DB;
}

DBManager::DBManager() {
	openConnection();
}

DBManager::~DBManager() {
	closeConnection();
}

void DBManager::openConnection() {
	resultCode = sqlite3_open(EmployeeDB::Config::dbFilePath.string().c_str(), &db);

	if (resultCode != SQLITE_OK) {
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	else {
		std::cout << "Opened database file successfully" << '\n';
	}
}

void DBManager::closeConnection() {
	resultCode = sqlite3_close(db);

	if (resultCode != SQLITE_OK) {
		throw std::runtime_error(sqlite3_errmsg(db));
	}
	else {
		std::cout << "Closed database file successfully" << '\n';
	}
}

int DBManager::executeQuery(const char* queryString) {
	resultCode = sqlite3_exec(db, queryString, 0, 0, &errMsg);

	if (resultCode == SQLITE_OK) {
		std::cout << "Successfully executed Query" << '\n';
	}
	else {
		throw std::runtime_error{ errMsg };
	}

	return resultCode;
}

int DBManager::callback(void* arg, int argc, char** argv, char** azColName) {
	std::cout << "|--------------------|----------------------------------------|\n";
	int i;
	for (i = 0; i < argc; i++) {
		std::cout << "|" << std::setw(20) << std::left << azColName[i] << "|" << std::setw(40) << std::left << (argv[i] ? argv[i] : "NULL") << "|\n";
	}
	std::cout << "|--------------------|----------------------------------------|\n";
	std::cout << std::endl;
	return 0;
}

int DBManager::executeSelectQuery(const char* queryString, int (*callback)(void*, int, char**, char**), void* arg) {
	resultCode = sqlite3_exec(db, queryString, callback, arg, &errMsg);

	if (resultCode == SQLITE_OK) {
		std::cout << "Successfully executed Query" << '\n';
	}
	else {
		throw std::runtime_error{ errMsg };
	}

	return resultCode;
}

void DBManager::executeCascadeQuery() {
	std::string queryString = "PRAGMA foreign_keys = ON";

	try {
		instance().executeQuery(queryString.c_str());
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}