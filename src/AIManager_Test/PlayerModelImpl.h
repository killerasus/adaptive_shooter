/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   16:29
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test\testPlayerModel.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager_Test
	file base:	testPlayerModel
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Test implementation of PlayerModel abstract class
*********************************************************************/
#ifndef PLAYERMODELIMPL_H
#define PLAYERMODELIMPL_H

#include "playermodel.h"

class PlayerModelImpl : public PlayerModel
{
public:
	PlayerModelImpl();
	PlayerModelImpl(float valor);
	~PlayerModelImpl();

	virtual float compare( PlayerModel* comparable );
protected:
	
private:
	float _valor;
};

#endif
