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
#include <ClanLib/application.h>

#include <string>

#include "luafunctions.h"
#include "GameManager.h"
#include "TestScene.h"

#include "AIManager\aimanager.h"

class DisplayProgram
{
public:
	static int main(const std::vector<CL_String> &args)
	{

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

		GameManager* manager = GameManager::GetInstance();
		manager->LoadResource("../../../../data/resources.xml");

		TestScene newScene;
		manager->PushScene(&newScene);

		int ret = manager->Loop();

		delete manager;

#if _DEBUG
		console.display_close_message();
#endif

		return ret;
	}
};

// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
CL_ClanApplication app(&DisplayProgram::main);