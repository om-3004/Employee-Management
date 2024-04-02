#ifndef __EngineerControllerTest_h__
#define __EngineerControllerTest_h__

#include "pch.h"
#include "EngineerController.h"
#include "Engineer.h"

class EngineerControllerTest : public EmployeeDB::Controller::EngineerController {
public:
	static std::string getUpdateQueryCondition(Engineer& eng) {
		return EmployeeDB::Controller::EngineerController::getUpdateQueryCondition(eng);
	}
};

#endif