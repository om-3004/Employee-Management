#ifndef __DepartmentControllerTest_h__
#define __DepartmentControllerTest_h__

#include "DepartmentController.h"

using EmployeeDB::Controller::DepartmentController;

class DepartmentControllerTest : public DepartmentController {
public:
	static std::string getUpdateQueryCondition(Department& dept) {
		return DepartmentController::getUpdateQueryCondition(dept);
	}
};

#endif