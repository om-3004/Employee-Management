#ifndef __EngineerControllerTest_h__
#define __EngineerControllerTest_h__

#include "pch.h"
#include "EngineerController.h"
#include "Engineer.h"

using EmployeeDB::Controller::EngineerController;

class EngineerControllerTest : public EngineerController {
public:
	static std::string getUpdateQueryCondition(Engineer& eng) {
		return EngineerController::getUpdateQueryCondition(eng);
	}
};

#endif