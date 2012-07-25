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
	//TODO: Import player models from Lua State
}



AIManager::~AIManager()
{
	std::vector<PlayerModel*>::iterator it;

	for (it = _playerModels.begin(); it != _playerModels.end(); )
	{
		delete (*it);
		it = _playerModels.erase( it );
	}
}



void AIManager::update()
{
	std::vector<PlayerModel*>::iterator itPM;
	float result(0.0f);

	for (itPM = _playerModels.begin(); itPM != _playerModels.end(); itPM++)
	{
		result = _currentObservedPlayerModel->compare( *itPM );

		// Checks if observed player model is lesser than current comparable player model
		if (result < 0.0f)
		{
			continue;
		}
		else
		{
			// Checks if observed player model matches current comparable player model
			if (result == 0.0f)
			{
				_currentReferenceModel = *itPM;
				break;
			}
			else
			{
				// Checks if observed player model is superior to current comparable player model
				if (result)
				{
					// Compares referenced with current comparable
					result = _currentReferenceModel->compare( *itPM );

					// Checks if reference model is inferior to current comparable
					if (result < 0.0f)
					{
						// Reference model should be updated to current comparable
						_currentReferenceModel = *itPM;
					} 
				}
			}
		}
	}

	_currentObservedPlayerModel->setName( _currentReferenceModel->getName() );

	std::vector<AIAgent*>::iterator it;

	for (it = _aiAgents.begin(); it != _aiAgents.end(); it++)
	{
		(*it)->updateStats();
	}
}



void AIManager::setLuaState( lua_State* L )
{
	_luaState = L;
}



lua_State* AIManager::getLuaState() const
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



void AIManager::setCurrentPlayerModel( PlayerModel* model )
{
	_currentObservedPlayerModel = model;
}



PlayerModel* AIManager::getCurrentPlayerModel() const
{
	return _currentObservedPlayerModel;
}



void AIManager::setCurrentReferenceModel( PlayerModel* model )
{
	_currentReferenceModel = model;
}



PlayerModel* AIManager::getCurrentReferenceModel() const
{
	return _currentReferenceModel;
}



void AIManager::addPlayerModel( PlayerModel* model )
{
	_playerModels.push_back( model );
}



bool AIManager::removePlayerModel( PlayerModel* model )
{
	bool result = false;

	std::vector<PlayerModel*>::iterator it;

	for (it = _playerModels.begin(); it != _playerModels.end(); it++)
	{
		if ((*it) == model)
		{
			_playerModels.erase( it );
			result = true;
			break;
		}
	}

	return result;
}



std::vector<PlayerModel*>* AIManager::getPlayerModelVector() const
{
	return new std::vector<PlayerModel*>( _playerModels );
}
