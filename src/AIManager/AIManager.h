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
#pragma once

#include <vector>
#include "AIAgent.h"
#include "PlayerModel.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class AIManager
{
public:
	/**
	 * Constructor
	 * 
	 * @param	  L	Lua state that is watched and manipulated
	 */
	AIManager( lua_State* L );

	/** Destructor */
	virtual ~AIManager();

	/**
	 * Checks PlayerModel updates and updates AIAgents accordingly
	 */
	void update();

	/**
	 * Sets Lua state observed
	 * @param	  L	New Lua state
	 */
	void setLuaState( lua_State* L );

	/**
	 * Gets lua_State currently observed
	 * 
	 * @return	  lua_State*	Current Lua state
	 */
	lua_State* getLuaState() const;

	/**
	 * Inserts a new AIAgent in the agents control list
	 *
	 * @param	  agent	AIAgent to be inserted
	 */
	void insertAgent( AIAgent* agent );

	/**
	 * Removes an agent from the agents control list
	 * 
	 * @param	  agent	AIAgent to be removed
	 * @return	  bool	True if agent was found and removed, false otherwise
	 */
	bool removeAgent( AIAgent* agent );

	
	/**
	 * Gets the number of agents in the agents control list
	 * 
	 * @return	  unsigned int
	 */
	unsigned int getNumberofAgents() const;

	/**
	 * Sets the current player model
	 *
	 * @param[in]	model	Pointer to player model to be observed
	 */
	void setCurrentPlayerModel( PlayerModel* model );

	/**
	 * Returns the current player model observed
	 *
	 * @return	PlayerModel*	Pointer to current player model observed
	 */
	PlayerModel* getCurrentPlayerModel() const;

	/**
	 * Sets the current player model being referenced
	 *
	 * @param[in]	model	Pointer to player model from the vector
	 */
	void setCurrentReferenceModel( PlayerModel* model );

	/**
	 * Returns the current player model being referenced from the list
	 *
	 * @return	PlayerModel*	Pointer to current player model referenced
	 */
	PlayerModel* getCurrentReferenceModel() const;

	/**
	 * Includes a player model in the manager. Takes responsibility of deleting the pointer.
	 * 
	 * @param	  model	Pointer to player model
	 */
	void addPlayerModel( PlayerModel*  model );

	/**
	 * Removes a PlayerModel from the manager
	 * 
	 * @param	  model	Pointer to model to remove
	 * @return	  bool	true if the model was found and removed
	 */
	bool removePlayerModel( PlayerModel* model );

	/**
	 * Gets a copy of the player model vector from the manager
	 * 
	 * @return	  std::vector<PlayerModel*>*	Returns a copy of the player model vector. Caller must delete.
	 */
	std::vector<PlayerModel*>* copyPlayerModelVector () const;

	/**
	 * Calls each AIAgent's updateStats to keep up with PlayerModel changes
	 */
	void updateAgents();

protected:

private:
	lua_State *_luaState; //Lua state used to load parameters
	PlayerModel *_currentObservedPlayerModel; //PlayerModel relative to the current observed player
	PlayerModel *_currentReferenceModel; //PlayerModel from _playerModels that matches the last observed player model
	std::vector<PlayerModel*> _playerModels; //Vector of PlayerModels
	std::vector<AIAgent*> _aiAgents;
};
