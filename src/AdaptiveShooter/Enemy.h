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

	enum EnemyBehavior{
		DONTSHOOT = 0,
		SHOOT = 1,
		GODOWN = 2,
		GOHORIZONTAL = 4,
		GOSINUSOID = 8
	};

	/**
	 * Constructor
	 */
	Enemy();

	/**
	 * Constructor
	 * 
	 * @param[in]	x
	 * @param[in]	y
	 * @param[in]	speedX	In pixels per second
	 * @param[in]	speedY	In pixels per second
	 * @param[in]	health	Health points
	 * @param[in]	points	Points value
	 */
	Enemy(float x, float y, float speedX, float speedY, int health = 50, int points = 100);

	/**
	 * Constructor
	 * 
	 * @param[in]	position
	 * @param[in]	speed	In pixels per second
	 * @param[in]	health	Health points
	 * @param[in]	points	Points value
	 */
	Enemy(clan::Vec2f& position, clan::Vec2f& speed, int health = 50, int points = 100);

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

	/**
	 * Sets enemy health value
	 * 
	 * @param[in]  health	New health
	 */
	void setHealth( int health );

	/**
	 * Gets enemy's current health value
	 * 
	 * @return	int	Health value
	 */
	int getHealth();

	/**
	 * Gets the multiplier value
	 * 
	 * @return	float	The multiplier value
	 */
	float getMultiplier();

	/**
	 * Gets the enemy's behavior
	 * 
	 * @return	  Enemy::EnemyBehavior	The current behavior
	 */
	unsigned int getBehavior();

	/**
	 * Sets the enemy behavior
	 */
	void setBehavior( unsigned int behavior );

	void setAmplitudeLimit( float limit );

	float getAmplitudeLimit();

protected:
	float _multiplier; // Speed multiplier
	unsigned int _behavior;
	float _amplitudeLimit; // For sinusoid behavior
	float _currentAmplitude;
private:
	int _points; // Score points value
	int _health; // Health points
};
#endif
