/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   13:33
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager\playermodel.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager
	file base:	playermodel
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Interface class for player model used in AIManager framework
*********************************************************************/
#include "PlayerModel.h"

PlayerModel::PlayerModel( unsigned int numberOfTraits, float learningRate ):_traitValues( numberOfTraits, 0.5f ), _learningRate( learningRate )
{

}



PlayerModel::~PlayerModel()
{

}



void PlayerModel::resetTraits()
{
	for (unsigned int i = 0; i < _traitValues.size(); i++)
	{
		_traitValues[i] = 0.5f;
	}
}



std::string PlayerModel::getName()
{
	return _name;
}



void PlayerModel::setName( std::string name )
{
	_name = name;
}



void PlayerModel::updateTrait( unsigned int trait, float observedValue )
{
	float currentValue = _traitValues[trait];
	float delta = observedValue - currentValue;
	float weightedDelta = _learningRate * delta;

	_traitValues[trait] += weightedDelta;

	if(_traitValues[trait] > 1.0f)
	{
		_traitValues[trait] = 1.0f;
	}
}



float PlayerModel::getTrait( unsigned int trait )
{
	return _traitValues[trait];
}



void PlayerModel::setTrait( unsigned int trait, float value )
{
	// Trimming the value to range.
	if (value >= 0.0f && value <= 1.0f)
	{
		_traitValues[trait] = value;
	}
	else
	{
		if (value > 1.0f)
		{
			_traitValues[trait] = 1.0f;
		}
		else
		{
			_traitValues[trait] = 0.0f;
		}
	}
}



const unsigned int PlayerModel::getNumberOfTraits() const
{
	return _traitValues.size();
}



void PlayerModel::setLearningRate( float rate )
{
	_learningRate = rate;
}



float PlayerModel::getLearningRate() const
{
	return _learningRate;
}
