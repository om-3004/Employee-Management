#ifndef _viewQA_h_
#define _viewQA_h_
#include "../model/QA.h"

namespace EmployeeDB::Console {

	void inQA() noexcept;
	void operationOfQA(const char& input) noexcept;
	bool insertInQA();
	bool deleteInQA();
	bool updateInQA();
	bool viewInQA();
}


#endif