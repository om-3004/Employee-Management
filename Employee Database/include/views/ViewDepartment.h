#ifndef _viewDepartment_h_
#define _viewDepartment_h_
#include "../model/Department.h"

namespace EmployeeDB::Console {

	void inDepartment() noexcept;
	void operationOfDept(const char& input) noexcept;
	bool insertDept();
	bool deleteDept();
	bool updateDept();
	bool viewDept();
}

#endif