#ifndef __TableController_H__
#define __TableController_H__

#include <iostream>
#include "Table.h"

namespace EmployeeDB::Controller {
	class TableController {
	public:
		static bool deleteTableQuery(const std::string& tableName);
		static bool executeCreateQuery(EmployeeDB::Model::Table& tab, int columnCount, int keyCount);
	protected:
		static std::string createTableQuery(EmployeeDB::Model::Table& tab, int columnCount, int keyCount);
	};
}

#endif