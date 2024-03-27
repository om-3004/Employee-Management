#include <exception>
#include <iomanip>
#include "DepartmentController.h"
#include "DBManager.h"

using EmployeeDB::Controller::DepartmentController;
using EmployeeDB::DBManager;

bool DepartmentController::insertDepartment(const Department& obj) {
	std::string queryString = "INSERT INTO Department (departmentName, baseSalary, allowance, deduction) "
		+ std::string{ "VALUES (" } +
		"\"" + obj.getDepartmentName() + "\"" + ", " +
		std::to_string(obj.getBaseSalary()) + ", " +
		std::to_string(obj.getAllowance()) + ", " +
		std::to_string(obj.getDeduction()) + ");";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
		std::cout << "Successfully inserted a Department.\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::cerr << "Department could not be inserted.\n";
		return false;
	}
	return true;
}

int DepartmentController::getDepartmentIDbyName(const std::string_view& departmentName) {
	std::string deptName = static_cast<std::string>(departmentName);
	std::string queryString = "SELECT departmentID FROM Department WHERE departmentName = \"" + deptName + "\";";
	int departmentID{ -1 };

	auto getDepartmentIDCallback = [](void* data, int argc, char** argv, char** azColName) -> int {
		int* eId = static_cast<int*>(data);
		if (!strcmp(azColName[0], "departmentID")) {
			*eId = std::stoi(argv[0]);
		}
		return 0;
		};

	try {
		DBManager::instance().executeCustomQuery(queryString.c_str(), getDepartmentIDCallback, &departmentID);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}

	return departmentID;
}

bool DepartmentController::checkDepartmentExistence(const std::string& departmentID) {
	std::string queryString = "SELECT departmentID FROM Department WHERE departmentID = " + departmentID + ";";

	int callbackCount{ 0 };

	try {
		callbackCount = DBManager::instance().executeRowCountQuery(queryString.c_str());
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	if (callbackCount == 0) {
		return false;
	}

	return true;
}

bool DepartmentController::selectDepartment(const std::string& attributeName, const std::string& attributeValue) {
	std::string queryString = "SELECT * FROM Department " + ((attributeName.size() != 0) ? "WHERE " + attributeName + " = \"" + attributeValue + "\"" : "") + ";";

	try {
		int rowCount = DBManager::instance().executeSelectQuery(queryString.c_str());
		std::cout << rowCount << std::string{ " record" } + (rowCount > 1 ? "s" : "") + " found\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
};

bool DepartmentController::deleteDepartmentByID(int ID) {
	std::string queryString = "DELETE FROM Department WHERE departmentID = " + std::to_string(ID) + ";";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
		std::cout << "Successfully deleted a Department.\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::cerr << "Department could not be deleted.\n";
		return false;
	}
	return true;
}

std::string DepartmentController::getUpdateQueryCondition(Department& obj) {
	std::string updateQueryCondition{ "" };

	if (obj.getDepartmentName() != "#") {
		updateQueryCondition += "departmentName = \"" + obj.getDepartmentName() + "\"";
	}
	if (obj.getBaseSalary() != -1.0) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "baseSalary = " + std::to_string(obj.getBaseSalary());
	}
	if (obj.getAllowance() != -1.0) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "allowance = " + std::to_string(obj.getAllowance());
	}
	if (obj.getDeduction() != -1.0) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "deduction = " + std::to_string(obj.getDeduction());
	}

	return updateQueryCondition;
}

bool DepartmentController::updateDepartment(Department& obj) {

	std::string updateQueryCondition = getUpdateQueryCondition(obj);

	if (updateQueryCondition.size() != 0) {
		std::string queryString = "UPDATE Department SET " + updateQueryCondition + " WHERE departmentID = " + std::to_string(obj.getDepartmentID()) + ";";
		try {
			DBManager::instance().executeQuery(queryString.c_str());
			std::cout << "Successfully updated a Department.\n";
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			std::cerr << "Department could not be updated.\n";
			return false;
		}
	}
	return true;
}