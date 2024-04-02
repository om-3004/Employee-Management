#ifndef __HRControllerTest_h__
#define __HRControllerTest_h__

#include "HRController.h"

using EmployeeDB::Controller::HRController;

class HRControllerTest : public HRController {
public:
	static std::string getUpdateQueryCondition(HR& hr) {
		return HRController::getUpdateQueryCondition(hr);
	}
};

#endif