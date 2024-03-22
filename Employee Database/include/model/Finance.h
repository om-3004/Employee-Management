#ifndef __Finance_h__
#define __Finance_h__
#include "Employee.h"

namespace EmployeeDB::Model {

    class Finance : public Employee {
    public:
        Finance() : accountingTool{ "" } {}
        Finance(bool isUpdateObj) : Employee{ isUpdateObj }, accountingTool{ "#" } {}

        const std::string& getAccountingTool() const {
            return accountingTool;
        }

        void setAccountingTool(const std::string& tool) {
            accountingTool = tool;
        }

    private:
        std::string accountingTool;
    };
}

#endif
