#ifndef __SPLIT_H
#define __SPLIT_H

// functions to split a string by a specific delimiter
#include <cxx/string.hpp>
#include <cxx/vector.hpp>
#include <string.h>

namespace std
{
	std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<std::string>  split(const std::string &s, char delim);


	std::vector<std::string>& split(const std::string &s, const std::string& delims, std::vector<std::string> &elems);
	std::vector<std::string>  split(const std::string &s, const std::string& delims);


	template < class ContainerT >
	void tokenize(const std::string& str, ContainerT& tokens,
	              const std::string& delimiters = " ", const bool trimEmpty = false)
	{

	    std::string::size_type pos, lastPos = 0;
	    while(true)
	    {
		pos = str.find(delimiters.c_str());
		if(pos == std::string::npos)
		{

		    pos = str.length();

		    if(pos != lastPos || !trimEmpty) {
			tokens.push_back(typename ContainerT::value_type(str.c_str()+lastPos, (typename ContainerT::value_type::size_type)pos-lastPos));
		    }

		    break;
		}
		else
		{
		    if(pos != lastPos || !trimEmpty) {
			tokens.push_back(typename ContainerT::value_type(str.c_str()+lastPos, (typename ContainerT::value_type::size_type)pos-lastPos));
		    }
		}

		lastPos = pos + 1;
	    }
	};
}

#endif
