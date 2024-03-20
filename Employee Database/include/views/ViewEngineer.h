#ifndef _viewEngineer_h_
#define _viewEngineer_h_
#include "../model/Engineer.h"

namespace EmployeeDB::Console {

	void inEngineer();
	void operationOfEng(const char& input);
	bool insertEngineer();
	bool deleteEngineer();
	bool updateEngineer();
	bool viewEngineer();
}


#endif