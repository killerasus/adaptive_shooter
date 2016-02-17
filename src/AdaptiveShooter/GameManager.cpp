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
#include "ClanLib/core.h"

GameManager* GameManager::_instance = 0;

GameManager::GameManager(): setup_core(), setup_display(), setup_gl(), setup_sound(), sound_output(44100),
	_canvas( NULL ), _quit( false ), _player( NULL ), _playerOptions( NULL ), _enemyOptions ( NULL )
{
	L = lua_open();
	luaL_openlibs(L);
	RegisterLuaCLHelper(L);

	// Creates window
	_window = new clan::DisplayWindow("Adaptive Shooter - Bruno Baere", 640, 480);
	_canvas = new clan::Canvas( *_window );

	_aiManager = new AIManager(L);
	//_loggerFile = new logog::LogFile("test.txt");
	_loggerFile = new clan::FileLogger("log.txt");
	_loggerFile->enable();
	// Player can only be created when there is already a GameManager instantiated

	// Loads sounds and prepare
	loadSoundEffects();
	loadMusics();
	loadOptions();
}



GameManager::~GameManager()
{
	cleanUp();
}



void GameManager::loadXMLResource( std::string resourceFile )
{
	_resourceDocument = clan::XMLResourceDocument(resourceFile);
	_resourceManager = clan::XMLResourceManager::create( _resourceDocument );
}



int GameManager::loop()
{
	try
	{
		_last_time = _game_time.get_time_elapsed_ms();

		while (!_quit)
		{
			if(_window->get_ic().get_keyboard().get_keycode(clan::keycode_escape) == true)
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
			clan::KeepAlive::process();

			// Avoid using 100% CPU in the loop:
			clan::System::sleep(10);
		}
	}
	catch(clan::Exception &exception)
	{
		// Create a console window for text-output if not available
		clan::ConsoleWindow console("Console", 80, 160);
		clan::Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
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
	_window->get_gc().clear(clan::Colorf::black);

	if (!_sceneStack.empty() && _sceneStack.top() != NULL)
	{
		_sceneStack.top()->draw();
	}

	// Make the stuff visible:
	_window->flip();
}



void GameManager::update()
{
	_time_delta_ms = _game_time.get_tick_time_elapsed_ms();

	if (_time_delta_ms > 1000)
		_time_delta_ms = 1000;		// Limit the time difference, if the application was paused (eg, moving the window on WIN32)

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



clan::DisplayWindow* GameManager::getWindow()
{
	return _window;
}



const clan::ResourceManager& GameManager::getResourceManager() const
{
	return _resourceManager;
}


const clan::XMLResourceDocument& GameManager::getResourceDocument() const
{
	return _resourceDocument;
}


int GameManager::getDeltaTime()
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
	delete _playerOptions;
	_playerOptions = NULL;

	delete _enemyOptions;
	_enemyOptions = NULL;

	delete _aiManager;
	_aiManager = NULL;

	lua_close(L);
	L = NULL;

	delete _gameOverScene;
	_gameOverScene = NULL;

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
	clan::Rect windowViewPort = _window->get_viewport();
	_player = new Player( 0.0f, 0.0f, _playerOptions->speedX, _playerOptions->speedY, n, _playerOptions->resource,
		new PlayerModelImpl( _playerOptions->learningRate ), _playerOptions->lives );
	//_player->setupCollisionOutlines();
	_player->setPositionX( float((windowViewPort.get_width() >> 1) - (_player->getCurrentSprite().get_width() >> 1)) );
	_player->setPositionY( float(windowViewPort.get_height() - _player->getCurrentSprite().get_height()) );

	// Setting Easy
	PlayerModelImpl* model = new PlayerModelImpl( _playerOptions->learningRate );
	model->setName( "Easy" );

	model->setTrait( PlayerModelImpl::ACCURACY, 0.0f, 0.3f, 0.5f, (0.0f + 0.3f)*0.5f );
	//model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.0f, 0.3f, 1.0f, (0.0f + 0.3f)*0.5f );
	model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.6f, 1.0f, 1.0f, (0.6f + 1.0f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_WAVE, 0.0f, 0.3f, 0.6f, (0.0f + 0.3f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_TOTAL, 0.0f, 0.3f, 1.0f, (0.0f + 0.3f)*0.5f );

	_aiManager->addPlayerModel( model );

	// Setting Normal
	model = new PlayerModelImpl( _playerOptions->learningRate );
	model->setName( "Normal" );

	model->setTrait( PlayerModelImpl::ACCURACY, 0.3f, 0.6f, 0.5f, (0.3f + 0.6f)*0.5f );
	model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.3f, 0.6f, 1.0f, (0.3f + 0.6f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_WAVE, 0.3f, 0.6f, 0.6f, (0.3f + 0.6f)*0.5f );
	model->setTrait( PlayerModelImpl::ENEMIES_WASTED_TOTAL, 0.3f, 0.6f, 1.0f, (0.3f + 0.6f)*0.5f );

	_aiManager->addPlayerModel( model );

	// Setting Hard
	model = new PlayerModelImpl( _playerOptions->learningRate );
	model->setName( "Hard" );

	model->setTrait( PlayerModelImpl::ACCURACY, 0.6f, 1.0f, 0.5f, (0.6f + 1.0f)*0.5f );
	//model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.6f, 1.0f, 1.0f, (0.6f + 1.0f)*0.5f );
	model->setTrait( PlayerModelImpl::LIVES_VARIATION, 0.0f, 0.3f, 1.0f, (0.0f + 0.3f)*0.5f );
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



clan::Logger* GameManager::getLogger()
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

#ifdef _DEBUG
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/Attention.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/PrepareForAction.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/Warning.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/MENU_Select.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/MENU_Pick.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/laser1.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/laser3.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/slimeball.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "../../data/sounds/Explosion.wav" ) );
#else
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/Attention.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/PrepareForAction.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/Warning.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/MENU_Select.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/MENU_Pick.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/laser1.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/laser3.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/slimeball.wav" ) );
	_soundEffects.push_back( clan::SoundBuffer( "./data/sounds/Explosion.wav" ) );
#endif
	
}



