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

Weapon::Weapon( std::string name, std::string shotResource, float delay, int damage /*= 50*/,
	WeaponLevel level /*= WL_LEVEL_0*/, float speedX /* = 0.0f */, float speedY /* = -300.0f */ )
	: _canShoot( true ), _damage( damage ), _level( level ), _delay( delay ), _timer ( 0.0f ), _name( name ),
	_shotResource( shotResource ), _shotSpeed( speedX, speedY )
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



std::vector<Shot*> Weapon::shoot( Entity* entity )
{
	std::vector<Shot*> shots;

	if (_canShoot)
	{
		TestScenePlayer *currentScene = dynamic_cast<TestScenePlayer*>( GameManager::getInstance()->peekScene() );

		if (currentScene != NULL )
		{
			Shot* newShot = new Shot(entity->getPosition().x + entity->getCurrentSprite()->get_width()*0.5f,
				entity->getPosition().y, _shotSpeed.x, _shotSpeed.y, _shotResource, _damage);

			shots.push_back( newShot );

			setCanShoot( false );
		}
	}

	return shots;
}



void Weapon::setName( std::string name )
{
	_name = name;
}



std::string Weapon::getName() const
{
	return _name;
}



void Weapon::setShotSpeed( float x, float y )
{
	_shotSpeed.x = x;
	_shotSpeed.y = y;
}



void Weapon::setShotSpeed( CL_Vec2f& speed )
{
	_shotSpeed = speed;
}




CL_Vec2f Weapon::getShotSpeed() const
{
	return _shotSpeed;
}
