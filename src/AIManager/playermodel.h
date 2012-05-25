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

class PlayerModel
{
public:
	
	/** Constructor */
	PlayerModel();

	/** Destructor */
	~PlayerModel();

	/** Initializes the model with trait values equal to 0.5, representing lack of knowledge */
	void initialize();

	/**
	 * Returns the name of the player model
	 * 
	 * @return	  std::string
	 */
	std::string getName();

	/**
	 * Sets the name of the player model
	 * 
	 * @param	  name	New name
	 */
	void setName( std::string name );

	/**
	 * Updates the trait with the given value using LMS
	 * 
	 * @param	  trait			Position of the trait in the _traitValues
	 * @param	  observedValue Value observed of the trait
	 */
	void updateTrait( unsigned int trait, float observedValue );

	/**
	 * Gets the trait value
	 * 
	 * @param	  trait	The trait position from the collection
	 * @return	  float	Trait value in range [0..1] if trait is [0.._traitValues.size())
	 */
	float getTrait( unsigned int trait );

	/**
	 * Sets trait with new value
	 * 
	 * @param	  trait	The trait position from the collection
	 * @param	  value	New trait value
	 */
	void setTrait( unsigned int trait, float value );

	/**
	 * Sets new learning rate for the player model
	 * 
	 * @param	  rate	Value in the range (0..1]
	 */
	void setLearningRate( float rate );

	/**
	 * Compares the current model to a reference model.
	 * 
	 * @param	  comparable	The player model to compare to
	 * @return	  float			0 if the models match, < 0 if current model is under the comparable, > 1 if current model is above
	 */
	virtual float compare(PlayerModel* comparable) = 0;
protected:

private:
	std::vector<float> _traitValues;
	std::string _name;
	static float _learningRate;
};

#endif // PlayerModel_h__
