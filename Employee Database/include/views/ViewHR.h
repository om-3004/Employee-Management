#ifndef _viewHR_h_
#define _viewHR_h_
#include "../model/HR.h"

namespace EmployeeDB::Console {

	void inHR();
	void operationOfHR(const char& input);
	bool insertHR();
	bool deleteHR();
	bool updateHR();
	bool viewHR();
}


#endif