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
#include "AIManager.h"

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

	static GameManager* GetInstance();
	virtual ~GameManager();

	/**
	 * Main game loop implementation
	 * 
	 * @return	  int	Loop result. 0 if ok, other in case of error
	 */
	int Loop();

	void LoadResource(std::string resourceFile);

	void CleanUp();

	/**
	 * Pushes a scene into stack. Top of the stack scene is rendered and updated.
	 * 
	 * @param	  Scene*
	 */
	void PushScene(Scene*);

	/**
	 * Pops the scene from the top of the scene stack.
	 * 
	 * @return	  Scene*	Scene popped. Null if no scene is in stack.
	 */
	Scene* PopScene();

	/**
	 * Gets current game window
	 * 
	 * @return	  CL_DisplayWindow*
	 */
	CL_DisplayWindow* GetWindow();

	/**
	 * Gets resource manager
	 * 
	 * @return	  CL_ResourceManager*
	 */
	CL_ResourceManager* GetResourceManager();

	/**
	 * Gets current Lua state
	 * 
	 * @return	  lua_State*
	 */
	lua_State* GetLuaState();

	/**
	 * Sets current Lua state
	 * 
	 * @param	  l	Lua state
	 */
	void SetLuaState(lua_State* l);

	/**
	 * Gets current loop delta time
	 * 
	 * @return	  float	time since last loop in miliseconds
	 */
	float GetDeltaTime();

protected:
	GameManager();
	virtual void Draw();
	virtual void Update();
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
	AIManager _aiManager;

	static GameManager* _instance;
};

#endif // GameManager_h__