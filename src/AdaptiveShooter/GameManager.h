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

#ifndef GameManager_h__
#define GameManager_h__

#include <stack>

#include "ClanLib/core.h"
#include "ClanLib/display.h"

#ifdef _GL1
	#include "ClanLib/gl1.h"
#else
	#include "ClanLib/gl.h"
#endif

#include "Scene.h"
#include "FadingScene.h"
#include "AIManager/AIManager.h"
#include "Player.h"

extern "C"
{
	#include "lua.h"
};

// Logging tool
//#define LOGOG_USE_PREFIX 1
//#include "logog.hpp"

/**
 * GameManager provides a Singleton interface for manipulating elements common to
 * the game
 */
class GameManager
{
public:

	static GameManager* getInstance();
	virtual ~GameManager();

	/**
	 * Main game loop implementation
	 * 
	 * @return	  int	Loop result. 0 if ok, other in case of error
	 */
	int loop();

	void loadResource(std::string resourceFile);

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
	CL_DisplayWindow* getWindow();

	/**
	 * Gets resource manager
	 * 
	 * @return	  CL_ResourceManager*
	 */
	CL_ResourceManager* getResourceManager();

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
	 * @return	  float	time since last loop in miliseconds
	 */
	float getDeltaTime();

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
	CL_Logger* getLogger();

	/**
	 * Gets the GameOver scene
	 * 
	 * @return	FadingScene*	Game over, man, game over
	 */
	FadingScene* getGameOverScene();

protected:
	GameManager();
	virtual void draw();
	virtual void update();
private:
	CL_SetupCore setup_core;
	CL_SetupDisplay setup_display;
#ifdef _GL1
	CL_SetupGL1 setup_gl;
#else
	CL_SetupGL setup_gl;
#endif // _GL1

	CL_ResourceManager* _resourceManager;
	CL_DisplayWindow* _window;

	lua_State *L;
	bool _quit;

	unsigned int _last_time;
	unsigned int _current_time;
	float _time_delta_ms;

	std::stack<Scene*> _sceneStack;
	AIManager* _aiManager;
	Player* _player;

	static GameManager* _instance;

	FadingScene* _gameOverScene;

	//logog::LogFile* _loggerFile;
	CL_Logger* _loggerFile;
};

#endif // GameManager_h__
