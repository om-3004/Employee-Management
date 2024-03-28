#ifndef _viewFinance_h_
#define _viewFinance_h_
#include "../model/Finance.h"

namespace EmployeeDB::Console {

	void financeMenu() noexcept;
	void operationOfFin(const char& input) noexcept;
	bool insertInFinance();
	bool deleteInFinance();
	bool updateInFinance();
	bool viewInFinance();
}


#endif