#ifndef __FinanceControllerTest_h__
#define __FinanceControllerTest_h__

#include "pch.h"
#include "FinanceController.h"
#include "Finance.h"

class FinanceControllerTest : public EmployeeDB::Controller::FinanceController {
public:
	static std::string getUpdateQueryCondition(Finance& fin) {
		return EmployeeDB::Controller::FinanceController::getUpdateQueryCondition(fin);
	}
};

#endif