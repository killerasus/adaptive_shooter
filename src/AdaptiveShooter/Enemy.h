/********************************************************************
	created:	2012/05/24
	created:	24:5:2012   14:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Enemy.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Enemy
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef Enemy_h__
#define Enemy_h__

#include "DynamicEntity.h"
#include "AIManager/AIAgent.h"

class Enemy : public DynamicEntity, public AIAgent
{
public:
	Enemy();

	/**
	 * Constructor
	 * 
	 * @param	  x
	 * @param	  y
	 * @param	  speedX	In pixels per second
	 * @param	  speedY	In pixels per second
	 */
	Enemy(float x, float y, float speedX, float speedY);

	/**
	 * Constructor
	 * 
	 * @param	  position
	 * @param	  speed		In pixels per second
	 */
	Enemy(CL_Vec2f& position, CL_Vec2f& speed);

	virtual ~Enemy();

	virtual void update() = 0;

	virtual void updateStats() = 0;

protected:
	
private:
};
#endif
