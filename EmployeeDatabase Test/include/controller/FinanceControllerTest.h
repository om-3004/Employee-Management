#ifndef __FinanceControllerTest_h__
#define __FinanceControllerTest_h__

#include "pch.h"
#include "FinanceController.h"
#include "Finance.h"

using EmployeeDB::Controller::FinanceController;

class FinanceControllerTest : public FinanceController {
public:
	static std::string getUpdateQueryCondition(Finance& fin) {
		return FinanceController::getUpdateQueryCondition(fin);
	}
};

#endif