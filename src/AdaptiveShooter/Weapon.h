/********************************************************************
	created:	2012/07/15
	created:	15:7:2012   3:40
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Weapon.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Weapon
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	This class represents weapon enhancements gained by the Player
*********************************************************************/

#ifndef Weapon_h__
#define Weapon_h__

#include <ClanLib/core.h>
#include "Shot.h"

// TODO: Modify for receiving which player created the shot
class Weapon
{
public:

	/** Describes weapon level */
	enum WeaponLevel
	{
		WL_LEVEL_0,
		WL_LEVEL_1,
		WL_LEVEL_2
	};

	/**
	 * Constructor
	 * 
	 * @param[in]	name			Weapon's name
	 * @param[in]	shotResource	Resource string
	 * @param[in]	delay			Delay between shots in miliseconds
	 * @param[in]	damage			Base damage caused by each shot
	 * @param[in]	level			Weapon's level
	 */
	Weapon(std::string name, std::string shotResource, float delay, int damage = 50, WeaponLevel level = WL_LEVEL_0);

	/** Destructor */
	virtual ~Weapon();

	/**
	 * Updates weapon's timer
	 */
	virtual void update();

	/**
	 * Sets if weapon can shoot. Resets current weapon timer.
	 *
	 * @param[in]	can	true or false
	 */
	void setCanShoot( bool can );

	/**
	 * Gets weapon's shooting state
	 * 
	 * @return	  bool	true if weapon can shoot right now
	 */
	bool getCanShoot() const;

	/**
	 * Sets weapon's delay between shoots timer. If delay is negative, it's set to 0.0f.
	 * 
	 * @param[in]  delay	Delay in miliseconds
	 */
	void setDelay( float delay );

	/**
	 * Gets weapon's current time delay between shoots
	 * 
	 * @return	  float	Weapon delay between shoots in miliseconds
	 */
	float getDelay() const;

	/**
	 * Gets current timer
	 * 
	 * @return	float	Current timer value in miliseconds
	 */
	float getTimer() const;

	/**
	 * Sets weapon's shoot damage. If damage is negative, it's set to 1.
	 * 
	 * @param[in]  damage	Damage amount
	 */
	void setDamage( int damage );

	/**
	 * Gets weapon's current shoot damage
	 * 
	 * @return	  int	Damage amount
	 */
	int getDamage() const;

	/**
	 * Sets weapon's current level
	 * 
	 * @param[in]  level	Weapon's level
	 */
	void setWeaponLevel( WeaponLevel level );

	/**
	 * Gets weapon's current level
	 * 
	 * @return	Weapon::WeaponLevel	Weapon's current level
	 */
	WeaponLevel getWeaponLevel() const;

	/**
	 * Makes weapon shoot. Instantiates new Shot objects in current Scene. Delegates deletion to Scene.
	 *
	 * @return	int	How many shots were created. 0 if canShoot returns false
	 */
	virtual int shoot();

protected:
	
private:
	bool _canShoot; // Indicates if weapon is ready to shoot
	int _damage; // Damage caused by each shot
	WeaponLevel _level; // Weapon's level
	float _delay; // Indicates delay between shots in miliseconds
	float _timer; // Current weapon timer in miliseconds.
	std::string _name; // Weapon's name
	std::string _shotResource; // Resource file for creating shots
};

#endif // Weapon_h__
