#include <kernel/kernel.hpp>
#include <cxx/stl.hpp>
#include <cxx/iostream.hpp>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <cmdParse.h>
#include <kernel/mm.h>
#include <kernel/utils.h>

void* kernel_instance;
uint32_t initial_esp;

extern "C" void kernel_shell();
extern "C" int __bss_start__;
extern "C" int __bss_end__;
extern "C" void _enable_interrupts();

Kernel::Kernel() 
{
	m_driverList = new dev::DriverList();
	
}

int Kernel::RunKernel(int args, char** argv)
{  
	m_devices = new dev::DeviceManager();
	m_devices->ProbeAll();

  	std::cout.SetDevice("fb0");
  	std::cin.SetDevice("uart0");

  	 _enable_interrupts();
  	std::cout << "CS/Os5-ARM on Raspberry Pi\n" << "CPU-Freq: " << get_cpu_freq() << " Mhz\n";
  	std::cout << "RAM/VRAM: " << get_system_mem() << "/" << get_video_mem() << " MB\n";

  	FrameBuffer* fb = get_framebuffer_info();
  	set_framebuffer(fb);

  	std::cout << "Framebuffer: " << fb->ifbX << "x" << fb->ifbY << "-" << fb->iDepth << "\n";
  	std::cout << "\tBase: " << fb->iBaseAdress << " Size: " << fb->iSize << "\n";

  	kernel_shell();
	
	return 0;
}

extern "C" int kernel_main(int r0, unsigned int r1, unsigned int r2 )
{
	int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;
    while( bss < bss_end )
        *bss++ = 0;


   

    uint32_t mem = 128*1024*1024; // 128 MB
    mm_init(mem);
	kernel_instance = new Kernel();

    return ((Kernel*)kernel_instance)->RunKernel(0, NULL);
}

