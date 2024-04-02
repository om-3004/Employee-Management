#ifndef __QAControllerTest_h__
#define __QAControllerTest_h__

#include "QAController.h"

using EmployeeDB::Controller::QAController;

class QAControllerTest : public QAController {
public:
	static std::string getUpdateQueryCondition(QA& qa) {
		return QAController::getUpdateQueryCondition(qa);
	}
};

#endif