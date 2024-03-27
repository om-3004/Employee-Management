#ifndef __common_h_
#define __common_h_
#include <iostream>
#include <string>
#include "../Validator.h"
#include "../model/Employee.h"

namespace EmployeeDB::Console {

	int inputID(const std::string_view& op, const std::string_view& ent);

	void printEmpFields(const std::string_view& empType);
	void printEmpFieldsWithID(const std::string_view& empType);

	bool repeatUpdateField(bool& x);

	bool dltConfirmation(const int& id, const std::string_view& ent);

	bool repeatOperation(const std::string& op, const std::string& ent);

	std::string trim(std::string str, const std::string chars = "\t\n\v\f\r ");

	void askUserInput(EmployeeDB::Model::Employee& e);

	std::string checkInput(const std::string& s);

	void matchInpField(const std::string& inputField, std::string& arg1, std::string& arg2);

	void updateEmp(const std::string& input, EmployeeDB::Model::Employee& e);

	void matchInpFieldDept(const std::string& inputField, std::string& arg1, std::string& arg2);

	bool viewOperation(char& input);

	bool insertOperation(char& input, const std::string_view& empType);
};

#endif