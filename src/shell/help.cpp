#include <shell/shell.hpp>
#include <cxx/iostream.hpp>

int csShell::help(csShell* shell, std::vector<std::string> args)
{
	for (std::list<csShellCommand>::iterator it = shell->m_pCommands.begin(); it != shell->m_pCommands.end(); it++)
	{
		std::cout << std::tab << "-> "<< it->Name << " - " << it->Description << std::endl;
	}
	return 0;
}