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

PlayerModel::PlayerModel( unsigned int numberOfTraits, float learningRate ):_traits( numberOfTraits ), _learningRate( learningRate )
{

}



PlayerModel::~PlayerModel()
{

}



void PlayerModel::resetTraits()
{
	for (unsigned int i = 0; i < _traits.size(); i++)
	{
		_traits[i]._currentValue = 0.5f;
	}
}



std::string PlayerModel::getName() const
{
	return _name;
}



void PlayerModel::setName( std::string name )
{
	_name = name;
}



void PlayerModel::updateTrait( unsigned int trait, float observedValue )
{
	float currentValue = _traits[trait]._currentValue;
	float delta = observedValue - currentValue;
	float weightedDelta = _learningRate * delta;

	_traits[trait]._currentValue += weightedDelta;

	if(_traits[trait]._currentValue > 1.0f)
	{
		_traits[trait]._currentValue = 1.0f;
	}
}




Trait PlayerModel::getTrait( unsigned int trait ) const
{
	return _traits[trait];
}



float PlayerModel::getTraitValue( unsigned int trait ) const
{
	return _traits[trait]._currentValue;
}



float PlayerModel::getTraitMinimum( unsigned int trait ) const
{
	return _traits[trait]._minValue;
}



float PlayerModel::getTraitMaximum( unsigned int trait ) const
{
	return _traits[trait]._maxValue;
}



float PlayerModel::getTraitWeight( unsigned int trait ) const
{
	return _traits[trait]._weight;
}



void PlayerModel::setTrait( unsigned int trait, float minimum, float maximum, float weight, float value )
{
	setTraitValue( trait, value );
	setTraitMinimum( trait, minimum );
	setTraitMaximum( trait, maximum );
	setTraitWeight( trait, weight );
}



void PlayerModel::setTraitValue( unsigned int trait, float value )
{
	// Trimming the value to range.
	if (value >= 0.0f && value <= 1.0f)
	{
		_traits[trait]._currentValue = value;
	}
	else
	{
		if (value > 1.0f)
		{
			_traits[trait]._currentValue = 1.0f;
		}
		else
		{
			_traits[trait]._currentValue = 0.0f;
		}
	}
}



void PlayerModel::setTraitMinimum( unsigned int trait, float value )
{
	_traits[trait]._minValue = value;
}



void PlayerModel::setTraitMaximum( unsigned int trait, float value )
{
	_traits[trait]._maxValue = value;
}



void PlayerModel::setTraitWeight( unsigned int trait, float value )
{
	_traits[trait]._weight = value;
}



const unsigned int PlayerModel::getNumberOfTraits() const
{
	return _traits.size();
}



void PlayerModel::setLearningRate( float rate )
{
	_learningRate = rate;
}



float PlayerModel::getLearningRate() const
{
	return _learningRate;
}
