#ifndef _viewDepartment_h_
#define _viewDepartment_h_
#include "../model/Department.h"

namespace EmployeeDB::Console {

	void inDepartment();
	void operationOfDept(const char& input);
	bool insertDept();
	bool deleteDept();
	bool updateDept();
	bool viewDept();
}

#endif