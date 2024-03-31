#ifndef __TableController_H__
#define __TableController_H__

#include <iostream>
#include "Table.h"

using EmployeeDB::Model::Table;

namespace EmployeeDB::Controller {
	class TableController {
	public:
		static bool createTableQuery(EmployeeDB::Model::Table& tab, int colCount, int keyCount);
		static bool deleteTableQuery(std::string& tableName);
	};
}

#endif
