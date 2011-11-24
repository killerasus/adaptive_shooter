/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   2:01
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\main.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	main
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Main entry for Adaptive Shooter
*********************************************************************/

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include <string>
#include "luafunctions.h"	
#include "AIManager\aimanager.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class DisplayProgram
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;
		AIManager* manager;
		char* text;

		lua_State *L = lua_open();
		luaL_openlibs(L);
		RegisterLuaCLConsolePrint(L);

#if _DEBUG
		CL_ConsoleWindow console("Debug Console", 80, 160);
		CL_Console::write_line("Arguments: %1", args.size());

		std::cout << "Arguments: " + args.size();

		for( unsigned int i = 0; i < args.size(); i++ )
		{
			CL_Console::write( "[%1] = %2\t", i, args[i] );
		}

		CL_Console::write_line("");
#endif

		try
		{
			CL_DisplayWindow window("Hello World", 640, 480);

			CL_GraphicContext gc = window.get_gc();
			CL_InputDevice keyboard = window.get_ic().get_keyboard();
			CL_Font font(gc, "Tahoma", 30);

#if _DEBUG
			if (args.size() > 1)
			{
				if (luaL_dofile(L, args[1].c_str()) == 0)
				{
					lua_getglobal(L,"text");
					text = (char*)lua_tostring(L,-1);
				}
			}
			else
			{
				text = "Hello World without Lua script";
			}
#endif

			while (!keyboard.get_keycode(CL_KEY_ESCAPE))
			{
				gc.clear(CL_Colorf::cadetblue);

				CL_Draw::line(gc, 0, 110, 640, 110, CL_Colorf::yellow);
#if _DEBUG
				font.draw_text(gc, 100, 100, text, CL_Colorf::lightseagreen);
#else
				font.draw_text(gc, 100, 100, "Hello World!", CL_Colorf::lightseagreen);
#endif

				// Make the stuff visible:
				window.flip();

				// Read messages from the windowing system message queue, if any are available:
				CL_KeepAlive::process();

				// Avoid using 100% CPU in the loop:
				CL_System::sleep(10);
			}
		}
		catch(CL_Exception &exception)
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
			console.display_close_message();

			return -1;
		}

		lua_close(L);

#if _DEBUG
		console.display_close_message();
#endif

		return 0;
	}
};

// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
CL_ClanApplication app(&DisplayProgram::main);