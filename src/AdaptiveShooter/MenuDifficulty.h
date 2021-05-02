/********************************************************************
	created:	2012/07/25
	created:	25:7:2012   12:35
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\MenuDifficulty.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	MenuDifficulty
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/
#pragma once

#include "Menu.h"
#include "FadingScene.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"

class MenuDifficulty : public Menu, public FadingScene
{
public:

	MenuDifficulty();
	virtual ~MenuDifficulty();

	virtual void draw();

	virtual void update();

	virtual void ExecuteState();

protected:
	
private:

	enum {
		DIFFICULTY_EASY = 0,
		DIFFICULTY_NORMAL,
		DIFFICULTY_HARD
	};

	bool _isFading;

#ifdef _DEBUG
	clan::Font* _font;
#endif
};
