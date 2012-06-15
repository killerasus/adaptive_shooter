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
	~TestEnemy();

	virtual void draw();

	virtual void update();

	virtual void updateStats();

protected:
	
private:
};

#endif // TestEnemy_h__
