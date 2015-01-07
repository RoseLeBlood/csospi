#include <softEvent/event.hpp>
#include <kernel/kernel.hpp>

extern "C" void* kernel_instance;

Event::Event(char* device, unsigned int ticks)
{
	m_iTicks = ticks;
	m_iPref = 0;
	dev::Driver *dev = ((Kernel*)kernel_instance)->GetDriver(device);
	if(dev != NULL)
		dev->SetCallback(driverCallback, this);
}
void Event::int_CallBack(dev::Driver* sender) 
{
	m_iPref++;
	if((m_iPref ==  m_iTicks))
	{
		m_iPref = 0;
		CallBack(sender);
	}
}
void Event::driverCallback(dev::Driver* sender, void* userdata)
{
	Event* other = (Event*)userdata;
	if(other != NULL)
		other->int_CallBack(sender);
}
void Event::CallBack(dev::Driver* sender) 
{ 
	printf("Hallo Welt\n");
}