#include <string.h>
#include <stdio.h>
#include <cxx/iostream.hpp>
#include <iob.h>
#include <time.h>
#include <sleep.h>
#include <kernel/kernel.hpp>
#include <dev/SysTimer.hpp>
#include <gol.hpp>

#define SHELLCOMMAND(x)		int (x) (int argc, char **argv)

typedef struct
{
        char    Name[128];
        char    Description[512];
        SHELLCOMMAND((*Call));
} ShellCommand;



SHELLCOMMAND(ShellHelp); //                  (int argc, char **argv);
SHELLCOMMAND(ShellShutdown); //               (int argc, char **argv);
SHELLCOMMAND(ShellClear); //                  (int argc, char **argv);
SHELLCOMMAND(ShellUmount); //                 (int argc, char **argv);
SHELLCOMMAND(ShellNow); //					(int argc, char **argv);
SHELLCOMMAND(ShellDev); //					(int argc, char **argv);
SHELLCOMMAND(ShellRand); //					(int argc, char **argv);
SHELLCOMMAND(ShellSleep);

ShellCommand _commands[] =
{
       { "lsdev", "List current used devices", ShellDev },
       { "help", "This help", ShellHelp },
       { "clear", "clear the terminal screen", ShellClear },
       { "shutdown", "Shutdown or reboot the system", ShellShutdown },
       { "now", "Current date time", ShellNow },
       { "rand", "Random Number", ShellRand },
       { "sleep", "Test Raspberry Pi Timer Device", ShellSleep },
       { "gol", "Game Of Life Framebuffer Test", gameOfLife },
};
#define _COMMANDS_N             (sizeof(_commands) / sizeof(ShellCommand))

char string[128];
char path[1024];


void get()
{
	int p = 0;
    char ch;
    
    
    while((ch = getch()) != 13)
    {
        if((ch == '\b') && (p == 0))
                continue;

        std::cout <<(ch);
        if(ch == '\b')
        {
                p--;
        }
        else
        {
                string[p] = ch;
                p++;
        }
    }
	string[p] = 0;
   	std::cout << "\n";
}
void drawPreamble(int ret)
{
	if(ret != 0)
	{
		std::cout << std::textcolor::Red << ret << " " 
				  << std::textcolor::White << "kshell "
				  << std::textcolor::LightBlue 
			  	  << "/" << std::textcolor::LightGrey << " > " ;
		ret = 0;
	}
	else
	{
		std::cout << std::textcolor::White << "kshell "
				  << std::textcolor::LightBlue 
			  	  << "/" << std::textcolor::LightGrey << " > " ;
	}
}
int run()
{
	if(strcmp(string, "\0"))
  	{
        for(uint32_t i = 0; i < _COMMANDS_N; i++)
        {
            if(!strcmp(string, _commands[i].Name))
            {
            		
             	return _commands[i].Call(0, NULL);
            }
        }
    }
    iodelay(150);
    return 255;
}
extern "C" void kernel_shell()
{
    bool exit = false;
    strcpy(path, "/");
    drawPreamble(0);
    
    //shell_fsnode = fs_root;
    
    while(!exit)
    {
       	get();
        drawPreamble(run());
    }
}
SHELLCOMMAND(ShellSleep)
{
    std::cout << "\nWait Test";
    sleep(3);
    std::cout << " OK" << "\n";

    return 0;
}
int ShellEcho (int argc, char **argv)
{
	return 0;
}



int ShellUmount(int argc, char **argv)
{
        return 0;
}

int ShellClear(int argc, char **argv)
{
        cls();
        
	
        return 0;
}


int ShellHelp(int argc, char **argv)
{
        unsigned i;

        for(i = 0; i < _COMMANDS_N; i++)
        {
        	std::cout << std::tab << "-> "<< _commands[i].Name << " - " << _commands[i].Description << std::endl;
        }

        return 0;
}
int ShellRand(int argc, char **argv)
{
        //GetDeviceByName
        //void* RandDevice = GetDeviceByName("rand0");
       // if(RandDevice != NULL)
        //{
        	std::cout << rand() << "\n";
       // }
	return 0;
}
int ShellShutdown(int argc, char **argv)
{
        
        return 0;
}
const char *mon_name[] = 
{
	"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun",
	"Dec", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
int ShellNow(int argc, char **argv)
{
	tm* timeptr= localtime(NULL);
	
	std::cout << std::tab << mon_name[timeptr->tm_mon + 7];

	int day = timeptr->tm_mday;
	int hour = timeptr->tm_hour;
	int min = timeptr->tm_min;
	int sec = timeptr->tm_sec;
	
	std::cout << " " << (day < 10 ? "0" : "") << day ;
	std::cout << " " << (hour < 10 ? "0" : "") << hour;
	std::cout << ":" << (min < 10 ? "0" : "") << min;
	std::cout << ":" << (sec < 10 ? "0" : "") << sec;
	
	std::cout << " " << timeptr->tm_year << std::endl;
	
	return 0;
}
int ShellDev					(int argc, char **argv)
{
	dev::listDevices *drv = Kernel::Instance().GetDevices()->getList();
	
	for(dev::listDevices::iterator i = drv->begin() ; i != drv->end(); i++)
	{
		std::cout << "\t" << (*i)->getName() << " : " << (*i)->getDriver()->getName() << std::endl;
	}
	
	return 0;
}
