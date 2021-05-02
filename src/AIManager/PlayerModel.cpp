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
#include <assert.h>

PlayerModel::PlayerModel( unsigned int numberOfTraits, float learningRate ):_traits( numberOfTraits ), _learningRate( learningRate )
{}

PlayerModel::~PlayerModel()
{}

void PlayerModel::resetTraits()
{
	for (unsigned int i = 0; i < _traits.size(); i++)
		_traits[i]._currentValue = 0.5f;
}

std::string PlayerModel::getName() const
{ return _name; }

void PlayerModel::setName( std::string name )
{ _name = name; }

void PlayerModel::updateTrait( unsigned int trait, float observedValue )
{
	float currentValue = _traits[trait]._currentValue;
	float delta = observedValue - currentValue;
	float weightedDelta = _learningRate * delta;

	setTraitValue( trait, _traits[trait]._currentValue + weightedDelta );
}

Trait PlayerModel::getTrait( unsigned int trait ) const
{ return _traits[trait]; }

float PlayerModel::getTraitValue( unsigned int trait ) const
{ return _traits[trait]._currentValue; }

float PlayerModel::getTraitMinimum( unsigned int trait ) const
{ return _traits[trait]._minValue; }

float PlayerModel::getTraitMaximum( unsigned int trait ) const
{ return _traits[trait]._maxValue; }

float PlayerModel::getTraitWeight( unsigned int trait ) const
{ return _traits[trait]._weight; }

void PlayerModel::setTrait( unsigned int trait, float minimum, float maximum, float weight, float newValue )
{
	setTraitValue( trait, newValue );
	setTraitMinimum( trait, minimum );
	setTraitMaximum( trait, maximum );
	setTraitWeight( trait, weight );
}

void PlayerModel::setTraitValue( unsigned int trait, float newValue )
{
	// Trimming the value to range.
	if (newValue >= 0.0f && newValue <= 1.0f)
		_traits[trait]._currentValue = newValue;
	else
	{
		if (newValue > 1.0f)
			_traits[trait]._currentValue = 1.0f;
		else
			_traits[trait]._currentValue = 0.0f;
	}
}

void PlayerModel::setTraitMinimum( unsigned int trait, float newValue )
{ _traits[trait]._minValue = newValue; }

void PlayerModel::setTraitMaximum( unsigned int trait, float newValue )
{ _traits[trait]._maxValue = newValue; }

void PlayerModel::setTraitWeight( unsigned int trait, float newWeight )
{ _traits[trait]._weight = newWeight; }

const unsigned int PlayerModel::getNumberOfTraits() const
{ return _traits.size(); }

void PlayerModel::setLearningRate( float rate )
{ _learningRate = rate; }

float PlayerModel::getLearningRate() const
{ return _learningRate; }

void PlayerModel::setTraitsToReferenceAverage( PlayerModel* referenced )
{
	for (unsigned int i = 0; i < referenced->getNumberOfTraits(); i++)
	{
		float average = 0.5f * ( referenced->getTraitMaximum( i ) + referenced->getTraitMinimum( i ) );
		setTraitValue( i , average );
	}
}
