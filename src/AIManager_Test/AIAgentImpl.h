/********************************************************************
	created:	2012/05/24
	created:	24:5:2012   14:46
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager_Test\AIAgentImpl.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager_Test
	file base:	AIAgentImpl
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#pragma once

#include "AIManager/AIAgent.h"
#include "AIManager/PlayerModel.h"

class AIAgentImpl : public AIAgent
{
public:
	AIAgentImpl( PlayerModel* player );
	virtual ~AIAgentImpl();

	virtual void updateStats();

	float getShootingRate();

protected:
	
private:
	PlayerModel* _playerModel;
	float _shootingRate;
	float _xSpeed;
	float _ySpeed;
};
