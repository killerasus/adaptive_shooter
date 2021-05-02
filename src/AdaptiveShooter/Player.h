/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   3:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Player.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Player
	file ext:	h
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/
#pragma once

#include "AIManager/PlayerModel.h"
#include "DynamicEntity.h"
#include "Shooter.h"
#include "ControllerInterface.h"

class Player : public DynamicEntity, public Shooter
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
	 *	Gets current player's model
	 * 
	 * @return	  PlayerModel*
	 */
	PlayerModel* getPlayerModel() const;

	/**
	 * Sets player's score
	 * 
	 * @param[in]	score	New value
	 */
	void setScore( int score);

	/**
	 * Gets player's score
	 * 
	 * @return	int	Player's score
	 */
	int getScore() const;

	/**
	 * Add points to player's score
	 * 
	 * @param[in]	value	Points to add
	 */
	void addToScore( int value );

	virtual void addShots( std::vector<Shot*> shots );

	/**
	 * Gets invincibility
	 * 
	 * @return	bool	True if invincible, false otherwise
	 */
	bool getInvincible();

	/**
	 * Enable or disable invincibility
	 * 
	 * @param[in]	status
	 */
	void setInvincible( bool status );

protected:
private:
	unsigned int _playerNumber;
	unsigned int _lives;
	int _score;
	PlayerModel* _model;
	std::string _spriteResourceKey;
	Weapon* _weapon;
	ControllerInterface* _controller;
	bool _invincible;
	int _invincibilityTimerBase;
	int _invincibilityTimer;
	float _alphaFlash;

	/**
	 * Updates invincibility timer
	 * 
	 * @param[in]	dt	Time delta since last update
	 */
	void updateInvincibility( int dt );
};
