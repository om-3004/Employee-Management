#ifndef _viewManager_h_
#define _viewManager_h_
#include "../model/Manager.h"

namespace EmployeeDB::Console {

	void inManager() noexcept;
	void operationOfMan(const char& input) noexcept;
	bool makeManager();
	bool deleteManager();
	bool updateManager();
	bool viewManager();
}


#endif