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

private:
	CL_Font* _font;
	std::vector<Enemy*> _enemies;
	std::vector<Shot*> _playerShots;
	std::vector<Shot*> _enemyShots;
};

#endif // TestScenePlayer_h__
