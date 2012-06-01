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

#include "Scene.h"

class TestScenePlayer : public Scene
{
public:
	TestScenePlayer();
	virtual ~TestScenePlayer();

	virtual void draw();

	virtual void update();

};

#endif // TestScenePlayer_h__
