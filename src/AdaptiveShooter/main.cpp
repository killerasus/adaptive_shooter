#include <ClanLib/core.h>
#include <ClanLib/application.h>

class ConsoleProgram
{
public:
	static int main(const std::vector<CL_String> &args);
};

// Create global application object:
// You MUST include this line or the application start-up will fail to
// locate your console application object.
CL_ClanApplication app(&ConsoleProgram::main);

int ConsoleProgram::main(const std::vector<CL_String> &args)
{
	// Setup clanCore:
	CL_SetupCore setup_core;

	// Create a console Window if one does not exist:
	CL_ConsoleWindow console_window("Console");

	// Write a line to the console:
	CL_Console::write_line("Hello World!");

	// Wait for a key so the window won't close immediately.
	CL_Console::wait_for_key();

	return 0;
}