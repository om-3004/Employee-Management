#ifndef _Validator_h_
#define _Validator_h

#include <regex>
#include <string>

namespace EmployeeDB {

	class Validator {
	public:
		static bool validateEmail(const std::string& email);
		static bool validateMobile(const std::string& number);
		static bool validateDate(const std::string& date);
		static int validateGender(const std::string& gender);
		static bool validateCharInput(char& in);
		static bool validateInputMenu(char& in);
		static bool validateInputMainMenu(char& in);
		static bool validateInputView(char& in);
		static bool validateViewOfFields(std::string& in);
		static bool validateUpdate(std::string& in);
		static bool validateDeptUpdate(std::string& in);
		static bool validateViewOfDeptFields(std::string& in);
		static bool validateManUpdate(std::string& in);
		static bool validateViewOfManFields(std::string& in);
	};
}

#endif // !_Validator_h_
