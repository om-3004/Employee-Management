#ifndef _viewHR_h_
#define _viewHR_h_
#include "../model/HR.h"

namespace EmployeeDB::Console {

	void HRMenu() noexcept;
	void operationOfHR(const char& input) noexcept;
	bool insertHR();
	bool deleteHR();
	bool updateHR();
	bool viewHR();
}


#endif