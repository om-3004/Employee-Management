#ifndef __TableControllerTest_h__
#define __TableControllerTest_h__

#include "TableController.h"

using EmployeeDB::Controller::TableController;

class TableControllerTest : public TableController {
public:
	static std::string createTableQuery(EmployeeDB::Model::Table& table, int columnCount, int keyCount) {
		return TableController::createTableQuery(table, columnCount, keyCount);
	}
};

#endif