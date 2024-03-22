#ifndef __Engineer_h__
#define __Engineer_h__

#include "Employee.h"

namespace EmployeeDB::Model {

    class Engineer : public Employee {
    public:
        Engineer() : technology{ "" } {}
        Engineer(bool isUpdateObj) : Employee{ isUpdateObj }, technology{ "#" } {}

        const std::string& getTechnology() const {  
            return technology;
        }

        void setTechnology(const std::string& tech) {
            technology = tech;
        }

    private:
        std::string technology;
    };
}

#endif
