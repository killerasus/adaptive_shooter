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



float PlayerModelImpl::compare( PlayerModel* comparable )
{
	float traitValue;
	float total = 0.0f;
	float totalCompareMin = 0.0f;
	float totalCompareMax = 0.0f;

	for (int i = 0; i < PlayerModelImpl::TRAITS_SIZE; i++)
	{
		total += getTraitValue( i );
		totalCompareMin += comparable->getTraitMinimum( i );
		totalCompareMax += comparable->getTraitMaximum( i );
	}

	// Checks if model is under the comparable
	if (total < totalCompareMin)
	{
		return -1.0f;
	} 
	else
	{
		// Checks if model is above comparable
		if (total > totalCompareMax)
		{
			return 1.0f;
		} 
		else
		{
			return 0.0f;
		}
	}
}
