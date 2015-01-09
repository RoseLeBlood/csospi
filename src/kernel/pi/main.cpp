#include <kernel/kernel.hpp>
#include <cxx/stl.hpp>
#include <cxx/iostream.hpp>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <cmdParse.h>
#include <kernel/mm.h>
#include <kernel/power.h>

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

	std::cout.SetDevice("uart0");
  	std::cin.SetDevice("uart0");


  	std::cout << std::textcolor::LightGrey << "CS/Os5-ARM on Raspberry Pi\n" << "CPU-Freq: " << get_cpu_freq() << " Mhz\n";
  	std::cout << "RAM/VRAM: " << (uint32_t)(m_sram / 1024 / 1024) << "/" << (uint32_t)(m_vram / 1024 / 1024) << " MB\n";

  	kernel_shell();
	for(;;) ;
	return 0;
}
extern "C" void platforminit(void);

extern "C" int kernel_main(int r0, unsigned int r1, unsigned int r2 )
{
	int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;
    while( bss < bss_end )
        *bss++ = 0;
    
	power_init();
	platforminit();

	uint32_t system_ram = get_system_mem();
	uint32_t gpu_ram = get_video_mem();

    mm_init(system_ram);

	kernel_instance = new Kernel(system_ram, gpu_ram, get_framebuffer_info());

    return ((Kernel*)kernel_instance)->RunKernel(0, NULL);
}





extern "C" void __attribute__((interrupt("ABORT"))) reset_vector(void)
{

}

/**
    @brief The undefined instruction interrupt handler
    If an undefined intstruction is encountered, the CPU will start
    executing this function. Just trap here as a debug solution.
*/
extern "C" void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    while( 1 )
    {
        /* Do Nothing! */
    }
}


/**
    @brief The supervisor call interrupt handler
    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
extern "C" void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
    while( 1 )
    {
        /* Do Nothing! */
    }
}


/**
    @brief The prefetch abort interrupt handler
    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
extern "C" void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{

}


/**
    @brief The Data Abort interrupt handler
    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
extern "C" void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{

}


/**
    @brief The IRQ Interrupt handler
    This handler is run every time an interrupt source is triggered. It's
    up to the handler to determine the source of the interrupt and most
    importantly clear the interrupt flag so that the interrupt won't
    immediately put us back into the start of the handler again.
*/
extern "C" void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
   
}


/**
    @brief The FIQ Interrupt Handler
    The FIQ handler can only be allocated to one interrupt source. The FIQ has
    a full CPU shadow register set. Upon entry to this function the CPU
    switches to the shadow register set so that there is no need to save
    registers before using them in the interrupt.
    In C you can't see the difference between the IRQ and the FIQ interrupt
    handlers except for the FIQ knowing it's source of interrupt as there can
    only be one source, but the prologue and epilogue code is quite different.
    It's much faster on the FIQ interrupt handler.
    The prologue is the code that the compiler inserts at the start of the
    function, if you like, think of the opening curly brace of the function as
    being the prologue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers, there's
    nothing we need to save.
    The epilogue is the code that the compiler inserts at the end of the
    function, if you like, think of the closing curly brace of the function as
    being the epilogue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers and so has
    not altered the main set of registers.
*/
extern "C" void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{

}