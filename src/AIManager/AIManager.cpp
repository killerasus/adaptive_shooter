/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   2:03
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AIManager\aimanager.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AIManager
	file base:	aimanager
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation for AIManager class
*********************************************************************/

#include "AIManager.h"

AIManager::AIManager(lua_State* L):_luaState(L)
{
}

AIManager::~AIManager()
{
}

void AIManager::update()
{

}

void AIManager::SetLuaState( lua_State* L )
{
	_luaState = L;
}

lua_State* AIManager::GetLuaState()
{
	return _luaState;
}

void AIManager::insertAgent( AIAgent* agent )
{
	if (agent != NULL)
	{
		_aiAgents.push_back( agent );
	}
}

bool AIManager::removeAgent( AIAgent* agent )
{
	for (std::vector<AIAgent*>::iterator it = _aiAgents.begin(); it != _aiAgents.end(); it++)
	{
		if (*it == agent)
		{
			_aiAgents.erase( it );
			return true;
		}
	}

	return false;
}

unsigned int AIManager::getNumberofAgents() const
{
	return _aiAgents.size();
}
