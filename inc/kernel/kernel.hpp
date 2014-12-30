#ifndef _CSOS_KERNEL_H_PP_
#define _CSOS_KERNEL_H_PP_

#include <sys/utsname.h>
#include <assert.h>

#include <cxx/string.hpp>
#include <cxx/list.hpp>

#include <dev/DriverList.hpp>
#include <dev/DeviceList.hpp>
#include <cxx/stl.hpp>

extern "C" void* kernel_instance;

class Kernel
{
public:
	Kernel();

	int RunKernel(int args, char** argv);
	
	dev::DriverList* GetDrivers()			
	{ 
		return m_driverList; 
	}
	dev::Driver*	 GetDriver(char* name) 
	{ 
		return GetDevice(name)->getDriver(); 
	}
	
	dev::DeviceManager* GetDevices()
	{ 
		return m_devices; 
	}
	dev::Device*		GetDevice(char* name) 
	{ 
		return m_devices->getDevice(name)->getDevice(); 
	}
	
	static Kernel& Instance() { return *((Kernel*)(kernel_instance)); }
private:
	void plotinfo(const char* text, uint32_t s, uint32_t e);
private:
	dev::DriverList*					m_driverList;
	dev::DeviceManager*			    	m_devices;
};

extern "C" void* GetDeviceByName(char* name);
extern "C" int	 GetDeviceByNameEx(char* name, void** device);


#endif