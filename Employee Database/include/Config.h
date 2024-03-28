#ifndef _Config_h_
#define _Config_h_

#include <filesystem>

namespace EmployeeDB::Config {
	static std::filesystem::path dbFilePath = "./data/EmployeeDB.db";
	static std::filesystem::path CSVFilePath = "./BackupTables_csv";
}

#endif