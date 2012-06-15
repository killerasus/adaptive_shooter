/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   9:59
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\TestScene.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestScene
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Test scene declaration
*********************************************************************/
#ifndef TestScene_h__
#define TestScene_h__

#include "Scene.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	/* overrides */
	virtual void draw();
	virtual void update();

protected:
	
private:
	float _x, _y;
	float _speed;
	CL_Font* _font;
	CL_Sprite* _boatSprite;
};

#endif // TestScene_h__
