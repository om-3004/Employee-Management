#ifndef __DBmanager_h__
#define __DBmanager_h__

#include "sqlite3.h"
#include <string>

namespace EmployeeDB {

	class DBManager {
	public:
		static DBManager& instance();

		int executeQuery(const char* query);
		int executeSelectQuery(const char* query, int (*callback)(void*, int, char**, char**) = DBManager::callback, void* arg = 0);
		static void executeCascadeQuery();

	private:
		DBManager();
		~DBManager();

		void openConnection();
		void closeConnection();

		static int callback(void* arg, int argc, char** argv, char** azColName);

		sqlite3* db;
		int resultCode;
		char* errMsg;
	};
}


#endif // !_DBmanager_h_
