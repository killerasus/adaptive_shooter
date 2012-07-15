/********************************************************************
	created:	2012/07/15
	created:	15:7:2012   4:03
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Weapon.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Weapon
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Weapon.h"
#include "GameManager.h"
#include "TestScenePlayer.h"
#include "Player.h"
#include "PlayerModelImpl.h"

Weapon::Weapon( std::string name, std::string shotResource, float delay, int damage /*= 50*/, WeaponLevel level /*= WL_LEVEL_0*/ )
	: _canShoot( true ), _damage( damage ), _level( level ), _delay( delay ), _timer ( 0.0f ), _name( name ), _shotResource( shotResource )
{

}



Weapon::~Weapon()
{

}



void Weapon::update()
{
	// Only updates timer if has shooted
	if (!_canShoot)
	{
		float dt = GameManager::getInstance()->getDeltaTime();
		_timer += dt;

		if (_timer >= _delay)
		{
			setCanShoot( true );
		}
	}
}



void Weapon::setCanShoot( bool can )
{
	_canShoot = can;
	_timer = 0.0f;
}



bool Weapon::getCanShoot() const
{
	return _canShoot;
}



void Weapon::setDelay( float delay )
{
	_delay = (delay >= 0.0f? delay : 0.0f);
}



float Weapon::getDelay() const
{
	return _delay;
}



float Weapon::getTimer() const
{
	return _timer;
}


void Weapon::setDamage( int damage )
{
	_damage = (damage > 0? damage : 1);
}



int Weapon::getDamage() const
{
	return _damage;
}



void Weapon::setWeaponLevel( WeaponLevel level )
{
	_level = level;
}



Weapon::WeaponLevel Weapon::getWeaponLevel() const
{
	return _level;
}



int Weapon::shoot()
{
	if (_canShoot)
	{
		TestScenePlayer *currentScene = dynamic_cast<TestScenePlayer*>( GameManager::getInstance()->peekScene() );
		Player* player = GameManager::getInstance()->getPlayer( 0 );

		if (currentScene != NULL)
		{
			Shot* newShot = new Shot(player->getPosition().x + player->getCurrentSprite()->get_width()*0.5f,
				player->getPosition().y, 0.0f, -300.0f, _shotResource, _damage);

			currentScene->addPlayerShot( newShot );

			setCanShoot( false );

			return 1;
		}
	}

	return 0;
}
