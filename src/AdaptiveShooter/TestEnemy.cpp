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
#include "TestScenePlayer.h"

#include <sstream>
#include <cmath>

TestEnemy::TestEnemy() : Enemy(), _weapon( new Weapon( "Standard laser", "sprites/roundShotMedium", GameManager::getInstance()->getEnemyOptions()->shotDelay ) )
{
	_weapon->setShotSpeed( 0.0f, GameManager::getInstance()->getEnemyOptions()->shotSpeedY );
	setCurrentWeapon( _weapon );
}

TestEnemy::TestEnemy(float x, float y, float speedX, float speedY, std::string resource) : Enemy ( x, y, speedX, speedY ),
	_weapon( new Weapon( "Standard laser", "sprites/roundShotMedium", GameManager::getInstance()->getEnemyOptions()->shotDelay ) )
{
	_weapon->setShotSpeed( 0.0f, GameManager::getInstance()->getEnemyOptions()->shotSpeedY );
	setCurrentWeapon( _weapon );

	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();
	_currentSprite = clan::Sprite::resource( gc, resource, manager->getResourceManager() );

	std::string descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite.get_frame_count(); i++)
	{
		std::string collisionResource = clan::string_format( "outlines/enemies/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( clan::CollisionOutline::load(collisionResource.c_str(), manager->getResourceDocument()) );
	}
}

TestEnemy::TestEnemy(clan::Vec2f& position, clan::Vec2f& speed, std::string resource) : Enemy(position, speed),
	_weapon( new Weapon( "Standard laser", "sprites/roundShotMedium", GameManager::getInstance()->getEnemyOptions()->shotDelay ) )
{
	_weapon->setShotSpeed( 0.0f, GameManager::getInstance()->getEnemyOptions()->shotSpeedY );
	setCurrentWeapon( _weapon );

	GameManager* manager = GameManager::getInstance();
	clan::Canvas& gc = manager->getCanvas();
	_currentSprite = clan::Sprite::resource( gc, resource, manager->getResourceManager() );

	std::string descriptor = resource.substr(resource.find_last_of("/") + 1);

	for (int i = 0; i < _currentSprite.get_frame_count(); i++)
	{
		std::string collisionResource = clan::string_format( "outlines/enemies/%1/%2_00%3", descriptor, descriptor, i );
		_currentOutlines.push_back( clan::CollisionOutline::load(collisionResource.c_str(), manager->getResourceDocument()) );
	}
}

TestEnemy::~TestEnemy()
{ delete _weapon; }

#ifdef _DEBUG
void TestEnemy::draw()
{
	this->DynamicEntity::draw();
	int frame = getCurrentSprite().get_current_frame();
	_currentOutlines[frame].draw( getPosition().x, getPosition().y, clan::Colorf::red,
		GameManager::getInstance()->getCanvas() );
}
#endif

void TestEnemy::update()
{
	Shooter::update();

	int dt = GameManager::getInstance()->getDeltaTime();

	if((_behavior & GOHORIZONTAL) == GOHORIZONTAL)
	{
		float before = getPosition().x;
		setPositionX( getPosition().x + getSpeed().x * _multiplier * dt * 0.001f );
		float after = getPosition().x;

		_currentAmplitude +=  fabs(after - before);

		correctHorizontalMovement();

		// Checks Sinusoid movement
		if ((_behavior & GOSINUSOID) == GOSINUSOID)
		{
			if (_currentAmplitude >= _amplitudeLimit)
			{
				clan::Vec2f speed = getSpeed();
				setSpeed( -(speed.x), speed.y ); //Changing movement direction
				_currentAmplitude = 0.0f;
			}
		}
	}

	if((_behavior & GODOWN) == GODOWN)
		setPositionY( getPosition().y + getSpeed().y * _multiplier * dt * 0.001f );

	if ((_behavior & SHOOT) == SHOOT)
	{
		if (checkWindowBoundary())
		{
			Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
			float center = getPosition().x + getCurrentSprite().get_width()*0.5f;
			float halfRange = 200.0f/_multiplier;

			if (playerOne->getPosition().x >= center - halfRange &&
				playerOne->getPosition().x + playerOne->getCurrentSprite().get_width() <= center + halfRange &&
				playerOne->getPosition().y >= getPosition().y)
				addShots( _weapon->shoot( this ) );
		}
	}
}

void TestEnemy::updateStats()
{
	PlayerModel* current = GameManager::getInstance()->getAIManager()->getCurrentPlayerModel();
	std::string perceptedDifficulty = current->getName();

	if (perceptedDifficulty == "Easy")
	{
		_multiplier = GameManager::getInstance()->getEnemyOptions()->easyMultiplier;
		_weapon->setDelay( _weapon->getDelay()/_multiplier );
	} 
	else
	{
		if (perceptedDifficulty == "Normal")
		{
			_multiplier = GameManager::getInstance()->getEnemyOptions()->normalMultiplier;
			_weapon->setDelay( _weapon->getDelay()/_multiplier );
		}
		else
		{
			if (perceptedDifficulty == "Hard")
			{
				_multiplier = GameManager::getInstance()->getEnemyOptions()->hardMultiplier;
				_weapon->setDelay( _weapon->getDelay()/_multiplier );
			} 
			else
			{
				std::ostringstream text;
				text << clan::DateTime().get_current_local_time().to_long_time_string().c_str();
				text <<"\nUnknown difficulty: ";
				text << perceptedDifficulty;
				text << "\n";
				GameManager::getInstance()->getLogger()->log("Error", text.str());
			}
		}
	}
}

void TestEnemy::addShots( std::vector<Shot*> shots )
{
	TestScenePlayer *currentScene = dynamic_cast<TestScenePlayer*>( GameManager::getInstance()->peekScene() );

	for (std::vector<Shot*>::iterator it = shots.begin(); it != shots.end(); it++)
		currentScene->addEnemyShot( (*it) );

	if (shots.size() > 0)
		GameManager::getInstance()->playSoundEffect(GameManager::SFX_LASER_1);
}

void TestEnemy::correctHorizontalMovement()
{
	clan::Vec2f position = getPosition();

	clan::Size windowSize = GameManager::getInstance()->getWindow()->get_gc().get_size();
	clan::Size spriteSize = getCurrentSprite().get_size();

	//Checks if sprite is trying to get outside window view to the right
	if (position.x + spriteSize.width > windowSize.width)
	{
		setPositionX( (float)(windowSize.width - spriteSize.width) );
		clan::Vec2f speed = getSpeed();
		setSpeed( -(speed.x), speed.y ); //Changing movement direction
		_currentAmplitude = 0.0f;
	}
	else
	{
		//Checks if sprite is trying to get outside window view to the left
		if (position.x < 0.0f)
		{
			setPositionX( 0.0f );
			clan::Vec2f speed = getSpeed();
			setSpeed( -(speed.x), speed.y ); //Changing movement direction
			_currentAmplitude = 0.0f;
		}
	}
}
