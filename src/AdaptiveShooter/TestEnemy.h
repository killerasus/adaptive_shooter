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
#ifndef TestEnemy_h__
#define TestEnemy_h__

#include "Enemy.h"

class TestEnemy : public Enemy
{
public:
	TestEnemy();

	TestEnemy(float x, float y, float speedX, float speedY, std::string resource);

	TestEnemy(CL_Vec2f& position, CL_Vec2f& speed, std::string resource);

	~TestEnemy();

	virtual void draw();

	virtual void update();

	virtual void updateStats();

protected:
	
private:
	float _multiplier; //Speed multiplier
};

#endif // TestEnemy_h__
