#include <exception>
#include "EmployeeController.h"
#include "DepartmentController.h"
#include "DBManager.h"

using EmployeeDB::Controller::EmployeeController, EmployeeDB::Controller::DepartmentController;
using EmployeeDB::DBManager;

bool EmployeeController::insertEmployee(const Employee& obj) {
	std::string queryString = "INSERT INTO Employee (firstName, middleName, lastName, dateOfBirth, mobileNumber, email, address, gender, dateOfJoining, departmentID, mentorID, performanceMetric, bonus) "
		+ std::string{ "VALUES (" } +
		"\"" + obj.getFirstName() + "\"" + ", " +
		(obj.getMiddleName().size() == 0 ? "NULL" : "\"" + obj.getMiddleName() + "\"") + ", " +
		"\"" + obj.getLastName() + "\"" + ", " +
		(obj.getDateOfBirth().size() == 0 ? "NULL" : "\"" + obj.getDateOfBirth() + "\"") + ", " +
		std::to_string(obj.getMobileNo()) + ", " +
		"\"" + obj.getEmail() + "\"" + ", " +
		"\"" + obj.getAddress() + "\"" + ", " +
		"\"" + EmployeeDB::Model::getGenderString(obj.getGender()) + "\"" + ", " +
		"\"" + obj.getDateOfJoining() + "\"" + ", " +
		std::to_string(obj.getDepartmentID()) + ", " +
		std::to_string(obj.getMentorID()) + ", " +
		(obj.getPerformanceMetric() == 0.0 ? "NULL" : std::to_string(obj.getPerformanceMetric())) + ", " +
		(obj.getBonus() == 0.0 ? "NULL" : std::to_string(obj.getBonus())) + ");";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}

int EmployeeController::getEmployeeIDbyEmail(const std::string& email) {
	std::string queryString = "SELECT employeeID FROM Employee WHERE email = \"" + email + "\";";
	int employeeID{ -1 };

	auto getEmployeeIDCallback = [](void* data, int argc, char** argv, char** azColName) -> int {
		int* eId = static_cast<int*>(data);
		if (!strcmp(azColName[0], "employeeID")) {
			*eId = std::stoi(argv[0]);
		}
		return 0;
		};

	try {
		DBManager::instance().executeCustomQuery(queryString.c_str(), getEmployeeIDCallback, &employeeID);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return -1;
	}

	return employeeID;
}

int EmployeeController::getDepartmentIDbyEmployeeID(int ID) {
	std::string queryString = "SELECT departmentID FROM Employee WHERE employeeID = " + std::to_string(ID) + ";";
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

bool EmployeeController::checkEmployeeExistence(const std::string& employeeID, const std::string& departmentName) {

	int departmentID{ -1 };

	if (departmentName != "*") {
		departmentID = DepartmentController::getDepartmentIDbyName(departmentName);
		if (departmentID == -1) {
			return false;
		}
	}

	std::string queryString = "SELECT employeeID FROM Employee WHERE employeeID = " + employeeID + (departmentID == -1 ? "" : " AND departmentID = " + std::to_string(departmentID)) + ";";

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

bool EmployeeController::deleteEmployeeByID(int ID) {
	std::string queryString = "DELETE FROM Employee WHERE employeeID = " + std::to_string(ID) + ";";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}

std::string EmployeeController::getUpdateQueryCondition(Employee& obj) {
	std::string updateQueryCondition{ "" };

	if (obj.getFirstName() != "#") {
		updateQueryCondition += "firstName = \"" + obj.getFirstName() + "\"";
	}
	if (obj.getMiddleName() != "#") {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "middleName = \"" + obj.getMiddleName() + "\"";
	}
	if (obj.getLastName() != "#") {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "lastName = \"" + obj.getLastName() + "\"";
	}
	if (obj.getDateOfBirth() != "#") {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "dateOfBirth = \"" + obj.getDateOfBirth() + "\"";
	}
	if (obj.getMobileNo() != -1) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "mobileNumber = " + std::to_string(obj.getMobileNo());
	}
	if (obj.getEmail() != "#") {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "email = \"" + obj.getEmail() + "\"";
	}
	if (obj.getAddress() != "#") {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "address = \"" + obj.getAddress() + "\"";
	}
	if (obj.getGender() != EmployeeDB::Model::Gender::Other) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "gender = \"" + EmployeeDB::Model::getGenderString(obj.getGender()) + "\"";
	}
	if (obj.getDateOfJoining() != "#") {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "dateOfJoining = \"" + obj.getDateOfJoining() + "\"";
	}
	if (obj.getMentorID() != -1) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "mentorID = " + std::to_string(obj.getMentorID());
	}
	if (obj.getPerformanceMetric() != -1.0) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "performanceMetric = " + std::to_string(obj.getPerformanceMetric());
	}
	if (obj.getBonus() != -1.0) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "bonus = " + std::to_string(obj.getBonus());
	}

	return updateQueryCondition;
}

bool EmployeeController::updateEmployee(Employee& obj) {

	std::string updateQueryCondition = getUpdateQueryCondition(obj);

	if (updateQueryCondition.size() != 0) {
		std::string queryString = "UPDATE Employee SET " + updateQueryCondition + " WHERE employeeID = " + std::to_string(obj.getEmployeeID()) + ";";

		try {
			DBManager::instance().executeQuery(queryString.c_str());
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}
	return true;
}

bool EmployeeController::getSalaryDetails(Salary& obj) {
	std::string queryString = "SELECT * FROM SalaryView WHERE employeeID = " + std::to_string(obj.getEmployeeID()) + ";";

	auto getSalaryDetailsCallback = [](void* data, int argc, char** argv, char** azColName) -> int {
		Salary* salaryObj = static_cast<Salary*>(data);

		salaryObj->setDepartmentID(std::stoi(argv[1]));
		salaryObj->setPerformanceMetric(std::stod(argv[2]));
		salaryObj->setBonus(std::stod(argv[3]));
		salaryObj->setBaseSalary(std::stod(argv[4]));
		salaryObj->setAllowance(std::stod(argv[5]));
		salaryObj->setDeduction(std::stod(argv[6]));
		return 0;
		};

	try {
		DBManager::instance().executeCustomQuery(queryString.c_str(), getSalaryDetailsCallback, &obj);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
	return true;
}