#include <dev/DriverList.hpp>
#include <stddef.h>
#include <cxx/iostream.hpp>
#include <dev/serial_out.hpp>
#include <dev/Random.hpp>
#include <kernel/kernel.hpp>
#include <dev/SysTimer.hpp>
#include <dev/Framebuffer.hpp>

extern "C" void AddDriver(dev::Driver* dev)
{
	Kernel::Instance().GetDrivers()->Add(dev);
}
namespace dev
{
	DriverList::DriverList()
	{
		m_driver = listDriver();

		Add(new SerialOut(0x3f8));
		Add(new std_random());
		Add(new SysTimer());
		Add(new Framebuffer());
	}
	DriverList::~DriverList()
	{

	}

	bool DriverList::Add(Driver *driver)
	{    
        m_driver.push_back(driver);   
        return Get(driver->getName()) != NULL;
	}
	
	Driver *DriverList::Get(const char *devname)
	{
		Driver *dr = NULL;
		
		for(listDriver::iterator i = m_driver.begin(); i != m_driver.end(); i++)
    	{
    		if( !strcmp((*i)->getDevName(), devname))
    		{
    			dr = *i;
    			break;
    		}
    	}		
    	return dr;
	}
	void DriverList::Rem(const char *name)
	{
		listDriver::iterator it = m_driver.begin();
		while (it != m_driver.end())
		{
			if( !strcmp((*it)->getDevName(), name))
			{
				it = m_driver.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}