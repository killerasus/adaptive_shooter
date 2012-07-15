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

class TestScenePlayer : public Scene
{
public:
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
};

#endif // TestScenePlayer_h__
