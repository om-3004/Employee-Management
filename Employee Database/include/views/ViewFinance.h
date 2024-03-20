#ifndef _viewFinance_h_
#define _viewFinance_h_
#include "../model/Finance.h"

namespace EmployeeDB::Console {

	void inFinance();
	void operationOfFin(const char& input);
	bool insertInFinance();
	bool deleteInFinance();
	bool updateInFinance();
	bool viewInFinance();
}


#endif