#include <kernel/kernel.hpp>
#include <cxx/stl.hpp>
#include <cxx/iostream.hpp>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <cmdParse.h>
#include <kernel/mm.h>

#include <softEvent/event.hpp>

void* kernel_instance;
uint32_t initial_esp;

extern "C" void kernel_shell();
extern "C" int __bss_start__;
extern "C" int __bss_end__;

Kernel::Kernel(uint64_t system_ram, uint64_t gpu_ram, KernelFrameBuffer *fb) 
{
	m_driverList = new dev::DriverList();
	m_vram = gpu_ram;
	m_sram = system_ram;
	m_pFB = fb;
	m_pFB->iDepth = FRMEBUFFER_DEPTH;
}





int Kernel::RunKernel(int args, char** argv)
{  
	m_devices = new dev::DeviceManager();
	m_devices->ProbeAll();

	std::cout.SetDevice("fb0");
  	std::cin.SetDevice("uart0");


  	std::cout << std::textcolor::LightGrey << "CS/Os5-ARM on Raspberry Pi\n" << "CPU-Freq: " << get_cpu_freq() << " Mhz\n";
  	std::cout << "RAM/VRAM: " << (uint32_t)(m_sram / 1024 / 1024) << "/" << (uint32_t)(m_vram / 1024 / 1024) << " MB\n";

  	kernel_shell();
	for(;;) ;
	return 0;
}

extern "C" int kernel_main(int r0, unsigned int r1, unsigned int r2 )
{
	int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;
    while( bss < bss_end )
        *bss++ = 0;
    
	uint32_t system_ram = get_system_mem();
	uint32_t gpu_ram = get_video_mem();

    mm_init(system_ram);

	kernel_instance = new Kernel(system_ram, gpu_ram, get_framebuffer_info());

    return ((Kernel*)kernel_instance)->RunKernel(0, NULL);
}

