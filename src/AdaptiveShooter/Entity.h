/********************************************************************
	created:	2011/12/06
	created:	6:12:2011   16:56
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\Entity.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	Entity
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Interface for Entity types
*********************************************************************/
#ifndef Entity_h__
#define Entity_h__

#include "ClanLib/core.h"
#include "ClanLib/display.h"

class Entity
{
public:

	enum CollisionDirection{
		CD_NOCOLLISION = 0,
		CD_LEFT = 1,
		CD_RIGHT = 2,
		CD_TOP = 4,
		CD_BOTTOM = 8
	};

	/**
	 * Constructor
	 */
	Entity();

	/**
	 * Constructor
	 * 
	 * @param	  position	Position vector
	 */
	Entity(clan::Vec2f& position);

	/**
	 * Constructor
	 * 
	 * @param	  x	Position in the x axis
	 * @param	  y	Position in the y axis
	 */
	Entity(float x, float y);

	virtual ~Entity();

	/**
	 * Gets the position of the Entity
	 *
	 * @return	  CL_Vec2f	Position
	 */
	clan::Vec2f getPosition() const;

	/**
	 * Sets the entity position
	 * 
	 * @param	  position	New position
	 */
	void setPosition(clan::Vec2f& position);

	/**
	 * Sets the entity position
	 *
	 * @param	  x	New x axis position
	 * @param	  y	New y axis position
	 */
	void setPosition(float x, float y);

	/**
	 * Sets x axis position
	 *
	 * @param	  x
	 */
	void setPositionX(float x);

	/**
	 * Sets y axis position
	 *
	 * @param	  y
	 */
	void setPositionY(float y);

	/**
	 * Gets current sprite in use 
	 *
	 * @return	  CL_Sprite*
	 */
	clan::Sprite& getCurrentSprite() const;

	/**
	 * Gets the alpha value of the current sprite.
	 *
	 * @return	  float	Alpha value of the current sprite, -1 if no current sprite set
	 */
	float getAlpha() const;

	/**
	 * Sets the alpha value of the current sprite
	 *
	 * @param	  alpha	New alpha value in the range [0.0, 1.0]
	 */
	void setAlpha(float alpha);

	/**
	 * Draws the current sprite to the screen
	 */
	virtual void draw() = 0;

	/**
	 * Updates the entity
	 */
	virtual void update() = 0;

	/**
	 * Checks if current sprite is still visible in screen boundaries
	 * 
	 * @return	  bool	true if inside graphics context window, false otherwise
	 */
	bool checkWindowBoundary();
	
	/**
	 * Bounds the entity to screen, canceling movement that would otherwise make the entity
	 * outside of screen boundaries
	 *
	 * @return	unsigned int	Directions where a collision has occurred. Check CollisionDirection for values.
	 */
	unsigned int boundToScreen();

protected:
	clan::Sprite _currentSprite;
private:
	clan::Vec2f _position;
};

#endif // Entity_h__
