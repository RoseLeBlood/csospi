#include <shell/shell.hpp>
#include <cxx/iostream.hpp>
#include <kernel/kernel.hpp>
#include <hash/md5.h>
#include <stdio.h>
#include <cxx/split.hpp>

csShell::csShell() 
{
	m_pCommands = std::list<csShellCommand>();
	m_pUser = std::list<csShellLogin>();
	m_bLogin = false;
	m_lastReturn = 0;

	m_pCommands.push_back(csShellCommand(std::string("help"), std::string("This text"), csShell::help));
	m_pCommands.push_back(csShellCommand(std::string("lsdev"), std::string("List current used devices"), csShell::lsdev));
	m_pCommands.push_back(csShellCommand(std::string("exit"), std::string("logout"), csShell::exit));
	m_pCommands.push_back(csShellCommand(std::string("echo"), std::string("display a line of text"), csShell::echo));
	m_pCommands.push_back(csShellCommand(std::string("set"), std::string("using: set {VARNAME} {DATA}"), csShell::set));
	m_pCommands.push_back(csShellCommand(std::string("unset"), std::string("using: unset {VARNAME}"), csShell::unset));
	//lsvar
	m_pCommands.push_back(csShellCommand(std::string("lsvar"), std::string("list all variables"), csShell::lsvar));
	
	m_pUser.push_back(csShellLogin(std::string("pi"), STD_USER_PASS));

	set(std::string("SHELL"), std::string("csos"), VarType::System);
	set(std::string("PLATFORM"), std::string(PLATFORM), VarType::System);
	set(std::string("MASCHIN"), std::string(MACHINE), VarType::System);
	set(std::string("VERSION"), std::string(VERSION), VarType::System);
}
std::string csShell::getinput(bool pass)
{
	static char string[64];
	int p = 0;
    char ch;
    
    
    while((ch = getch()) != 13)
    {
        if((ch == '\b') && (p == 0))
                continue;

        if(!pass) std::cout <<(ch);
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
	std::cout << std::textcolor::Yellow  << (get(std::string("$USER"))) << std::textcolor::LightGrey << "@" << NETWORKNAME  
	 			<< std::textcolor::White << " /" << std::textcolor::LightGrey << " % " ;
}
bool csShell::findAndRunCommand(std::string command)
{
	m_lastReturn = COSHELL_COMMANDNOTFOUND;
	 			
	std::vector<std::string> input =  std::split(command, " ");

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
					set(std::string("USER"), it->Name, VarType::System);
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
bool csShell::set(std::string name, std::string data, VarType::VarType_t type)
{
	std::string var = std::string("$");
	var << name;

	for (std::list<csShellVar>::iterator it = m_pVariable.begin(); it != m_pVariable.end(); it++)
	{
		if(it->Name == var && it->Type != VarType::System )
		{
			it->Variable = data;
			return true;
		}
	}
    
	m_pVariable.push_back(csShellVar(var, data, type));
}
std::string csShell::get(std::string name)
{
	for (std::list<csShellVar>::iterator it = m_pVariable.begin(); it != m_pVariable.end(); it++)
	{
		if(it->Name == name )
			return it->Variable;
	}
	return std::string("");
}
bool csShell::unset(std::string name)
{
	for (std::list<csShellVar>::iterator it = m_pVariable.begin(); it != m_pVariable.end(); it++)
	{
		if(it->Name == name && it->Type != VarType::System)
		{
			m_pVariable.erase(it);
			return true;
		}
	}
	return false;
}
//............................................



