#ifndef __ManagerControllerTest_h__
#define __ManagerControllerTest_h__

#include "pch.h"
#include "ManagerController.h"
#include "Manager.h"

using EmployeeDB::Controller::ManagerController;

class ManagerControllerTest : public ManagerController {
public:
	static std::string getUpdateQueryCondition(Manager& man) {
		return ManagerController::getUpdateQueryCondition(man);
	}
};

#endif