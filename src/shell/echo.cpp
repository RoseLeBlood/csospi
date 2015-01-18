#include <shell/shell.hpp>
#include <cxx/iostream.hpp>

int csShell::echo(csShell* shell, std::vector<std::string> args)
{
	for(int i = 1; i < args.size(); i++)
	{
		if(args[i][0] == '$')
		{
			std::cout << shell->get( args[i] ) << ' ';
		}
		else
			std::cout << args[i] << ' ';
	} 

	std::cout << std::endl;
	return 0;
}