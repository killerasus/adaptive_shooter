/********************************************************************
	created:	2012/06/15
	created:	15:6:2012   17:31
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\TestEnemy.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestEnemy
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/
#pragma once

#include "Enemy.h"
#include "Shooter.h"

class TestEnemy : public Enemy, public Shooter
{
public:
	TestEnemy();

	TestEnemy(float x, float y, float speedX, float speedY, std::string resource);

	TestEnemy(clan::Vec2f& position, clan::Vec2f& speed, std::string resource);

	virtual ~TestEnemy();

#ifdef _DEBUG
	virtual void draw();
#endif // _DEBUG

	virtual void update();

	virtual void updateStats();

	virtual void addShots( std::vector<Shot*> shots );

protected:
	
private:

	Weapon* _weapon;

	void correctHorizontalMovement();
};
