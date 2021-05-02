/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   2:01
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter\main.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter
	file base:	main
	file ext:	cpp
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	Main entry for Adaptive Shooter
*********************************************************************/

// ClanLib engine includes
#include "ClanLib/core.h"
#include "ClanLib/display.h"
#include "ClanLib/application.h"

// Std Lib includes
#include <string>

// Project includes
#include "luafunctions.h"
#include "GameManager.h"
#include "FadingScene.h"
#include "Menu.h"
#include "MenuDifficulty.h"
#include "TestScene.h"
#include "TestScenePlayer.h"
#include "StaticEntity.h"

// AI Manager includes
#include "AIManager/AIManager.h"

class DisplayProgram
{
public:
	static int main(const std::vector<std::string> &args){

#if _DEBUG
		clan::ConsoleWindow console("Debug Console", 80, 160);
		clan::Console::write_line("Arguments: %1", args.size());

		std::cout << "Arguments: " + args.size();

		for( unsigned int i = 0; i < args.size(); i++ )
		{
			clan::Console::write( "[%1] = %2\n", i, args[i] );
		}

		clan::Console::write_line("");
#endif
		int ret = 0;

		try
		{
			GameManager* manager = GameManager::getInstance();

#ifdef _DEBUG
			manager->loadXMLResource("../../data/resources.xml");
#else
			manager->loadXMLResource("./data/resources.xml");
#endif

			manager->setupPlayer(0);
	
			//Splash screen
			FadingScene* splashScreen = new FadingScene( 2000.0f, 2000.0f, 4000.0f, FadingScene::FM_FADE_INOUT );
			StaticEntity* newEntity = new StaticEntity( 0.0f, 0.0f, "scenes/logo" ); // Fading scene deletes this
			splashScreen->insertEntity( newEntity );
	
			//Menu screen
			MenuDifficulty* difficultyMenu = new MenuDifficulty();
	
			//Test scene
			TestScenePlayer* newTest = new TestScenePlayer();

			//Ending scene
			FadingScene* ending = new FadingScene( 2000.0f, 2000.0f, 2000.0f, FadingScene::FM_FADE_INOUT );
			newEntity = new StaticEntity( 0.0f, 0.0f, "scenes/congratulations" ); // Fading scene deletes this
			newEntity->setAlpha( 0.0f );
			ending->insertEntity( newEntity );
			
			newTest->setNextScene( ending );
			difficultyMenu->setNextScene( newTest );
			splashScreen->setNextScene( difficultyMenu );
			manager->pushScene( splashScreen );
			manager->pushScene( difficultyMenu );
	
			/* Main game loop */
			ret = manager->loop();
	
			delete newTest;
			delete splashScreen;
			delete ending;
			delete manager;

		}
		catch(clan::Exception &exception)
		{
			// Create a console window for text-output if not available
			clan::ConsoleWindow console("Console", 80, 160);
			clan::Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
			console.display_close_message();

			return -1;
		}

#ifdef _DEBUG
		console.display_close_message();
#endif
		return ret;
	}
};

// Create global application object, you MUST include this line or the application start-up will fail to locate your application object.
clan::Application app(&DisplayProgram::main);