void GameManager::loadMusics()
{
	_musicSessions.resize( MUSIC_VECTOR_SIZE );

#ifdef _DEBUG
	_musics.push_back( clan::SoundBuffer( "../../data/musics/DIGITAL_MEMORIES.ogg", false ) );
#else
	_musics.push_back( clan::SoundBuffer( "./data/musics/DIGITAL_MEMORIES.ogg", false ) );
#endif
}



GameManager::PlayerOptions* GameManager::getPlayerOptions()
{
	return _playerOptions;
}



GameManager::EnemyOptions* GameManager::getEnemyOptions()
{
	return _enemyOptions;
}



void GameManager::loadOptions()
{
	_playerOptions = new PlayerOptions();

	_playerOptions->speedX = 100.0f;
	_playerOptions->speedY = 100.0f;
	_playerOptions->resource = "sprites/rwing";
	_playerOptions->lives = 3;
	_playerOptions->learningRate = 0.3f;
	_playerOptions->shotSpeedX = 0.0f;
	_playerOptions->shotSpeedY = -200.0f;
	_playerOptions->shotDelay = 800.0f;
	_playerOptions->hitBoxScale = 1.0f;

	_enemyOptions = new EnemyOptions();

	_enemyOptions->shotSpeedX = 0.0f;
	_enemyOptions->shotSpeedY = 100.0f;
	_enemyOptions->shotDelay = 800.0f;
	_enemyOptions->easyMultiplier = 0.5f;
	_enemyOptions->normalMultiplier = 1.0f;
	_enemyOptions->hardMultiplier = 1.5f;

#ifdef _DEBUG
	int loadResult = luaL_dofile( L, "../../src/Scripts/config.lua" );
#else
	int loadResult = luaL_dofile( L, "./Scripts/config.lua" );
#endif

	if (!loadResult)
	{
		lua_getglobal( L, "Player" );

		if (lua_istable( L, -1 ))
		{
			lua_getfield( L, -1, "SpeedX" );
			_playerOptions->speedX = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "SpeedY" );
			_playerOptions->speedY = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "LearningRate" );
			_playerOptions->learningRate = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "Resource" );
			_playerOptions->resource = lua_tostring( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "Lives" );
			_playerOptions->lives = (unsigned int) lua_tointeger( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "ShotSpeedX" );
			_playerOptions->shotSpeedX = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "ShotSpeedY" );
			_playerOptions->shotSpeedY = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "ShotDelay" );
			_playerOptions->shotDelay = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "HitBoxScale" );
			_playerOptions->hitBoxScale = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );
		}
		else
		{
			// Create a console window for text-output if not available
			clan::ConsoleWindow console( "Console", 80, 160 );
			clan::Console::write_line( "Could not load Player from config.lua" );
			clan::Console::write_line( "\n%1", lua_tostring( L, -1 ) );
			clan::Console::wait_for_key();

			// Pops error message from stack
			lua_pop( L, 1 );
		}

		// Pops Player table
		lua_pop( L, 1 );

		// Gets Enemies table
		lua_getglobal( L, "Enemies" );

		if (lua_istable( L, -1 ))
		{
			lua_getfield( L, -1, "ShotSpeedX" );
			_enemyOptions->shotSpeedX = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "ShotSpeedY" );
			_enemyOptions->shotSpeedY = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "ShotDelay" );
			_enemyOptions->shotDelay = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "EasyMultiplier" );
			_enemyOptions->easyMultiplier = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "NormalMultiplier" );
			_enemyOptions->normalMultiplier = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );

			lua_getfield( L, -1, "HardMultiplier" );
			_enemyOptions->hardMultiplier = (float) lua_tonumber( L, -1 );
			lua_pop( L, 1 );
		}
		else
		{
			// Create a console window for text-output if not available
			clan::ConsoleWindow console( "Console", 80, 160 );
			clan::Console::write_line( "Could not load Enemies from config.lua" );
			clan::Console::write_line( "\n%1", lua_tostring( L, -1 ) );
			clan::Console::wait_for_key();

			// Pops error message from stack
			lua_pop( L, 1 );
		}
	}
	else
	{
		// Create a console window for text-output if not available
		clan::ConsoleWindow console( "Console", 80, 160 );
		clan::Console::write_line( "Could not load config.lua" );
		clan::Console::write_line( "\n%1", lua_tostring( L, -1 ) );
		clan::Console::wait_for_key();

		// Pops error message from stack
		lua_pop( L, 1 );
	}
}

clan::Canvas& GameManager::getCanvas()
{
	return *_canvas;
}
