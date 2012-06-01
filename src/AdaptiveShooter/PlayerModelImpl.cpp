/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   12:32
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\PlayerModelImpl.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	PlayerModelImpl
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "PlayerModelImpl.h"

PlayerModelImpl::PlayerModelImpl( float learningRate ) : PlayerModel(TRAITS_SIZE, learningRate)
{
	resetTraits();
}



PlayerModelImpl::~PlayerModelImpl()
{

}



/** @TODO: Implementar */
float PlayerModelImpl::compare( PlayerModel* comparable )
{
	return 0.0f;
}
