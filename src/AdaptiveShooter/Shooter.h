/********************************************************************
	created:	2012/07/23
	created:	23:7:2012   14:36
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Shooter.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Shooter
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/
#pragma once

#include "Weapon.h"

class Shooter
{
public:

	/**
	 *	Constructor
	 */
	Shooter();

	/**
	 * Constructor
	 * 
	 * @param[in]  weapon	Pointer to current weapon
	 */
	Shooter( Weapon* weapon );
	
	/**
	 * Destructor
	 */
	~Shooter();

	/**
	 * Set's the Entity's current weapon
	 * 
	 * @param	  newWeapon
	 */
	void setCurrentWeapon( Weapon* newWeapon );

	/**
	 * Gets Entity's current weapon
	 * 
	 * @return	  Weapon*	Current weapon
	 */
	Weapon* getCurrentWeapon() const;

	/**
	 * Calls current weapon update
	 */
	void update();

	/**
	 * Add shots from the weapon to the scene's correct shot list
	 * 
	 * @param[in]  shots	Vector of shots to be added to the scene
	 */
	virtual void addShots( std::vector<Shot*> shots ) = 0;

protected:

private:
	Weapon* _currentWeapon;
};
