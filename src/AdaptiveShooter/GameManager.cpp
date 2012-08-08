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
#include "StaticEntity.h"

GameManager* GameManager::_instance = 0;

GameManager::GameManager(): setup_core(), setup_display(), setup_gl(), setup_sound(), setup_mikmod(), setup_vorbis(),
	sound_output(44100), _resourceManager( 0 ), _quit( false ), _player( 0 )
{
	L = lua_open();
	luaL_openlibs(L);
	RegisterLuaCLHelper(L);

	// Creates window
	_window = new CL_DisplayWindow("Adaptive Shooter - Bruno Baere", 640, 480);

	_aiManager = new AIManager(L);
	//_loggerFile = new logog::LogFile("test.txt");
	_loggerFile = new CL_FileLogger("log.txt");
	_loggerFile->enable();
	// Player can only be created when there is already a GameManager instantiated

	// Loads sounds and prepare
	loadSoundEffects();
	loadMusics();
}



GameManager::~GameManager()
{
	cleanUp();
}



void GameManager::loadResource( std::string resourceFile )
{
	if (_resourceManager)
	{
		delete _resourceManager;
	}

	_resourceManager = new CL_ResourceManager(resourceFile);
}



int GameManager::loop()
{
	try
	{
		_last_time = CL_System::get_time();

		while (!_quit)
		{
			if(_window->get_ic().get_keyboard().get_keycode(CL_KEY_ESCAPE) == true)
			{
				_quit = true;
				break;
			}

			update();

			if (_quit)
			{
				return 0;
			}

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



Scene* GameManager::peekScene()
{
	Scene* top = NULL;

	if (!_sceneStack.empty())
	{
		top = _sceneStack.top();
	}

	return top;
}



void GameManager::draw()
{
	_window->get_gc().clear(CL_Colorf::black);

	if (!_sceneStack.empty() && _sceneStack.top() != NULL)
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
	if (!_sceneStack.empty() && _sceneStack.top() != NULL)
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
	_aiManager = NULL;

	lua_close(L);
	L = NULL;

	delete _gameOverScene;
	_gameOverScene = NULL;
	delete _resourceManager;
	_resourceManager = NULL;

	/** @TODO: Check if there is memory leak */
	/*while(!_sceneStack.empty())
	{
		_sceneStack.pop();
	}*/

	// Closes log operation
	delete _loggerFile;
	_loggerFile = NULL;

	delete _window;
	_window = NULL;
}



/** TODO: Rewrite when more players are supported*/
Player* GameManager::getPlayer( unsigned int n )
{
	return _player;
}



void GameManager::setupPlayer( unsigned int n )
{
	float startSpeedX = 100.0f;
	float startSpeedY = 100.0f;
	std::string resource = "sprites/rwing";
	unsigned int lives = 3;
	float learningRate = 0.3f;

	int loadResult = luaL_dofile( L, "../../../../src/Scripts/config.lua" );

	if (!loadResult)
	{
		lua_getglobal( L, "Player" );

		if (lua_istable( L, -1 ))
		{
			lua_getfield( L, -1, "SpeedX");
			startSpeedX = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "SpeedY");
			startSpeedY = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "LearningRate");
			learningRate = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "Resource");
			resource = lua_tostring( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "Lives");
			lives = (unsigned int) lua_tointeger( L, -1 );
			lua_pop( L, 1 );
		}
		else
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console( "Console", 80, 160 );
			CL_Console::write_line( "Could not load Player from config.lua" );
		}

		// Pops Player table
		lua_pop( L, 1 );
	}
	else
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console( "Console", 80, 160 );
		CL_Console::write_line( "Could not load config.lua" );
	}
	

	CL_Rect windowViewPort = _window->get_viewport();
	_player = new Player( 0.0f, 0.0f, startSpeedX, startSpeedY, n, resource, new PlayerModelImpl( learningRate ), lives );
	//_player->setupCollisionOutlines();
	_player->setPositionX( float((windowViewPort.get_width() >> 1) - (_player->getCurrentSprite()->get_width() >> 1)) );
	_player->setPositionY( float(windowViewPort.get_height() - _player->getCurrentSprite()->get_height()) );

	// Setting Easy
	PlayerModelImpl* model = new PlayerModelImpl( learningRate );
	model->setName( "Easy" );

	model->setTrait( PlayerModelImpl::ACCURACY, 0.0f, 0.3f, 0.5f, (0.0f + 0.3f)*0.5f );
	model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.0f, 0.3f, 1.0f, (0.0f + 0.3f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_WAVE, 0.0f, 0.3f, 0.6f, (0.0f + 0.3f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_TOTAL, 0.0f, 0.3f, 1.0f, (0.0f + 0.3f)*0.5f );

	_aiManager->addPlayerModel( model );

	// Setting Normal
	model = new PlayerModelImpl( learningRate );
	model->setName( "Normal" );

	model->setTrait( PlayerModelImpl::ACCURACY, 0.3f, 0.6f, 0.5f, (0.3f + 0.6f)*0.5f );
	model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.3f, 0.6f, 1.0f, (0.3f + 0.6f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_WAVE, 0.3f, 0.6f, 0.6f, (0.3f + 0.6f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_TOTAL, 0.3f, 0.6f, 1.0f, (0.3f + 0.6f)*0.5f );

	_aiManager->addPlayerModel( model );

	// Setting Hard
	model = new PlayerModelImpl( learningRate );
	model->setName( "Hard" );

	model->setTrait( PlayerModelImpl::ACCURACY, 0.6f, 1.0f, 0.5f, (0.6f + 1.0f)*0.5f );
	model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.6f, 1.0f, 1.0f, (0.6f + 1.0f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_WAVE, 0.6f, 1.0f, 0.6f, (0.6f + 1.0f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_TOTAL, 0.6f, 1.0f, 1.0f, (0.6f + 1.0f)*0.5f );

	_aiManager->addPlayerModel( model );
	_aiManager->setCurrentPlayerModel( _player->getPlayerModel() );

	// TODO: Should not be here!!!!
	_gameOverScene = new FadingScene( 2000.0f, 2000.0f, 2000.0f, FadingScene::FM_FADE_INOUT );
	StaticEntity* newEntity = new StaticEntity( 0.0f, 0.0f, "scenes/gameover" ); // Fading scene deletes this
	newEntity->setAlpha( 0.0f );
	_gameOverScene->insertEntity( newEntity );
}



AIManager* GameManager::getAIManager()
{
	return _aiManager;
}



CL_Logger* GameManager::getLogger()
{
	return _loggerFile;
}




FadingScene* GameManager::getGameOverScene()
{
	return _gameOverScene;
}



void GameManager::playSoundEffect( SoundEffects sound )
{
	_soundEffectSessions[sound] = _soundEffects[sound].play();
}



bool GameManager::poolSoundEffect( SoundEffects sound )
{
	return _soundEffectSessions[sound].is_playing();
}




void GameManager::stopSoundEffect( SoundEffects sound )
{
	if (poolSoundEffect( sound ))
	{
		_soundEffectSessions[sound].stop();
	}
}



void GameManager::playMusic( Musics music )
{
	_musicSessions[music] = _musics[music].play();
}



bool GameManager::poolMusic( Musics music )
{
	return _musicSessions[music].is_playing();
}



void GameManager::stopMusic( Musics music )
{
	if (poolMusic( music ))
	{
		_musicSessions[music].stop();
	}
}



void GameManager::loadSoundEffects()
{
	_soundEffectSessions.resize( SFX_VECTOR_SIZE );

	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/Attention.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/PrepareForAction.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/Warning.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/MENU_Select.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/MENU_Pick.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/laser1.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/laser3.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/slimeball.wav" ) );
	_soundEffects.push_back( CL_SoundBuffer( "../../../../data/sounds/Explosion.wav" ) );
}



void GameManager::loadMusics()
{
	_musicSessions.resize( MUSIC_VECTOR_SIZE );

	_musics.push_back( CL_SoundBuffer( "../../../../data/musics/DIGITAL_MEMORIES.ogg", false ) );
}
