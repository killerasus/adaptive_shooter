/********************************************************************
	created:	2012/01/04
	created:	4:1:2012   4:26
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\MenuItem.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	MenuItem
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef MenuItem_h__
#define MenuItem_h__

#include "Entity.h"
#include <string>

class MenuItem : public Entity
{
public:

	enum MenuItemState{
		MIStateNotSelected = 0,
		MIStateSelected
	};

	MenuItem(float x, float y, std::string notSelectedResource_id, std::string SelectedResource_id);

	virtual ~MenuItem();

	virtual void draw();

	virtual void update();

protected:
	
private:
	CL_Sprite *_selected;
	CL_Sprite *_notSelected;
	MenuItemState _state;
};

#endif // MenuItem_h__
