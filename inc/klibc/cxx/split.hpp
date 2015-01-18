#ifndef __SPLIT_H
#define __SPLIT_H

// functions to split a string by a specific delimiter
#include <cxx/string.hpp>
#include <cxx/vector.hpp>
#include <string.h>

namespace std
{
	std::vector<std::string> split(std::string&  strString, const char*  delimiter);
	std::vector<std::wstring> split(std::wstring& strString, const wchar_t* delemiter);

	template<typename T, class StringT>
	void tokenize(T* s, T delim, std::vector<StringT>& container)
	{
		const T *olds = s;
		T olddelim = delim;

		while(olddelim && *s) 
		{
			while(*s && (delim != *s)) s++;
			*s ^= olddelim = *s; 
			container.push_back(StringT(olds));
			*s++ ^= olddelim; 
			olds = s;
		}
	}
}

#endif
