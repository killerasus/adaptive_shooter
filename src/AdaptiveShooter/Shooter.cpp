/********************************************************************
	created:	2012/07/23
	created:	23:7:2012   14:44
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Shooter.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Shooter
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Shooter.h"

Shooter::Shooter() : _currentWeapon( NULL )
{}

Shooter::Shooter( Weapon* weapon ) : _currentWeapon( weapon )
{}

Shooter::~Shooter()
{}

void Shooter::setCurrentWeapon( Weapon* newWeapon )
{ _currentWeapon = newWeapon; }

Weapon* Shooter::getCurrentWeapon() const
{ return _currentWeapon; }

void Shooter::update()
{
	if (_currentWeapon)
		_currentWeapon->update();
}
