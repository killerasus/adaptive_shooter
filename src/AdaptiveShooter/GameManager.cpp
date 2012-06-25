/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   9:15
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\GameManager.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	GameManager
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	GameManager implementation
*********************************************************************/

#include "GameManager.h"
#include "luafunctions.h"
#include "PlayerModelImpl.h"

GameManager* GameManager::_instance = 0;

GameManager::GameManager(): setup_core(), setup_display(), setup_gl(), _quit(false), _player(0)
{
	L = lua_open();
	luaL_openlibs(L);
	RegisterLuaCLHelper(L);

	_window = new CL_DisplayWindow("Hello World", 640, 480);

	_aiManager = new AIManager(L);
	// Player can only be created when there is already a GameManager instantiated
}



GameManager::~GameManager()
{
	cleanUp();
}



void GameManager::loadResource( std::string resourceFile )
{
	_resourceManager = new CL_ResourceManager(resourceFile);
}



int GameManager::loop()
{
	try
	{
		_last_time = CL_System::get_time();

		while (!_quit)
		{
#if _DEBUG
			if(_window->get_ic().get_keyboard().get_keycode(CL_KEY_ESCAPE) == true)
			{
				_quit = true;
				break;
			}
#endif

			update();
			draw();

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
		
		cleanUp();

		return -1;
	}

	return 0;
}



void GameManager::pushScene(Scene* scene)
{
	_sceneStack.push(scene);
}



Scene* GameManager::popScene()
{
	Scene* top = NULL;

	if (!_sceneStack.empty())
	{
		top = _sceneStack.top();
		_sceneStack.pop();
	}

	return top;
}



void GameManager::draw()
{
	_window->get_gc().clear(CL_Colorf::black);

	if (!_sceneStack.empty())
	{
		_sceneStack.top()->draw();
	}

	// Make the stuff visible:
	_window->flip();
}



void GameManager::update()
{
	_current_time = CL_System::get_time();
	unsigned int time_difference = _current_time - _last_time;
	if (time_difference > 1000)
		time_difference = 1000;		// Limit the time difference, if the application was paused (eg, moving the window on WIN32)
	_time_delta_ms = static_cast<float> (time_difference);
	_last_time = _current_time;

	//Update
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->update();
	} 
	else
	{
		_quit = true;
	}
}



GameManager* GameManager::getInstance()
{
	if(_instance == 0)
	{
		_instance = new GameManager();
	}

	return _instance;
}



CL_DisplayWindow* GameManager::getWindow()
{
	return _window;
}



CL_ResourceManager* GameManager::getResourceManager()
{
	return _resourceManager;
}



float GameManager::getDeltaTime()
{
	return _time_delta_ms;
}



lua_State* GameManager::getLuaState()
{
	return L;
}



void GameManager::getLuaState( lua_State* l )
{
	if (L != NULL)
	{
		lua_close(L);
	}

	L = l;
}



void GameManager::cleanUp()
{
	delete _aiManager;

	lua_close(L);

	L = NULL;

	/** @TODO: Check if there is memory leak */
	/*while(!_sceneStack.empty())
	{
		_sceneStack.pop();
	}*/

	delete _window;
	_window = NULL;
}



/** @TODO: Rewrite when more players are supported*/
Player* GameManager::getPlayer( unsigned int n )
{
	return _player;
}



void GameManager::setupPlayer( unsigned int n )
{
	_player = new Player("sprites/boat", new PlayerModelImpl(0.3f), 0.0f, 0.0f, 50.0f, 50.0f, n, 3);
}



AIManager* GameManager::getAIManager()
{
	return _aiManager;
}
