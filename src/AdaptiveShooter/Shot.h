/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   13:20
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Shot.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Shot
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef Shot_h__
#define Shot_h__

#include "DynamicEntity.h"

class Shot : public DynamicEntity
{
public:
	Shot(std::string resource);
	
	/**
	 * Constructor
	 * 
	 * @param	  x			X coordinate referring to the middle of the sprite in screen coordinates
	 * @param	  y			Y coordinate referring to the bottom of the sprite in screen coordinates
	 * @param	  speedX
	 * @param	  speedY
	 * @param	  resource
	 */
	Shot(float x, float y, float speedX, float speedY, std::string resource);
	
	/**
	 * Constructor
	 * 
	 * @param	  position	Coordinates referring to the middle and bottom of the sprite in screen coordinates
	 * @param	  speed
	 * @param	  resource
	 */
	Shot(CL_Vec2f& position, CL_Vec2f& speed, std::string resource);

	virtual ~Shot();

#ifdef _DEBUG
	virtual void draw();
#endif // _DEBUG

	virtual void update();

protected:
	
private:
};

#endif // Shot_h__
