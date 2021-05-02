/********************************************************************
	created:	2012/07/02
	created:	2:7:2012   14:53
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter\ControllerInterface.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\Jogo\src\AdaptiveShooter
	file base:	ControllerInterface
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/
#pragma once

class ControllerInterface {
public:

	ControllerInterface(){};

	virtual ~ControllerInterface(){};

	/**
	 * Checks if Up is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerUp() = 0;

	/**
	 * Checks if Down is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerDown() = 0;

	/**
	 * Checks if Left is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerLeft() = 0;

	/**
	 * Checks if Right is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerRight() = 0;

	/**
	 * Checks if Fire is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerFire() = 0;

	/**
	 * Checks if Bomb is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerBomb() = 0;

	/**
	 * Checks if Back is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerBack() = 0;

	/**
	 * Checks if Start is pressed
	 *
	 * @return bool	True if key is pressed
	 */
	virtual bool isControllerStart() = 0;
};
