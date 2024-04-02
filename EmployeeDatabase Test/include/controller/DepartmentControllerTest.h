#ifndef __DepartmentControllerTest_h__
#define __DepartmentControllerTest_h__

#include "DepartmentController.h"

class DepartmentControllerTest : public EmployeeDB::Controller::DepartmentController {
public:
	static std::string getUpdateQueryCondition(Department& dept) {
		return EmployeeDB::Controller::DepartmentController::getUpdateQueryCondition(dept);
	}
};

#endif