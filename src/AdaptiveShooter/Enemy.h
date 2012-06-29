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
	 * @param[in]	x
	 * @param[in]	y
	 * @param[in]	speedX	In pixels per second
	 * @param[in]	speedY	In pixels per second
	 * @param[in]	points	Points value
	 */
	Enemy(float x, float y, float speedX, float speedY, int points = 0);

	/**
	 * Constructor
	 * 
	 * @param[in]	position
	 * @param[in]	speed	In pixels per second
	 * @param[in]	points	Points value
	 */
	Enemy(CL_Vec2f& position, CL_Vec2f& speed, int points = 0);

	virtual ~Enemy();

	virtual void update() = 0;

	virtual void updateStats() = 0;

	/**
	 * Modifies enemy's points value
	 * 
	 * @param	  points
	 */
	void setPoints(int points);

	/**
	 * Gets enemy points value
	 * 
	 * @return	  int	Enemy points value
	 */
	virtual int getPoints();

protected:
	
private:
	int _points;
};
#endif
