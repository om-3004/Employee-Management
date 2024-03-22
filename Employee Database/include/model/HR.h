#ifndef __HR_h__
#define __HR_h__

#include "Employee.h"

namespace EmployeeDB::Model {

    class HR : public Employee {
    public:
        HR() : hrSpecialization{ "" } {}
        HR(bool isUpdateObj) : Employee{ isUpdateObj }, hrSpecialization{ "#" } {}

        const std::string& getHRSpecialization() const {
            return hrSpecialization;
        }

        void setHRSpecialization(const std::string& specialization) {
            hrSpecialization = specialization;
        }

    private:
        std::string hrSpecialization;
    };
}

#endif
