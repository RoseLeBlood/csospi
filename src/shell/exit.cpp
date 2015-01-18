#include <shell/shell.hpp>
#include <cxx/iostream.hpp>

int csShell::exit(csShell* shell, std::vector<std::string> args)
{
	shell->Exit();

	return COSHELL_LOGOUT;
}
