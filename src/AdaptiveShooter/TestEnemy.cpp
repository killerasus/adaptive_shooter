/********************************************************************
	created:	2012/06/15
	created:	15:6:2012   17:33
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\TestEnemy.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestEnemy
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "TestEnemy.h"
#include "GameManager.h"
#include "PlayerModelImpl.h"

TestEnemy::TestEnemy() : Enemy()
{

}



TestEnemy::TestEnemy(float x, float y, float speedX, float speedY, std::string resource) : Enemy ( x, y, speedX, speedY )
{

}



TestEnemy::TestEnemy(CL_Vec2f& position, CL_Vec2f& speed, std::string resource)
{

}



TestEnemy::~TestEnemy()
{

}



void TestEnemy::draw()
{

}



void TestEnemy::update()
{
	float dt = GameManager::getInstance()->getDeltaTime();
	setPositionX( getPosition().x + getSpeed().x * _multiplier * dt * 0.001f );
	CL_Vec2f position = getPosition();

	CL_Size windowSize = GameManager::getInstance()->getWindow()->get_gc().get_size();
	CL_Size spriteSize = getCurrentSprite()->get_size();

	//Checks if sprite is trying to get outside window view to the right
	if (position.x + spriteSize.width > windowSize.width)
	{
		setPositionX( (float)(windowSize.width - spriteSize.width) );
		CL_Vec2f speed = getSpeed();
		setSpeed( -(speed.x), speed.y ); //Changing movement direction
	}
	else
	{
		//Checks if sprite is trying to get outside window view to the left
		if (position.x < 0.0f)
		{
			setPositionX( 0.0f );
			CL_Vec2f speed = getSpeed();
			setSpeed( -(speed.x), speed.y ); //Changing movement direction
		}
	}
}



void TestEnemy::updateStats()
{
	PlayerModel* current = GameManager::getInstance()->getAIManager()->getCurrentPlayerModel();
	std::string perceptedDifficulty = current->getName();

	if (perceptedDifficulty == "Easy")
	{
		//TODO: Change stats (multiplier)
	} 
	else
	{
		if (perceptedDifficulty == "Normal")
		{
			//TODO: Change stats (multiplier)
		}
		else
		{
			if (perceptedDifficulty == "Hard")
			{
				//TODO: Change stats (multiplier)
			} 
			else
			{
				//TODO: Log error. Unknown difficulty
			}
		}
	}
}
