	#include <exception>
#include "ManagerController.h"
#include "EmployeeController.h"
#include "DBManager.h"

using EmployeeDB::Controller::ManagerController, EmployeeDB::Controller::EmployeeController;

bool ManagerController::insertManager(Manager& obj) {

	/*int departmentID = EmployeeController::getDepartmentIDbyEmployeeID(obj.getManagerID());

	if (departmentID == -1) {
		std::cerr << "Department was not found for provided managerID.";
		return false;
	}*/

	//obj.setDepartmentID(departmentID);

	std::string queryString = "INSERT INTO Manager (managerID, departmentID, teamSize, yearsOfExp, projectTitle, role) VALUES (" +
		std::to_string(obj.getManagerID()) + ", " +
		std::to_string(obj.getDepartmentID()) + ", " +
		std::to_string(obj.getTeamSize()) + ", " +
		std::to_string(obj.getYearsOfExp()) + ", " +
		(obj.getProjectTitle().has_value() ? "\"" + obj.getProjectTitle().value() + "\"" : "NULL") + "," +
		(obj.getRole().has_value() ? "\"" + obj.getRole().value() + "\"" : "NULL") + ");";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
		std::cout << "Successfully inserted a Manager.\n";
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		std::cerr << "Manager could not be inserted.\n";
		return false;
	}
	return true;
}

bool ManagerController::selectManager(const std::string& attributeName, const std::string& attributeValue) {
	std::string queryString = "SELECT * FROM ManagerView " + ((attributeName.size() != 0) ? "WHERE " + attributeName + " = \"" + attributeValue + "\"" : "") + ";";

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

bool ManagerController::deleteManagerByID(int ID) {
	std::string queryString = "DELETE FROM Manager WHERE managerID = " + std::to_string(ID) + ";";

	try {
		DBManager::instance().executeQuery(queryString.c_str());
		std::cout << "Successfully deleted a Manager.\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		std::cerr << "Manager could not be deleted.\n";
		return false;
	}
	return true;
};

std::string ManagerController::getUpdateQueryCondition(Manager& obj) {
	std::string updateQueryCondition{ "" };

	if (obj.getTeamSize() != -1) {
		updateQueryCondition += "teamSize = " + std::to_string(obj.getTeamSize());
	}
	if (obj.getYearsOfExp() != -1) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "yearsOfExp = " + std::to_string(obj.getYearsOfExp());
	}
	if (obj.getProjectTitle().has_value()) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "projectTitle = \"" + obj.getProjectTitle().value() + "\"";
	}
	if (obj.getRole().has_value()) {
		if (updateQueryCondition.size() != 0) {
			updateQueryCondition += ", ";
		}
		updateQueryCondition += "role = \"" + obj.getRole().value() + "\"";
	}

	return updateQueryCondition;
}

bool ManagerController::updateManager(Manager& obj) {
	bool employeeResult = EmployeeController::updateEmployee(obj);

	if (!employeeResult) {
		std::cerr << "Manager could not be updated.\n";
		return false;
	}

	std::string updateQueryCondition = getUpdateQueryCondition(obj);

	if (updateQueryCondition.size() != 0) {
		std::string queryString = "UPDATE Manager SET " + updateQueryCondition + " WHERE managerID = " + std::to_string(obj.getManagerID()) + ";";
		try {
			DBManager::instance().executeQuery(queryString.c_str());
			std::cout << "Successfully updated a Manager.\n";
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			std::cerr << "Manager could not be updated.\n";
			return false;
		}
	}
	return true;
}

bool ManagerController::checkManagerExistence(const std::string& managerID) {
	std::string queryString = "SELECT managerID FROM Manager WHERE managerID = " + managerID + ";";

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
