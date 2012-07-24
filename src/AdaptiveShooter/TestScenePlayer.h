/********************************************************************
	created:	2012/06/01
	created:	1:6:2012   5:22
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\TestScenePlayer.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestScenePlayer
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef TestScenePlayer_h__
#define TestScenePlayer_h__

#include <vector>
#include <list>

#include "ClanLib/core.h"
#include "ClanLib/display.h"

#include "Scene.h"
#include "Enemy.h"
#include "Shot.h"
#include "Player.h"

class TestScenePlayer : public Scene
{
public:

	// Used for storing data from Lua scene descriptor
	struct EnemyDescription{
		std::string resource;
		float startPositionX;
		float startPositionY;
		float speedX;
		float speedY;
		std::string instanceClass;
	};

	// Used for storing data from Lua scene descriptor
	struct Wave{
		std::vector<EnemyDescription> enemies;
	};

	// Used to access data in EnemyDescription table in Lua
	enum EnemyDescriptionData
	{
		EDD_SPRITE_RESOURCE = 1,
		EDD_START_X,
		EDD_START_Y,
		EDD_SPEED_X,
		EDD_SPEED_Y,
		EDD_CLASS
	};

	TestScenePlayer();

	virtual ~TestScenePlayer();

	virtual void draw();

	virtual void update();

	/**
	 * Adds a player shot to the Scene entities and player's shots control list
	 * 
	 * @param	  newShot
	 * @return	  void
	 */
	void addPlayerShot(Shot* newShot);

	/**
	 * Adds an enemy shot to the Scene entities and enemies' shots control list
	 * 
	 * @param	  newShot
	 * @return	  void
	 */
	void addEnemyShot(Shot* newShot);

private:
	CL_Font* _font;
	std::vector<Enemy*> _enemies;
	std::list<Shot*> _playerShots;
	std::list<Shot*> _enemyShots;
	std::vector<Wave> _waves;

	// Player One
	int _shotsWave;
	int _shotsWaveOnTarget;
	int _shotsTotal;
	int _shotsTotalOnTarget;
	int _livesStartWave;
	int _livesEndWave;
	int _enemiesWave;
	int _enemiesWaveWasted;
	int _enemiesTotal;
	int _enemiesTotalWasted;

	float _keyDelayTime; // Miliseconds
	float _timer; // Miliseconds
	bool _canPressKey;
	unsigned int _waveNumber;
	bool _waveOn;

	/**
	 * Removes player shot from Scene entities and player's shot control.
	 * 
	 * @param	  shot
	 * @return	  void
	 */
	void removePlayerShot(Shot* shot);

	/**
	 * Removes enemy shot from Scene entities and enemies' shot control.
	 * 
	 * @param	  shot
	 * @return	  void
	 */
	void removeEnemyShot(Shot* shot);

	/**
	 * Computes collision for each shot in Scene and boundary exit
	 */
	void computeShotsCollision();

	/**
	 * Begins wave variables
	 */
	void waveBegin();

	/**
	 * Updates player model based on wave scores, updates scene totals
	 */
	void waveFinish();

	/**
	 * Checks if any enemy is dead or out of bounds. Sets Player's and Wave's variables accordingly.
	 */
	void validateEnemies();

	/**
	 * Adds an enemy to the wave. Also registers in AIManager and in Scene entities list.
	 * 
	 * @param[in]  enemy	Pointer to enemy to add
	 */
	void addWaveEnemy( Enemy* enemy );

	/**
	 * Applies damage to Enemy and updates wave and scene shot variables.
	 * 
	 * @param[in]  shot		Pointer to shot that hit the enemy
	 * @param[in]  enemy	Pointer to enemy hit by the shot
	 */
	void computeShotHitEnemy( Shot* shot, Enemy* enemy );

	/**
	 * Applies damage to Player and updates wave and scene shot variables
	 * 
	 * @param[in]	shot
	 * @param[in]	player
	 */
	void computeShotHitPlayer( Shot* shot, Player* player );

#ifdef _DEBUG
	void createDebugEnemy();
#endif

	/**
	 * Instantiates a wave from _waves
	 * 
	 * @param[in]  i	Wave position in the container
	 */
	void createWave( int i );

	/**
	 * Loads scene from a Lua file
	 * 
	 * @param[in]	sceneFile	Lua file containing a scene table
	 */
	void loadScene( std::string sceneFile );
};

#endif // TestScenePlayer_h__
