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
	 * @param[in]	x			X coordinate referring to the middle of the sprite in screen coordinates
	 * @param[in]	y			Y coordinate referring to the bottom of the sprite in screen coordinates
	 * @param[in]	speedX		X axis speed in pixels per second
	 * @param[in]	speedY		Y axis speed in pixels per second
	 * @param[in]	resource	Resource location in resource file
	 * @param[in]	damage		Amount of damage caused to Entity
	 */
	Shot(float x, float y, float speedX, float speedY, std::string resource, int damage);
	
	/**
	 * Constructor
	 * 
	 * @param[in]	position	Coordinates referring to the middle and bottom of the sprite in screen coordinates
	 * @param[in]	speed		Speed vector in pixels per second
	 * @param[in]	resource	Resource location in resource file
	 * @param[in]	damage		Amount of damage caused to Entity
	 */
	Shot(CL_Vec2f& position, CL_Vec2f& speed, std::string resource, int damage);

	virtual ~Shot();

#ifdef _DEBUG
	virtual void draw();
#endif // _DEBUG

	virtual void update();

	/**
	 * Sets shot damage amount
	 * 
	 * @param	  damage	Damage value
	 */
	void setDamage( int damage );

	/**
	 * Gets shot damage amount
	 * 
	 * @return	  int	Amount of damage to be applied
	 */
	int getDamage ();

protected:
	
private:
	int _damage;
};

#endif // Shot_h__
