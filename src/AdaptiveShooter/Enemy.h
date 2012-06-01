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

#include "Entity.h"
#include "AIManager/AIAgent.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Enemy : public AIAgent, Entity
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void draw();

	virtual void update();

	virtual void setAlpha( float alpha );

	virtual void updateStats();

protected:
	
private:

};
#endif