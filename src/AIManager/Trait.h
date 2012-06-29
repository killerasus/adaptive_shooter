/********************************************************************
	created:	2012/06/29
	created:	29:6:2012   4:12
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager\Trait.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AIManager
	file base:	Trait
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef Trait_h__
#define Trait_h__

/** 
 * Trait struct represents a trait with diffent interpretations:
 * In an observed player model, just _currentValue has a meaning
 * In a reference player model, _minValue and _maxValue represent minimal and
 * maximal values of the trait for that player model
 *
 * Ex:
 * In a reference model for Easy player, the trait accuracy could have a min of 0 and a max of 0.33
 * In an observed model for a player, min and max doesn't have any meaning, but _currentValue represents
 * the current observed value for that trait.
 */
struct Trait
{
	/**
	 * Constructor
	 * 
	 * @param	  current	Trait current / starting value
	 * @param	  minimal	Trait minimum value
	 * @param	  maximal	Trait maximum value
	 * @param	  weight	Trait weight
	 */
	Trait(float current = 0.0f, float minimal = 0.0f, float maximal = 0.0f, float weight = 1.0f)
		: _minValue(minimal), _maxValue(maximal), _currentValue(current), _weight(weight)
	{

	}

	float _minValue; // Minimum value for the associated player model
	float _maxValue; // Maximum value for the associated player model
	float _currentValue; // Current value in current player model
	float _weight; // Weight for player model comparison
};

#endif // Trait_h__