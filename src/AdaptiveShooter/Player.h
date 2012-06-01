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
#include "Entity.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Player : public Entity
{
public:

	/**
	 * Constructor
	 * 
	 * @param[in]	  sprite	Sprite path in resource file
	 * @param[in]	  model		Implementation of PlayerModel interface
	 * @param[in]	  x			Starting x position
	 * @param[in]	  y			Starting y position
	 * @param[in]	  speedX	Starting x speed
	 * @param[in]	  speedY	Starting y speed
	 */
	Player(std::string  sprite, PlayerModel* model, float x, float y, float speedX, float speedY);

	/**
	 * Destructor
	 */
	virtual ~Player();

	virtual void draw();

	virtual void update();

	virtual void setAlpha( float alpha );

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

	/**
	 * Gets player position on screen related to left uppermost corner
	 * 
	 * @return	  CL_Vec2f
	 */
	CL_Vec2f getPosition() const;

	/**
	 * Sets player position on screen
	 * 
	 * @param	  pos
	 */
	void setPosition(CL_Vec2f& pos) const;

	/**
	 * Gets player speed vector
	 * 
	 * @return	  CL_Vec2f
	 */
	CL_Vec2f getSpeed() const;

	/**
	 * Sets player speed vector
	 * 
	 * @param	  speed
	 */
	void setSpeed(CL_Vec2f& speed);

protected:
private:
	unsigned int _playerNumber;
	unsigned int _lives;
	CL_Sprite* _currentSprite;
	PlayerModel* _model;
	CL_Vec2f _position;
	CL_Vec2f _speed;
	float _shotTimer; // This must go to a weapon class
};

#endif // Player_h__
