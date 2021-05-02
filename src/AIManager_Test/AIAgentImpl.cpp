/********************************************************************
	created:	2012/05/29
	created:	29:5:2012   15:30
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager_Test\AIAgentImpl.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager_Test
	file base:	AIAgentImpl
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "AIAgentImpl.h"

AIAgentImpl::AIAgentImpl( PlayerModel* player ) :_playerModel(player), _shootingRate(0.5f), _xSpeed(3.0f), _ySpeed(3.0f)
{}

AIAgentImpl::~AIAgentImpl()
{}

void AIAgentImpl::updateStats()
{
	if (_playerModel->getName() == "Normal")
		_shootingRate = 1.0f;
}

float AIAgentImpl::getShootingRate()
{ return _shootingRate; }
