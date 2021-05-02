/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   9:07
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\GameManager.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	GameManager
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	GameManager class definition
*********************************************************************/
#pragma once

#include <stack>

#include "ClanLib/core.h"
#include "ClanLib/display.h"
#include "ClanLib/sound.h"
#include "ClanLib/gl.h"
#include "Scene.h"
#include "FadingScene.h"
#include "AIManager/AIManager.h"
#include "Player.h"

extern "C"
{
	#include "lua.h"
};

/**
 * GameManager provides a Singleton interface for manipulating elements common to
 * the game
 */
class GameManager
{
public:

	// Enum for accessing sound effects
	enum SoundEffects{
		SFX_ATTENTION = 0,
		SFX_PREPARE,
		SFX_WARNING,
		SFX_MENU_SELECT,
		SFX_MENU_PICK,
		SFX_LASER_1,
		SFX_LASER_3,
		SFX_BLASTER,
		SFX_EXPLOSION,
		SFX_VECTOR_SIZE
	};

	// Enum for accessing musics
	enum Musics{
		STAGE_1 = 0,
		MUSIC_VECTOR_SIZE
	};

	// Struct for player options set from config.lua
	struct PlayerOptions{
		float speedX;
		float speedY;
		std::string resource;
		float learningRate;
		unsigned int lives;
		float shotSpeedX;
		float shotSpeedY;
		float shotDelay;
		float hitBoxScale;
	};

	// Struct for enemy options set from config.lua
	struct EnemyOptions{
		float shotSpeedX;
		float shotSpeedY;
		float shotDelay;
		float easyMultiplier;
		float normalMultiplier;
		float hardMultiplier;
	};

	static GameManager* getInstance();
	virtual ~GameManager();

	/**
	 * Main game loop implementation
	 * 
	 * @return	  int	Loop result. 0 if ok, other in case of error
	 */
	int loop();

	void loadXMLResource(std::string resourceFile);

	void cleanUp();

	/**
	 * Pushes a scene into stack. Top of the stack scene is rendered and updated.
	 * 
	 * @param	  Scene*
	 */
	void pushScene(Scene*);

	/**
	 * Pops the scene from the top of the scene stack.
	 * 
	 * @return	  Scene*	Scene popped. Null if no scene is in stack.
	 */
	Scene* popScene();

	/**
	 * Gets the scene from the top of the scene stack. Does not pop.
	 * 
	 * @return	  Scene*	Scene on the top of the stack. Null if no scene is in stack.
	 */
	Scene* peekScene();

	/**
	 * Gets current game window
	 * 
	 * @return	  CL_DisplayWindow*
	 */
	clan::DisplayWindow* getWindow();

	/**
	 * Gets the current canvas
	 * @return clan::Canvas*
	 */
	clan::Canvas& getCanvas();

	/**
	 * Gets resource manager
	 * 
	 * @return	  CL_ResourceManager*
	 */
	const clan::ResourceManager& getResourceManager() const;

	/**
	 * Gets the resource document used to create the resource manager 
	 *
	 * @return Reference to the XML Resource Document
	 */
	const clan::XMLResourceDocument& getResourceDocument() const;

	/**
	 * Gets current Lua state
	 * 
	 * @return	  lua_State*
	 */
	lua_State* getLuaState();

	/**
	 * Sets current Lua state
	 * 
	 * @param	  l	Lua state
	 */
	void getLuaState(lua_State* l);

	/**
	 * Gets current loop delta time
	 * 
	 * @return	  float	time since last loop in milliseconds
	 */
	int getDeltaTime();

	/**
	 * Gets Player n
	 * 
	 * @param	  n			Number of the player, from 0 to max_players - 1
	 * @return	  Player*	Pointer to player, null if not instanced
	 */
	Player* getPlayer(unsigned int n);

	/**
	 * Setup player n. Call just when GameManager is instanced.
	 * 
	 * @param	  n	Number of player, from 0 to max_players - 1
	 */
	void setupPlayer(unsigned int n);

	/**
	 * Gets AIManager for the game
	 * 
	 * @return	  AIManager*	Pointer to AIManager object
	 */
	AIManager* getAIManager();

	/**
	 * Gets logger
	 *
	 * @return	CL_Logger*	Pointer to logger object
	 */
	clan::Logger* getLogger();

	/**
	 * Gets the GameOver scene
	 * 
	 * @return	FadingScene*	Game over, man, game over
	 */
	FadingScene* getGameOverScene();

	void playSoundEffect( SoundEffects sound );

	bool poolSoundEffect( SoundEffects sound );

	void stopSoundEffect( SoundEffects sound );

	void playMusic( Musics music );

	bool poolMusic( Musics music );

	void stopMusic( Musics music );

	void loadSoundEffects();

	void loadMusics();

	PlayerOptions* getPlayerOptions();

	EnemyOptions* getEnemyOptions();

protected:
	GameManager();
	virtual void draw();
	virtual void update();
private:
	clan::SetupCore setup_core;
	clan::SetupDisplay setup_display;
	clan::SetupSound setup_sound;
	clan::SoundOutput sound_output;
	clan::SetupGL setup_gl;

	clan::XMLResourceDocument _resourceDocument;
	clan::ResourceManager _resourceManager;
	clan::DisplayWindow* _window;
	clan::Canvas* _canvas;

	lua_State *L;
	bool _quit;

	clan::GameTime _game_time;
	unsigned int _last_time;
	unsigned int _current_time;
	int _time_delta_ms;

	std::stack<Scene*> _sceneStack;
	AIManager* _aiManager;
	Player* _player;

	static GameManager* _instance;

	FadingScene* _gameOverScene;

	clan::Logger* _loggerFile;

	PlayerOptions* _playerOptions;
	EnemyOptions* _enemyOptions;

	std::vector<clan::SoundBuffer> _soundEffects;
	std::vector<clan::SoundBuffer_Session> _soundEffectSessions;
	std::vector<clan::SoundBuffer> _musics;
	std::vector<clan::SoundBuffer_Session> _musicSessions;

	/**
	 * Loads player and enemy options from config.lua
	 */
	void loadOptions();
};
