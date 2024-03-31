#ifndef __Table_H__
#define __Table_H__

#include<string>
#include<array>
#include<vector>

namespace EmployeeDB::Model {

	class Table {
	public:
		void setTableName(std::string& tablename) {
			tableName = tablename;
		}
		const std::string& getTableName() {
			return tableName;
		}
		void setForeignKeyConstraint(std::vector<std::array<std::string, 4>> foreign) {
			foreignKeyConstraint = std::move(foreign);
		}
		const std::vector<std::array<std::string, 4>>& getForeignKeyConstraint() {
			return foreignKeyConstraint;
		}
		void setColumns(std::vector<std::array<std::string, 3>>& col) {
			columns = std::move(col);
		}
		const std::vector<std::array<std::string, 3>>& getColumns() {
			return columns;
		}
	private:
		std::string tableName;
		std::vector<std::array<std::string, 3>> columns;
		std::vector<std::array<std::string, 4>> foreignKeyConstraint;
	};

}

#endif