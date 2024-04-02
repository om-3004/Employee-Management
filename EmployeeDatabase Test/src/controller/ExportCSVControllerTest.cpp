#include "ExportCSVControllerTest.h"
#include "ExportCSVFixture.h"
#include "pch.h"
#include <filesystem>

namespace fs = std::filesystem;
using EmployeeDB::Controller::ExportController;

TEST_F(ExportFixture, Test_exportToCSVSuccess) {
	EXPECT_TRUE(ExportController::exportToCSV("Manager", "Manager"));
	EXPECT_TRUE(ExportController::exportToCSV("Employee", "Employee"));
	EXPECT_TRUE(ExportController::exportToCSV("Department", "Department"));

	fs::path exportPath{ "./BackupTables_csv/Manager.csv" };
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/Employee.csv";
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/Department.csv";
	EXPECT_TRUE(fs::exists(exportPath));
}

TEST_F(ExportFixture, Test_exportToCSVFailure) {
	EXPECT_FALSE(ExportController::exportToCSV("Maaaaaanager", "Manager"));
}

TEST_F(ExportFixture, Test_exportAll) {
	EXPECT_TRUE(ExportController::exportAll());

	fs::path exportPath{ "./BackupTables_csv/ManagerBackup.csv" };
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/EmployeeBackup.csv";
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/DepartmentBackup.csv";
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/EngineerBackup.csv";
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/HRBackup.csv";
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/QABackup.csv";
	EXPECT_TRUE(fs::exists(exportPath));

	exportPath = "./BackupTables_csv/FinanceBackup.csv";
	EXPECT_TRUE(fs::exists(exportPath));
}

TEST_F(ExportFixture, Test_removecommas) {
	std::string stringToTest{ "34, Grove Street, Ganton, Los Santos" };

	ExportControllerTest::removecommas(stringToTest);

	EXPECT_STREQ("34 Grove Street Ganton Los Santos", stringToTest.c_str());
}