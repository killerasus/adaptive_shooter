/********************************************************************
	created:	2012/06/18
	created:	18:6:2012   17:40
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\DynamicEntity.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	DynamicEntity
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef DynamicEntity_h__
#define DynamicEntity_h__

#include "Entity.h"

class DynamicEntity : public Entity
{
public:
	DynamicEntity();

	/**
	 * Constructor
	 * 
	 * @param	  x
	 * @param	  y
	 * @param	  speedX
	 * @param	  speedY
	 */
	DynamicEntity(float x, float y, float speedX, float speedY);

	/**
	 * Constructor
	 * 
	 * @param	  position
	 * @param	  speed
	 * @return	  
	 */
	DynamicEntity(CL_Vec2f& position, CL_Vec2f& speed);

	virtual ~DynamicEntity();

	/**
	 * Gets speed
	 *
	 * @return	  CL_Vec2f
	 */
	CL_Vec2f getSpeed() const;

	/**
	 * Sets speed
	 * 
	 * @param	  x	Speed value in x axis
	 * @param	  y	Speed value in y axis
	 */
	void setSpeed(float x, float y);

	/**
	 * Sets speed
	 *
	 * @param	  speed
	 */
	void setSpeed(CL_Vec2f& speed);

	virtual void draw() = 0;

	virtual void update() = 0;

protected:
	
private:
	CL_Vec2f _speed;
};

#endif // DynamicEntity_h__
