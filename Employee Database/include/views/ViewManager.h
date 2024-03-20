#ifndef _viewManager_h_
#define _viewManager_h_
#include "../model/Manager.h"

namespace EmployeeDB::Console {

	void inManager();
	void operationOfMan(const char& input);
	bool makeManager();
	bool deleteManager();
	bool updateManager();
	bool viewManager();
}


#endif