#ifndef __TableFixture_h__
#define __TableFixture_h__

#include "pch.h"
#include "Table.h"
#include "DBManager.h"

using EmployeeDB::Model::Table;
using EmployeeDB::DBManager;

class TableFixture : public ::testing::Test {
protected:
	void SetUp() override {
		table = std::make_unique<Table>();

		table->setTableName("Salary");

		std::vector<std::array<std::string, 3>> columns;
		columns.reserve(3);
		std::vector<std::array<std::string, 4>> foreignKeys;

		columns.emplace_back(std::move(std::array<std::string, 3>{"ID", "INT", "NOT NULL UNIQUE PRIMARY KEY"}));
		columns.emplace_back(std::move(std::array<std::string, 3>{"baseSalary", "REAL", "NOT NULL"}));
		columns.emplace_back(std::move(std::array<std::string, 3>{"bonus", "REAL", "NOT NULL"}));
		columns.emplace_back(std::move(std::array<std::string, 3>{"allowance", "REAL"}));

		table->setColumns(columns);

		foreignKeys.emplace_back(std::move(std::array<std::string, 4>{"ID", "Employee", "employeeID", "ON DELETE CASCADE"}));

		table->setForeignKeyConstraint(foreignKeys);

		emptyTable = std::make_unique<Table>();
		emptyTable->setTableName("Roles");
	}

	void TearDown() override {
		std::string_view queryString = "DROP TABLE IF EXISTS Roles";
		DBManager::instance().executeQuery(queryString.data());

		queryString = "DROP TABLE IF EXISTS Salary";
		DBManager::instance().executeQuery(queryString.data());
	}

	std::unique_ptr<Table> table;
	std::unique_ptr<Table> emptyTable;
};

#endif // !__TableFixture_h__