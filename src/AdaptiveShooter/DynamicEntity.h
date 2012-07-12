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
	 * @param	  speedX	In pixels per second
	 * @param	  speedY	In pixels per second
	 */
	DynamicEntity(float x, float y, float speedX, float speedY);

	/**
	 * Constructor
	 * 
	 * @param	  position
	 * @param	  speed		In pixels per second
	 * @return	  
	 */
	DynamicEntity(CL_Vec2f& position, CL_Vec2f& speed);

	virtual ~DynamicEntity();

	virtual void draw();

	virtual void update() = 0;

	/**
	 * Gets speed
	 *
	 * @return	  CL_Vec2f
	 */
	CL_Vec2f getSpeed() const;

	/**
	 * Sets speed
	 * 
	 * @param	  x	Speed value in x axis in pixels per second
	 * @param	  y	Speed value in y axis in pixels per second
	 */
	void setSpeed(float x, float y);

	/**
	 * Sets speed
	 *
	 * @param	  speed	In pixels per second
	 */
	void setSpeed(CL_Vec2f& speed);

	/**
	 * Sets speed x component
	 * 
	 * @param	  x	Speed value in x axis in pixels per second
	 */
	void setSpeedX(float x);

	/**
	 * Sets speed y component
	 * 
	 * @param	  y Speed value in y axis in pixels per second
	 */
	void setSpeedY(float y);

	/**
	 * Gets the current collision outline from the current sprite
	 * 
	 * @return	  const CL_CollisionOutline*	Const pointer to current collision outline
	 */
	CL_CollisionOutline* getCurrentCollisionOutline() const;

protected:
	std::vector<CL_CollisionOutline*> _currentOutlines;
private:
	CL_Vec2f _speed;
};

#endif // DynamicEntity_h__
