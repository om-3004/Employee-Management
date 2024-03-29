#include <exception>
#include "DBManager.h"
#include "FinanceController.h"
#include "EmployeeController.h"
#include "DepartmentController.h"

using EmployeeDB::Controller::EmployeeController;
using EmployeeDB::Controller::FinanceController;
using EmployeeDB::Controller::DepartmentController;
using EmployeeDB::DBManager;

bool FinanceController::insertFinance(Finance& obj) {
	int departmentID = DepartmentController::getDepartmentIDbyName("Finance");

	if (departmentID == -1) {
		std::cerr << "\x1B[31mFinance department not found. Please insert a department named Finance.\033[0m\n";
		return false;
	}

	obj.setDepartmentID(departmentID);

	bool employeeResult = EmployeeController::insertEmployee(obj);

	if (!employeeResult) {
		std::cerr << "\x1B[31mFinance could not be inserted.\033[0m\n";
		return false;
	}

	int employeeID = EmployeeController::getEmployeeIDbyEmail(obj.getEmail());

	std::string queryString = "INSERT INTO Finance (employeeID, accountingTool) VALUES (" +
		std::to_string(employeeID) + ", " +
		"\"" + obj.getAccountingTool() + "\");";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
		std::cout << "\x1B[32mSuccessfully inserted a Finance.\033[0m\n";
	}
	catch (const std::exception& e) {
		std::cerr << "\x1B[31m" << e.what() << "\033[0m\n";
		std::cerr << "\x1B[31mFinance could not be inserted.\033[0m\n";
		return false;
	}
	return true;
}

bool FinanceController::selectFinance(const std::string& attributeName, const std::string& attributeValue) {
	std::string queryString = "SELECT * FROM Employee NATURAL JOIN Finance " + ((attributeName.size() != 0) ? "WHERE " + attributeName + " = \"" + attributeValue + "\"  COLLATE NOCASE" : "") + ";";

	try {
		int rowCount = DBManager::instance().executeSelectQuery(queryString.c_str());
		std::cout << "x1B[33m" << rowCount << std::string{" record"} + (rowCount > 1 ? "s" : "") + " found\033[0m\n";
	}
	catch (const std::exception& e) {
		std::cerr << "\x1B[31m" << e.what() << "\033[0m\n";
		return false;
	}
	return true;
};

bool FinanceController::deleteFinanceByID(int ID) {
	bool deleteResult = EmployeeController::deleteEmployeeByID(ID);

	if (deleteResult) {
		std::cout << "\x1B[32mSuccessfully deleted a Finance.\033[0m\n";
	}
	else {
		std::cerr << "\x1B[31mFinance could not be deleted.\033[0m\n";
	}
	return deleteResult;
}

std::string FinanceController::getUpdateQueryCondition(Finance& obj) {
	std::string updateQueryCondition{ "" };

	if (obj.getAccountingTool() != "#") {
		updateQueryCondition = "accountingTool = \"" + obj.getAccountingTool() + "\"";
	}

	return updateQueryCondition;
}

bool FinanceController::updateFinance(Finance& obj) {

	bool employeeResult = EmployeeController::updateEmployee(obj);

	if (!employeeResult) {
		std::cerr << "\x1B[31mFinance could not be updated.\033[0m\n";
		return false;
	}

	std::string updateQueryCondition = getUpdateQueryCondition(obj);

	if (updateQueryCondition.size() != 0) {
		std::string queryString = "UPDATE Finance SET " + updateQueryCondition + " WHERE employeeID = " + std::to_string(obj.getEmployeeID()) + ";";

		try {
			DBManager::instance().executeQuery(queryString.c_str());
			std::cout << "\x1B[32mSuccessfully updated a Finance.\033[0m\n";
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			std::cerr << "\x1B[31mFinance could not be updated.\033[0m\n";
			return false;
		}
	}
	return true;
}