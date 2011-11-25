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

float PlayerModelImpl::Compare( PlayerModel* comparable )
{
	if (comparable)
	{
		return this->_valor - ((PlayerModelImpl*)comparable)->_valor;
	} 
	else
	{
		return this->_valor;
	}
}

PlayerModelImpl::PlayerModelImpl(float valor)
{
	_valor = valor;
}
