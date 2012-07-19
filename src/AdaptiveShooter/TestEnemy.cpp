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

#include "logog.hpp"

TestEnemy::TestEnemy() : Enemy(), _multiplier(1.0f)
{

}



TestEnemy::TestEnemy(float x, float y, float speedX, float speedY, std::string resource) : Enemy ( x, y, speedX, speedY ), _multiplier(1.0f)
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );

	CL_String descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/enemies/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline(collisionResource.c_str(), manager->getResourceManager()) );
	}
}



TestEnemy::TestEnemy(CL_Vec2f& position, CL_Vec2f& speed, std::string resource) : Enemy(position, speed), _multiplier(1.0f)
{
	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, resource, manager->getResourceManager() );

	CL_String descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/enemies/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline(collisionResource.c_str(), manager->getResourceManager()) );
	}
}



TestEnemy::~TestEnemy()
{
	delete _currentSprite;
#ifdef _DEBUG
	CL_Console::write_line("Enemy deleted");
#endif
}

#ifdef _DEBUG
void TestEnemy::draw()
{
	this->DynamicEntity::draw();
	int frame = getCurrentSprite()->get_current_frame();
	_currentOutlines[frame]->draw( getPosition().x, getPosition().y, CL_Colorf::red,
		GameManager::getInstance()->getWindow()->get_gc() );
}
#endif


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
		_multiplier = 0.5f;
	} 
	else
	{
		if (perceptedDifficulty == "Normal")
		{
			_multiplier = 1.0f;
		}
		else
		{
			if (perceptedDifficulty == "Hard")
			{
				_multiplier = 1.5f;
			} 
			else
			{
				LOGOG_ERROR( "\nUnknown difficulty: %s\n", perceptedDifficulty );
			}
		}
	}
}
