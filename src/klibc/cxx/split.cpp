#include <cxx/split.hpp>

namespace std
{
	std::vector<std::string> split(std::string&  strString, const char*  delimiter)
	{
		std::vector<std::string> container;
		tokenize<char, std::string>
			((char*)strString.c_str(), delimiter[0], container);
		return container;
	}
	std::vector<std::wstring> split(std::wstring& strString, const wchar_t* delimiter)
	{
		std::vector<std::wstring> container;
		tokenize<wchar_t, std::wstring>
			((wchar_t*)strString.c_str(), delimiter[0], container);
		return container;
	}
}