/********************************************************************
	created:	2012/07/28
	created:	28:7:2012   18:21
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Explosion.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Explosion
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef Explosion_h__
#define Explosion_h__

#include "DynamicEntity.h"

class Explosion : public DynamicEntity
{
public:
	/**
	 * Constructor
	 * 
	 * @param[in]	x			Center of the explosion in x axis in pixels
	 * @param[in]	y			Center of the explosion in y axis in pixels
	 * @param[in]	speedX		Speed in x axis in pixels per second
	 * @param[in]	speedY		Speed in y axis in pixels per second
	 * @param[in]	resource	Explosion resource id
	 */
	Explosion( float x, float y, float speedX, float speedY, std::string resource );

	~Explosion();

	virtual void update();

protected:
	
private:
};

#endif // Explosion_h__