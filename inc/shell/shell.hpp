#ifndef __FRAMEBUFFER_SHELL_H__
#define __FRAMEBUFFER_SHELL_H__

#include <types.h>
#include <cxx/string.hpp>
#include <cxx/list.hpp>
#include <cxx/vector.hpp>

// csos_pi ... user: pi
#define STD_USER_PASS std::string("6ee22a1e4208d2e3922000571025bb14")

#define COSHELL_COMMANDNOTFOUND 255
#define COSHELL_LOGOUT          254

class csShell;

typedef int (* shell_command)(csShell* shell, std::vector<std::string> args);

struct csShellCommand
{
	std::string Name;
	std::string Description;
	shell_command Function;

	inline csShellCommand() { }
	inline csShellCommand(std::string name, std::string desc, shell_command func)
	{
		Name = name;
		Description = desc;
		Function = func;
	}
};

struct csShellLogin
{
	std::string Name;
	std::string Password; // md5

	inline csShellLogin() { }
	inline csShellLogin(std::string name, std::string hash)
	{
		Name = name;
		Password = hash;
	}
};

class csShell
{
public:
	csShell();

	virtual void Run();
	virtual void Exit(); 
protected:
	virtual std::string getinput(bool pass);
	virtual void		drawPreamble();
	virtual bool 		findAndRunCommand(std::string command);
	virtual csShellLogin		login();
private:
	static int lsdev(csShell* shell, std::vector<std::string> args); 
	static int help(csShell* shell, std::vector<std::string> args); 
	static int exit(csShell* shell, std::vector<std::string> args);
	static int echo(csShell* shell, std::vector<std::string> args);
private:
	std::list<csShellCommand> m_pCommands;
	std::list<csShellLogin>	  m_pUser;

	uint32_t		m_lastReturn;
	bool			m_bRun;
	bool			m_bLogin;
};

#endif