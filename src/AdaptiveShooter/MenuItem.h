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

	/**
	 * Constructor
	 * 
	 * @param[in]	x						x axis position
	 * @param[in]	y						y axis position
	 * @param[in]	selectedResource_id		Selected image resource
	 * @param[in]	notSelectedResource_id	Not selected image resource
	 */
	MenuItem(float x, float y, std::string selectedResource_id, std::string notSelectedResource_id);

	virtual ~MenuItem();

	virtual void draw();

	virtual void update();

	/**
	 * Sets if MenuItem is selected
	 * 
	 * @param[in]	selected	True if selected, else false
	 */
	void setSelected( bool selected );

	/**
	 * Gets if MenuItem is selected
	 */
	bool getSelected();

protected:
	
private:
	CL_Sprite *_selected;
	CL_Sprite *_notSelected;
	bool _isSelected;
};

#endif // MenuItem_h__
