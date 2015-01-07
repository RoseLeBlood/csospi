#ifndef __CSOS_EVENT_HPP__
#define __CSOS_EVENT_HPP__

#include <dev/Driver.hpp>
#include <stdio.h>
#include <cxx/stl.hpp>

class Event
{
public:
	Event() { }
	Event( char* device, unsigned int ticks);

	virtual void CallBack(dev::Driver* sender);
private:
	void int_CallBack(dev::Driver* sender);
private:
	static void driverCallback(dev::Driver* sender, void* userdata);
private:
	unsigned int m_iTicks;
	unsigned long m_iPref;
};


#endif