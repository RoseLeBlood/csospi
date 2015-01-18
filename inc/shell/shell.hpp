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
#define MAX_VAR 		32

namespace VarType
{
	enum VarType_t
	{
		User,
		System
	};
}

struct csShellVar
{
	std::string Name;
	std::string Variable;
	VarType::VarType_t	Type;

	inline csShellVar() { }
	inline csShellVar(std::string name, std::string var, VarType::VarType_t t)
	{
		Name = name;
		Variable = var;
		Type = t;
	}
};
class csShell
{
public:
	csShell();

	virtual void Run();
protected:
	virtual void Exit(); 

	virtual bool 				set(std::string name, std::string data, VarType::VarType_t type);
	virtual bool 				unset(std::string name);
	virtual std::string 		get(std::string name);
	virtual std::string 		getinput(bool pass);
	virtual void				drawPreamble();
	virtual bool 				findAndRunCommand(std::string command);
	virtual csShellLogin		login();
private:
	static int lsdev(csShell* shell, std::vector<std::string> args); 
	static int help(csShell* shell, std::vector<std::string> args); 
	static int exit(csShell* shell, std::vector<std::string> args);
	static int echo(csShell* shell, std::vector<std::string> args);
	static int set(csShell* shell, std::vector<std::string> args);
	static int lsvar(csShell* shell, std::vector<std::string> args);
	// TODO: 
	static int hash(csShell* shell, std::vector<std::string> args);
	static int unset(csShell* shell, std::vector<std::string> args);
	static int passwd(csShell* shell, std::vector<std::string> args);

private:
	std::list<csShellCommand> m_pCommands;
	std::list<csShellLogin>	  m_pUser;
	std::list<csShellVar>	  m_pVariable;
					
	uint32_t		m_lastReturn;
	bool			m_bRun;
	bool			m_bLogin;
};

#endif