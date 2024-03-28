#ifndef _Validator_h_
#define _Validator_h

#include <regex>
#include <string>

namespace EmployeeDB {

	class Validator {
	public:
		static bool validateName(const std::string& in) noexcept;
		static bool validateNum(const std::string& in) noexcept;
		static bool validateReal(const std::string& in) noexcept;
		static bool validateEmail(const std::string& email) noexcept;
		static bool validateMobile(const std::string& number) noexcept;
		static bool validateDate(const std::string& date) noexcept;
		static bool validateGender(const std::string& gender) noexcept;
		static bool validateCharInput(char& in) noexcept;
		static bool validateInputMenu(char& in) noexcept;
		static bool validateInputMainMenu(char& in) noexcept;
		static bool validateInputView(char& in) noexcept;
		static bool validateViewOfFields(std::string& in) noexcept;
		static bool validateUpdate(std::string& in) noexcept;
		static bool validateDeptUpdate(std::string& in) noexcept;
		static bool validateViewOfDeptFields(std::string& in) noexcept;
		static bool validateManUpdate(std::string& in) noexcept;
		static bool validateViewOfManFields(std::string& in) noexcept;

		static bool validatecsvInput(char& in) noexcept;
	};
}

#endif // !_Validator_h_
