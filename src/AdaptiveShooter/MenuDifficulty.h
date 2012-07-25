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
#ifndef MenuDifficulty_h__
#define MenuDifficulty_h__


#include "Menu.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"

class MenuDifficulty : public Menu
{
public:

	MenuDifficulty();
	virtual ~MenuDifficulty();

#ifdef _DEBUG
	virtual void draw();
#endif

	virtual void ExecuteState();

protected:
	
private:

	enum {
		DIFFICULTY_EASY = 0,
		DIFFICULTY_NORMAL,
		DIFFICULTY_HARD
	};

#ifdef _DEBUG
	CL_Font* _font;
#endif
};

#endif // MenuDifficulty_h__
