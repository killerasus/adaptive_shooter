/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   16:39
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test\PlayerModelImpl.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test
	file base:	PlayerModelImpl
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "PlayerModelImpl.h"

//PlayerModelImpl::PlayerModelImpl()
//{
//
//}

PlayerModelImpl::PlayerModelImpl(float valor, float learningRate) : PlayerModel( TOTAL_STATS, learningRate )
{
	setTraitValue(SHOOTING_RATE, valor);
}

PlayerModelImpl::~PlayerModelImpl()
{

}

float PlayerModelImpl::compare( PlayerModel* comparable )
{
	if (comparable)
	{
		return this->getTraitValue(SHOOTING_RATE) - ((PlayerModelImpl*)comparable)->getTraitValue(SHOOTING_RATE);
	} 
	else
	{
		return this->getTraitValue(SHOOTING_RATE);
	}
}
