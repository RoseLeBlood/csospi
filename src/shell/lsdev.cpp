#include <shell/shell.hpp>
#include <cxx/iostream.hpp>
#include <kernel/kernel.hpp>

int csShell::lsdev(csShell* shell, std::vector<std::string> args)
{
	dev::listDevices *drv = Kernel::Instance().GetDevices()->getList();
	
	for(dev::listDevices::iterator i = drv->begin() ; i != drv->end(); i++)
	{
		std::cout << "\t" << (*i)->getName() << " : " << (*i)->getDriver()->getName() << std::endl;
	}

	return 0;
}