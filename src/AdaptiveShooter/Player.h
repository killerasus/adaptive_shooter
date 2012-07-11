/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   3:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Player.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Player
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef Player_h__
#define Player_h__

#include "AIManager/PlayerModel.h"
#include "DynamicEntity.h"

class Player : public DynamicEntity
{
public:

	/**
	 * Constructor
	 * 
	 * @param[in]	  x			Starting x position
	 * @param[in]	  y			Starting y position
	 * @param[in]	  speedX	Starting x speed
	 * @param[in]	  speedY	Starting y speed
	 * @param[in]	  number	Player number, from 0 to max_players - 1
	 * @param[in]	  sprite	Sprite path in resource file
	 * @param[in]	  model		Implementation of PlayerModel interface, Player takes care of deleting
	 * @param[in]	  lives		Number of starting lives, defaulted to 2
	 */
	Player( float x, float y, float speedX, float speedY, unsigned int number, std::string sprite, PlayerModel* model, 
		unsigned int lives = 2);

	/**
	 * Destructor
	 */
	virtual ~Player();

#ifdef _DEBUG
	virtual void draw();
#endif

	virtual void update();

	/**
	 * Gets Player number (0 to max_players - 1)
	 * 
	 * @return	  unsigned int
	 */
	unsigned int getPlayerNumber() const;

	/**
	 * Sets Player number (0 to max_players - 1)
	 * 
	 * @param	  val
	 */
	void setPlayerNumber(unsigned int val);

	/**
	 * Gets Player's lives
	 * 
	 * @return	  unsigned int
	 */
	unsigned int getLives() const;

	/**
	 * Sets Players lives
	 * 
	 * @param	  val
	 */
	void setLives(unsigned int val);

	/**
	 * Add val lives to player lives pool
	 * 
	 * @param	  val	Number of lives to add
	 */
	void addLives(unsigned int val);

	/**
	 * Subtracts val lives from lives pool
	 * 
	 * @param	  val	Number of lives to subtract
	 */
	void subtractLives(unsigned int val);

	/**
	 *	Gets current player model
	 * 
	 * @return	  PlayerModel*
	 */
	PlayerModel* getPlayerModel() const;

protected:
private:
	unsigned int _playerNumber;
	unsigned int _lives;
	std::vector<CL_CollisionOutline*> _currentOutlines;
	PlayerModel* _model;
	std::string _spriteResourceKey;
	float _shotTimer; // This must go to a weapon class
};

#endif // Player_h__
