/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   12:31
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\PlayerModelImpl.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	PlayerModelImpl
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef PlayerModelImpl_h__
#define PlayerModelImpl_h__

#include "AIManager/PlayerModel.h"

class PlayerModelImpl : public PlayerModel
{
public:

	enum PlayerTraits
	{
		ACCURACY,
		ENEMIES_WASTED_WAVE,
		ENEMIES_WASTED_TOTAL,
		LIVES_VARIATION,
		TRAITS_SIZE
	};

	PlayerModelImpl(float learningrate = 0.0f);

	virtual ~PlayerModelImpl();

	virtual float compare( PlayerModel* comparable );
	
private:
};

#endif // PlayerModelImpl_h__
