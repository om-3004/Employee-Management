#ifndef __Department_h__
#define __Department_h__

#include <string>

namespace EmployeeDB::Model {

    class Department {
    public:
        Department() :
            departmentName{ "" },
            departmentID{ 0 },
            baseSalary{ 0.0 },
            allowance{ 0.0 },
            deduction{ 0.0 } {
        }

        Department(bool isUpdateObj) :
            departmentName{ "#" },
            departmentID{ -1 },
            baseSalary{ -1.0 },
            allowance{ -1.0 },
            deduction{ -1.0 } {
        }

        int getDepartmentID() const {
            return departmentID;
        }

        void setDepartmentID(int id) {
            departmentID = id;
        }

        const std::string& getDepartmentName() const {
            return departmentName;
        }

        void setDepartmentName(const std::string& deptname) {
            departmentName = deptname;
        }

        void setName(const std::string& deptName) {
            departmentName = deptName;
        }

        double getBaseSalary() const {
            return baseSalary;
        }

        void setBaseSalary(double salary) {
            baseSalary = salary;
        }

        double getAllowance() const {
            return allowance;
        }

        void setAllowance(double allowanceAmount) {
            allowance = allowanceAmount;
        }

        double getDeduction() const {
            return deduction;
        }

        void setDeduction(double deductionAmount) {
            deduction = deductionAmount;
        }

    private:
        int departmentID;
        std::string departmentName;
        double baseSalary;
        double allowance;
        double deduction;
    };
}


#endif // !_Department_h_
