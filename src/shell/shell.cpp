#include <shell/shell.hpp>
#include <cxx/iostream.hpp>
#include <kernel/kernel.hpp>
#include <hash/md5.h>
#include <stdio.h>

std::vector<std::string> split(std::string&  strString,const char*  delimiter);

csShell::csShell() 
{
	m_pCommands = std::list<csShellCommand>();
	m_pUser = std::list<csShellLogin>();
	m_bLogin = false;
	m_lastReturn = 0;

	m_pCommands.push_back(csShellCommand(std::string("help"), std::string("This text"), csShell::help));
	m_pCommands.push_back(csShellCommand(std::string("lsdev"), std::string("List current used devices"), csShell::lsdev));
	m_pCommands.push_back(csShellCommand(std::string("exit"), std::string("logout"), csShell::exit));
	m_pCommands.push_back(csShellCommand(std::string("echo"), std::string("echo"), csShell::echo));

	m_pUser.push_back(csShellLogin(std::string("pi"), STD_USER_PASS));
}
char string[128];

std::string csShell::getinput(bool pass)
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

   	return std::string(string);// + std::string(string));
}
void csShell::drawPreamble()
{
   	if(m_lastReturn != 0)
	{
		std::cout << std::textcolor::Red << m_lastReturn;
	}
	std::cout << std::textcolor::Yellow  << "cosh" << std::textcolor::LightGrey << "@" << NETWORKNAME  
	 			<< std::textcolor::White << " /" << std::textcolor::LightGrey << " % " ;
}
bool csShell::findAndRunCommand(std::string command)
{
	m_lastReturn = COSHELL_COMMANDNOTFOUND;
	 			
	std::vector<std::string> input =  split(command, " ");

	for (std::list<csShellCommand>::iterator it = m_pCommands.begin(); it != m_pCommands.end(); it++)
	{
		if(it->Name == input[0])
		{
			m_lastReturn = it->Function(this, input);
			break;
		}
	}
	return m_lastReturn != COSHELL_LOGOUT; 
}
void csShell::Exit()
{
	m_bLogin = false;
	cls();
}
void csShell::Run()
{
	m_bRun = true;
	m_lastReturn = 0;
	std::string input;

	while(m_bRun)
	{
		if(m_bLogin)
		{
			input = getinput(false);
			if(!input.empty()) 
			{
				if(findAndRunCommand(input) == false)
					continue;
			}
		}
		else
		{
			login();
			m_lastReturn = 0;
		}
	    drawPreamble();
	}
}
csShellLogin csShell::login()
{
	std::string username, pass;
	char buf[260];

	while(true)
	{
		std::cout << "User: " ;
		username = getinput(false);
		std::cout << "Password: ";
		pass = getinput(true);

		for (std::list<csShellLogin>::iterator it = m_pUser.begin(); it != m_pUser.end(); it++)
		{
			if(it->Name == std::string(username))
			{
				
				md5(pass.c_str(), buf);
				if(it->Password == std::string(buf))
				{
					m_bLogin = true;
					return *it;
				}
				else
				{
					std::cout << std::textcolor::Red << "Login incorrect" << std::endl; 
				}
			}
		}
	}
}
//............................................
int csShell::lsdev(csShell* shell, std::vector<std::string> args)
{
	dev::listDevices *drv = Kernel::Instance().GetDevices()->getList();
	
	for(dev::listDevices::iterator i = drv->begin() ; i != drv->end(); i++)
	{
		std::cout << "\t" << (*i)->getName() << " : " << (*i)->getDriver()->getName() << std::endl;
	}

	return 0;
}
int csShell::help(csShell* shell, std::vector<std::string> args)
{
	for (std::list<csShellCommand>::iterator it = shell->m_pCommands.begin(); it != shell->m_pCommands.end(); it++)
	{
		std::cout << std::tab << "-> "<< it->Name << " - " << it->Description << std::endl;
	}
	return 0;
}
int csShell::exit(csShell* shell, std::vector<std::string> args)
{
	shell->Exit();

	return COSHELL_LOGOUT;
}
int csShell::echo(csShell* shell, std::vector<std::string> args)
{
	for(int i = 1; i < args.size(); i++)
		std::cout << args[i] << ' '; 

	std::cout << std::endl;
	return 0;
}

#include <string.h>



void tokenize(char *s, char delim,  std::vector<std::string> &container) {
	char *olds = s;
	char olddelim = delim;
	while(olddelim && *s) 
	{
		while(*s && (delim != *s)) s++;
		*s ^= olddelim = *s; 
		container.push_back(std::string(olds));
		*s++ ^= olddelim; 
		olds = s;
	}
}

std::vector<std::string> split(std::string&  strString,const char*  delimiter)
{
 	std::vector<std::string> container;
	tokenize((char*)(strString.c_str()), delimiter[0], container);
	return container;
}