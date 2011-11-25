/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   2:04
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AIManager\aimanager.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AIManager
	file base:	aimanager
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	AIManager is the class that manages AI updates, collects user data for dynamic difficulty adjustment
				and does the adjustment to each agent it manages. It's functionalities are customized via Lua functions
				implemented by the user-programmer and provided via a Lua state
*********************************************************************/

#include <vector>
#include "aiagent.h"
#include "playermodel.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class AIManager
{
public:
	AIManager(lua_State* L);
	virtual ~AIManager();
	void update();
	void SetLuaState(lua_State* L);
	lua_State* GetLuaState();
protected:

private:
	lua_State *_luaState;
	PlayerModel *_currentPlayerModel;
	std::vector<PlayerModel*> _playerModels;
	std::vector<AIAgent*> _aiAgents;
};