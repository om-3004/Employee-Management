#ifndef __Employee_H__
#define __Employee_H__

#include <string>
#include <algorithm>
#include <optional>
#include "Salary.h"

namespace EmployeeDB::Model {

    enum class Gender {
        Male,
        Female,
        Other
    };

    class Employee {
    public:
        Employee() :
            m_FirstName{ "" },
            m_MiddleName{ "" },
            m_LastName{ "" },
            m_Email{ "" },
            m_Address{ "" },
            m_DateOfBirth{ "" },
            m_DateOfJoining{ "" },
            m_PerformanceMetric{ 0.0 },
            m_MobileNumber{ 0 },
            m_Gender{ Gender::Male },
            m_EmployeeID{ 0 },
            m_DepartmentID{ 0 },
            m_MentorID{ 0 },
            m_Bonus{ 0.0 } {
        }

        Employee(bool isUpdateObj) :
            m_FirstName{ "#" },
            m_MiddleName{ std::nullopt },
            m_LastName{ "#" },
            m_Email{ "#" },
            m_Address{ "#" },
            m_DateOfBirth{ std::nullopt },
            m_DateOfJoining{ "#" },
            m_PerformanceMetric{ std::nullopt },
            m_MobileNumber{ -1 },
            m_Gender{ Gender::Other },
            m_EmployeeID{ -1 },
            m_DepartmentID{ -1 },
            m_MentorID{ -1 },
            m_Bonus{ std::nullopt } {
        }

        void setFirstName(const std::string& firstName) {
            m_FirstName = firstName;
        }
        void setMiddleName(const std::string& middleName) {
            m_MiddleName = middleName;
        }
        void setLastName(const std::string& lastName) {
            m_LastName = lastName;
        }
        void setEmail(const std::string& email) {
            m_Email = email;
        }
        void setAddress(const std::string& address) {
            m_Address = address;
        }
        void setDateOfBirth(const std::string& dateOfBirth) {
            m_DateOfBirth = dateOfBirth;
        }
        void setDateOfJoining(const std::string& dateOfJoining) {
            m_DateOfJoining = dateOfJoining;
        }
        void setPerformanceMetric(double performanceMetric) {
            m_PerformanceMetric = performanceMetric;
        }
        void setBonus(double bonus) {
            m_Bonus = bonus;
        }
        void setMobileNo(long long mobileNumber) {
            m_MobileNumber = mobileNumber;
        }
        void setGender(Gender gender) {
            m_Gender = gender;
        }
        void setEmployeeID(int employeeID) {
            m_EmployeeID = employeeID;
        }
        void setDepartmentID(int departmentID) {
            m_DepartmentID = departmentID;
        }
        void setMentorID(int mentorID) {
            m_MentorID = mentorID;
        }

        const std::string& getFirstName() const {
            return m_FirstName;
        }
        const std::optional<std::string>& getMiddleName() const {
            return m_MiddleName;
        }
        const std::string& getLastName() const {
            return m_LastName;
        }
        const std::string& getEmail() const {
            return m_Email;
        }
        const std::string& getAddress() const {
            return m_Address;
        }
        const std::optional<std::string>& getDateOfBirth() const {
            return m_DateOfBirth;
        }
        const std::string& getDateOfJoining() const {
            return m_DateOfJoining;
        }
        std::optional<double> getPerformanceMetric() const {
            return m_PerformanceMetric;
        }
        std::optional<double> getBonus() const {
            return m_Bonus;
        }
        long long getMobileNo() const {
            return m_MobileNumber;
        }
        Gender getGender() const {
            return m_Gender;
        }
        int getEmployeeID() const {
            return m_EmployeeID;
        }
        int getDepartmentID() const {
            return m_DepartmentID;
        }
        int getMentorID() const {
            return m_MentorID;
        }

        static inline double computeSalary(Salary& obj);

    private:

        std::string m_FirstName;
        std::optional<std::string> m_MiddleName;
        std::string m_LastName;
        std::string m_Email;
        std::string m_Address;
        std::optional<std::string> m_DateOfBirth;
        std::string  m_DateOfJoining;
        std::optional<double> m_PerformanceMetric;
        std::optional<double> m_Bonus;
        long long m_MobileNumber;
        Gender m_Gender;
        int m_EmployeeID;
        int m_DepartmentID;
        int m_MentorID;
    };

    inline std::string getGenderString(Gender g) {
        std::string tempStr{ "Male" };
        switch (g) {
        case Gender::Male:
            break;
        case Gender::Female:
            tempStr = "Female";
            break;
        case Gender::Other:
            tempStr = "Other";
            break;
        }
        return tempStr;
    }

    inline Gender getGenderFromString(std::string& genderString) {
        Gender gender{ Gender::Male };

        std::transform(genderString.begin(), genderString.end(), genderString.begin(), ::tolower);
        if (genderString == "male") {
            gender = Gender::Male;
        }
        else if (genderString == "female") {
            gender = Gender::Female;
        }
        else if (genderString == "other") {
            gender = Gender::Other;
        }
        return gender;
    }

    inline double Employee::computeSalary(Salary& obj) {
        double totalSalary{ 0.0 };

        totalSalary += obj.getBaseSalary();
        totalSalary += obj.getAllowance();
        totalSalary -= obj.getDeduction();
        totalSalary += obj.getBonus();
        totalSalary += (obj.getBaseSalary() * (obj.getPerformanceMetric() / 100));

        return totalSalary;
    }
}

#endif