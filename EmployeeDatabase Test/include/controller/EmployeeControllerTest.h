#ifndef __EmployeeControllerTest_h__
#define __EmployeeControllerTest_h__

#include "pch.h"
#include "EmployeeController.h"
#include "Employee.h"

using EmployeeDB::Controller::EmployeeController;

class EmployeeControllerTest : public EmployeeController {
public:
	static std::string getUpdateQueryCondition(EmployeeDB::Model::Employee& emp) {
		return EmployeeController::getUpdateQueryCondition(emp);
	}
};

#endif