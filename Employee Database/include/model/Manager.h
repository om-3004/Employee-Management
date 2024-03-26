#ifndef __Manager_h__
#define __Manager_h__

#include "Employee.h"

namespace EmployeeDB::Model {

    class Manager : public Employee {
    public:
        Manager() :
            managerID{ 0 },
            departmentID{ 0 },
            teamSize{ 0 },
            yearsOfExp{ 0 },
            projectTitle{ "" },
            role{ "" } {
        }

        Manager(bool isUpdateObj) : Employee(isUpdateObj),
            managerID{ 0 },
            departmentID{ 0 },
            teamSize{ 0 },
            yearsOfExp{ 0 },
            projectTitle{ "#" },
            role{ "#" } {
        }

        int getManagerID() const {
            return managerID;
        }

        void setManagerID(int id) {
            managerID = id;
        }

        int getDepartmentID() const {
            return departmentID;
        }

        void setDepartmentID(int id) {
            departmentID = id;
        }

        int getTeamSize() const {
            return teamSize;
        }

        void setTeamSize(int size) {
            teamSize = size;
        }

        double getYearsOfExp() const {
            return yearsOfExp;
        }

        void setYearsOfExp(double years) {
            yearsOfExp = years;
        }

        const std::string& getProjectTitle() const {
            return projectTitle;
        }

        void setProjectTitle(const std::string& title) {
            projectTitle = title;
        }

        const std::string& getRole() const {
            return role;
        }

        void setRole(const std::string& rl) {
            role = rl;
        }

    private:
        int managerID;
        int departmentID;
        int teamSize;
        double yearsOfExp;
        std::string projectTitle;
        std::string role;
    };
}

#endif