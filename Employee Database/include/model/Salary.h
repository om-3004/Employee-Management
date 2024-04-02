#ifndef __Salary_h__
#define __Salary_h__

namespace EmployeeDB::Model {

    class Salary {
    public:
        Salary() :
            employeeID{ 0 },
            departmentID{ 0 },
            performanceMetric{ 0.0 },
            bonus{ 0.0 },
            baseSalary{ 0.0 },
            allowance{ 0.0 },
            deduction{ 0.0 } {}

        int getEmployeeID() const {
            return employeeID;
        }
        void setEmployeeID(int empID) {
            employeeID = empID;
        }

        int getDepartmentID() const {
            return departmentID;
        }
        void setDepartmentID(int deptID) {
            departmentID = deptID;
        }

        double getPerformanceMetric() const {
            return performanceMetric;
        }
        void setPerformanceMetric(double amount) {
            performanceMetric = amount;
        }

        double getBonus() const {
            return bonus;
        }
        void setBonus(double amount) {
            bonus = amount;
        }

        double getBaseSalary() const {
            return baseSalary;
        }
        void setBaseSalary(double amount) {
            baseSalary = amount;
        }

        double getAllowance() const {
            return allowance;
        }
        void setAllowance(double amount) {
            allowance = amount;
        }

        double getDeduction() const {
            return deduction;
        }
        void setDeduction(double amount) {
            deduction = amount;
        }

        double computeSalary() const;
    private:
        int employeeID;
        int departmentID;
        double performanceMetric;
        double bonus;
        double baseSalary;
        double allowance;
        double deduction;
    };

    inline double Salary::computeSalary() const {
        auto totalSalary{ 0.0 };

        totalSalary += this->getBaseSalary();
        totalSalary += this->getAllowance();
        totalSalary -= this->getDeduction();
        totalSalary += this->getBonus();
        totalSalary += (this->getBaseSalary() * (this->getPerformanceMetric() / 100));

        return totalSalary;
    }
}

#endif