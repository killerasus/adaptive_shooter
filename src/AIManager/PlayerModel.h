/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   13:40
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager\playermodel.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\Jogo\src\AIManager
	file base:	playermodel
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Interface class for player model used in AIManager framework
*********************************************************************/

#ifndef PlayerModel_h__
#define PlayerModel_h__

#include <string>
#include <vector>

#include "Trait.h"

class PlayerModel
{
public:
	
	/**
	 * Constructor
	 * 
	 * @param[in]	numberOfTraits	Number of traits to be observed, initialized to 0.5f
	 * @param[in]	learningRate	Learning rate for the traits
	 */
	PlayerModel( unsigned int numberOfTraits, float learningRate );

	/** Destructor */
	virtual ~PlayerModel();

	/*
	 * Resets the model with trait values equal to 0.5, representing lack of knowledge
	 * (trait may or may not be present)
	 */
	void resetTraits();

	/**
	 * Returns the name of the player model
	 * 
	 * @return	  std::string
	 */
	std::string getName() const;

	/**
	 * Sets the name of the player model
	 * 
	 * @param	  name	New name
	 */
	void setName( std::string name );

	/**
	 * Updates the trait with the given value using LMS
	 * 
	 * @param	  trait			Position of the trait in the collection
	 * @param	  observedValue Value observed of the trait
	 */
	void updateTrait( unsigned int trait, float observedValue );

	/**
	 * Gets a copy of the trait
	 * 
	 * @param	  trait	Position of the trait in the collection
	 * @return	  Trait	Copy of the trait
	 */
	Trait getTrait( unsigned int trait ) const;

	/**
	 * Gets the trait value
	 * 
	 * @param	  trait	The trait position from the collection
	 * @return	  float	Trait value in range [0..1] if trait is [0.._traitValues.size())
	 */
	float getTraitValue( unsigned int trait ) const;

	/**
	 * Gets the trait minimum value
	 * 
	 * @param[in]	trait The trait position in the collection
	 * @return		float Trait minimum value in range [0..1] if trait is [0.._traitValues.size())
	 */
	float getTraitMinimum( unsigned int trait ) const;

	/**
	 * Gets the trait maximum value
	 * 
	 * @param[in] trait The trait position in the collection
	 * @return	  float Trait maximum value in range [0..1] if trait is [0.._traitValues.size())
	 */
	float getTraitMaximum( unsigned int trait ) const;

	/**
	 * Gets trait weight
	 * 
	 * @param	  trait	The trait position in the collection
	 * @return	  float	Weight value
	 */
	float getTraitWeight( unsigned int trait ) const;

	/**
	 * Sets trait with values
	 * 
	 * @param	  trait		The trait position in the collection
	 * @param	  minimum	Minimum value
	 * @param	  maximum	Maximum value
	 * @param	  weight	Weight value
	 * @param	  value		Current value
	 */
	void setTrait(unsigned int trait, float minimum, float maximum, float weight, float value);

	/**
	 * Sets trait with new value
	 * 
	 * @param[in] trait	The trait position in the collection
	 * @param[in] value	New trait value
	 */
	void setTraitValue( unsigned int trait, float value );

	/**
	 * Sets trait minimum with new value
	 * 
	 * @param[in] trait	The trait position in the collection
	 * @param[in] value	New trait minimum value
	 */
	void setTraitMinimum( unsigned int trait, float value );

	/**
	 * Sets trait maximum with new value
	 * 
	 * @param[in] trait	The trait position in the collection
	 * @param[in] value	New trait maximum value
	 */
	void setTraitMaximum( unsigned int trait, float value );

	/**
	 * Sets trait weight
	 * 
	 * @param	  trait	The trait position in the collection
	 * @param	  value	New trait weight value
	 */
	void setTraitWeight( unsigned int trait, float value );

	/**
	 * Gets the number of traits observed
	 * 
	 * @return	  const unsigned int
	 */
	const unsigned int getNumberOfTraits( ) const;

	/**
	 * Gets the learning rate
	 * 
	 * @return	  float
	 */
	float getLearningRate( ) const;

	/**
	 * Sets new learning rate for the player model
	 * 
	 * @param	  rate	Value in the range (0..1]
	 */
	void setLearningRate( float rate );

	/**
	 * Compares the current model to a reference model under a tolerance.
	 * 
	 * @param	  comparable	The player model to compare to
	 * @return	  float			0 if the models match, < 0 if current model is under the comparable, > 0 if current model is above
	 */
	virtual float compare( PlayerModel* comparable ) = 0;

	/**
	 * Sets player model traits to the average of the reference
	 * 
	 * @param[in]	referenced	Referenced model
	 */
	void setTraitsToReferenceAverage( PlayerModel* referenced );
protected:

private:
	std::vector<Trait> _traits;
	std::string _name;
	float _learningRate;
};

#endif // PlayerModel_h__
