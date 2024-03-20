#ifndef _viewQA_h_
#define _viewQA_h_
#include "../model/QA.h"

namespace EmployeeDB::Console {

	void inQA();
	void operationOfQA(const char& input);
	bool insertInQA();
	bool deleteInQA();
	bool updateInQA();
	bool viewInQA();
}


#endif