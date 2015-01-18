#include <shell/shell.hpp>
#include <cxx/iostream.hpp>
#include <cxx/split.hpp>

int csShell::set(csShell* shell, std::vector<std::string> args)
{
	//set VAR DAT
	if(args.size() == 3)
	{
		if(args[2][0] != '$')
			shell->set(args[1], args[2], VarType::User);
		else
			shell->set(args[1], shell->get(args[2]), VarType::User);
		return 0;

	}
	std::cout << "Using set {VARNAME} {DATA}" << std::endl;
	return -1;
}
int csShell::unset(csShell* shell, std::vector<std::string> args)
{
	// unset VAR
	if(args.size() == 2)
	{
		return shell->unset(args[1]) ? 0 : 1;

	}
	std::cout << "Using unset {VARNAME}" << std::endl;
	return -1;
}
int csShell::lsvar(csShell* shell, std::vector<std::string> args)
{
	for (std::list<csShellVar>::iterator it = shell->m_pVariable.begin(); it != shell->m_pVariable.end(); it++)
	{
		std::cout << it->Name << ": " << it->Variable << " (" << 
			(it->Type == VarType::User ? "U" : "S") << ")" << std::endl;
	}

	return 0;
}