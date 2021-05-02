/********************************************************************
	created:	2012/06/01
	created:	1:6:2012   5:24
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\TestScenePlayer.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestScenePlayer
	file ext:	cpp
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include <iostream>
#include <sstream>
#include "TestScenePlayer.h"
#include "GameManager.h"
#include "PlayerModelImpl.h"
#include "TestEnemy.h"
#include "Explosion.h"

#define ADAPTIVE 1

extern "C"
{
#include "lua.h"
};

TestScenePlayer::TestScenePlayer() : _shotsWave( 0 ), _shotsWaveOnTarget( 0 ), _shotsTotal( 0 ),
	_shotsTotalOnTarget( 0 ), _livesStartWave( 0 ), _livesEndWave( 0 ), _enemiesWave( 0 ), _enemiesWaveWasted( 0 ),
	_enemiesTotal( 0 ), _enemiesTotalWasted( 0 ), _keyDelayTime ( 1000.0f ), _timer( 0.0f ), _canPressKey( true ), _waveNumber( 0 ), _waveOn(false)
{
	clan::Canvas& gc = GameManager::getInstance()->getCanvas();
	_font = new clan::Font( gc, "Tahoma", 16 );

#ifdef _DEBUG
	loadScene( "../../src/Scripts/demoscene.lua" );
#else
	loadScene( "./Scripts/demoscene.lua" );
#endif
}

TestScenePlayer::~TestScenePlayer()
{ delete _font; }

void TestScenePlayer::draw()
{
	clan::Canvas& gc = GameManager::getInstance()->getCanvas();

	Player* playerOne = GameManager::getInstance()->getPlayer(0);
	playerOne->draw();

	// Calls parent draw implementation for drawing entities
	Scene::draw();

	_font->draw_text( gc, 10, 440, clan::string_format( "Lives: %1", playerOne->getLives() ), clan::Colorf::whitesmoke );
	_font->draw_text( gc, 500, 440, clan::string_format( "Score: %1", playerOne->getScore() ), clan::Colorf::whitesmoke );

#if _DEBUG
	std::ostringstream playerText;
	playerText.precision( 4 );

	playerText << "Player " << (playerOne->getPlayerNumber() + 1) << std::endl;
	playerText << "SpeedX = " << (playerOne->getSpeed().x) << " SpeedY = " << (playerOne->getSpeed().y) << std::endl;
	playerText << "Shot timer: " << (playerOne->getCurrentWeapon()->getDelay() - playerOne->getCurrentWeapon()->getTimer()) << std::endl;
	playerText << "Model = " << playerOne->getPlayerModel()->getName() << std::endl;
	playerText << "Firing accuracy = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::ACCURACY ) << std::endl;
	playerText << "Lives variation = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::LIVES_VARIATION ) << std::endl;
	playerText << "Enemies wasted wave = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::ENEMIES_WASTED_WAVE ) << std::endl;
	playerText << "Enemies wasted total = " << playerOne->getPlayerModel()->getTraitValue( PlayerModelImpl::ENEMIES_WASTED_TOTAL ) << std::endl;

	if (GameManager::getInstance()->getWindow()->get_ic().get_joystick_count() > 0)
	{
		clan::InputDevice joystick = GameManager::getInstance()->getWindow()->get_ic().get_joystick();
		playerText << "Joystick name = " << joystick.get_name().c_str() << std::endl;

		for (int i = 0; i < joystick.get_button_count(); i++)
		{
			if (joystick.get_keycode( i ))
			{
				playerText << "Joystick key = " << joystick.get_key_name( i ).c_str() << std::endl;
			}
		}

		for (unsigned int i = 0; i < joystick.get_axis_ids().size(); i++)
		{
			playerText << "Joystick axis " << i << " = " << joystick.get_axis( i ) << std::endl;
		}
	}

	std::string drawableText = playerText.str();
	float textX = 640.0f - _font->get_text_size(gc, drawableText).width - 10.f; 
	float textY = 110.0f;

	_font->draw_text(gc, textX, textY, drawableText, clan::Colorf::red);

	std::ostringstream waveText;
	waveText.precision( 4 );

	waveText << "Wave: " << _waveNumber << std::endl;
	waveText << "Enemies wave: " << _enemiesWave << std::endl;
	waveText << "Enemies wave wasted: " << _enemiesWaveWasted << std::endl;
	waveText << "Enemies total: " << _enemiesTotal << std::endl;
	waveText << "Enemies wasted total: " << _enemiesTotalWasted << std::endl;
	waveText << "Shots wave: " << _shotsWave << std::endl;
	waveText << "Shots wave on target: " << _shotsWaveOnTarget << std::endl;
	waveText << "Shots total: " << _shotsTotal << std::endl;
	waveText << "Shots total on target: " << _shotsTotalOnTarget << std::endl;

	std::string waveDrawableText = waveText.str();

	_font->draw_text(gc, 0.0f, 110.0f, waveDrawableText, clan::Colorf::green);

#endif
}

void TestScenePlayer::update()
{
	GameManager* manager = GameManager::getInstance();
	Player* playerOne = manager->getPlayer(0);
	int dt = manager->getDeltaTime();
	PlayerModel* model = playerOne->getPlayerModel();

	if (playerOne->getLives() <= 0)
	{
		GameManager::getInstance()->stopMusic( GameManager::STAGE_1 );
		setNextScene( manager->getGameOverScene() );

		// Last log

		clan::DateTime time = clan::DateTime::get_current_local_time();
		std::ostringstream text;
		text << "Player defeated\n";
		text << time.to_long_time_string().c_str();

		Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
		PlayerModel* model = playerOne->getPlayerModel();

		text << "\nPlayer defeated\n\n ";
		text << "Player: ";
		text << playerOne->getPlayerNumber() + 1;
		text << "\nStats:\n Accuracy ";
		text << model->getTraitValue(PlayerModelImpl::ACCURACY);
		text << "\tLives var ";
		text << model->getTraitValue(PlayerModelImpl::LIVES_VARIATION);
		text << "\tEnemies wave ";
		text << model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE);
		text << "\tEnemies total ";
		text << model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL);
		text << "\nModel name start: ";
		text << model->getName();
		text << "\n";
		text << "==================================\n";

		GameManager::getInstance()->getLogger()->log("Logging end", text.str());

		changeToNextScene();
		return;
	}

	// Checks if there is any wave in progress
	if (!_waveOn)
	{
		// If there are any waves to be processed
		if (_waveNumber < _waves.size())
		{
			waveBegin();
			createWave(_waveNumber);
		}
		else
		{
			GameManager::getInstance()->stopMusic( GameManager::STAGE_1 );

			clan::DateTime time = clan::DateTime::get_current_local_time();
			std::ostringstream text;
			text << time.to_long_time_string().c_str();

			Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
			PlayerModel* model = playerOne->getPlayerModel();

			text << "\nPlayer succeeded\n\n ";
			text << "Player: ";
			text << playerOne->getPlayerNumber() + 1;
			text << "\nStats:\n Accuracy ";
			text << model->getTraitValue(PlayerModelImpl::ACCURACY);
			text << "\tLives var ";
			text << model->getTraitValue(PlayerModelImpl::LIVES_VARIATION);
			text << "\tEnemies wave ";
			text << model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE);
			text << "\tEnemies total ";
			text << model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL);
			text << "\nModel name start: ";
			text << model->getName();
			text << "\n";
			text << "==================================\n";

			GameManager::getInstance()->getLogger()->log("Logging end", text.str());

			changeToNextScene();
			return;
		}
	}
	else
	{
		if (_enemies.size() == 0)
		{
			waveFinish();
		}
	}

	// Player updates occur separately because players can drop in or out
	// treating this in entities would be messy
	playerOne->update();

#if _DEBUG

	clan::InputDevice keyboard = manager->getWindow()->get_ic().get_keyboard();

	const float variation = 0.001f;

	if (keyboard.get_keycode(clan::keycode_y))
	{
		model->setTraitValue(PlayerModelImpl::ACCURACY, model->getTraitValue(PlayerModelImpl::ACCURACY) + dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_u))
	{
		model->setTraitValue(PlayerModelImpl::LIVES_VARIATION, model->getTraitValue(PlayerModelImpl::LIVES_VARIATION) + dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_i))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE) + dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_o))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL) + dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_h))
	{
		model->setTraitValue(PlayerModelImpl::ACCURACY, model->getTraitValue(PlayerModelImpl::ACCURACY) - dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_j))
	{
		model->setTraitValue(PlayerModelImpl::LIVES_VARIATION, model->getTraitValue(PlayerModelImpl::LIVES_VARIATION) - dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_k))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE) - dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_l))
	{
		model->setTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL, model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL) - dt*variation);
	}

	if (keyboard.get_keycode(clan::keycode_p))
	{
		model->resetTraits();
	}

	if (keyboard.get_keycode(clan::keycode_e))
	{
		createDebugEnemy();
	}

	if (keyboard.get_keycode(clan::keycode_space))
	{
		std::string modelName = model->getName();

		// Updates player model observed
		AIManager* aimanager = GameManager::getInstance()->getAIManager();
		aimanager->update();
		
		/*LOGOG_INFO( "Player: %d\nStats:\n Accuracy %f\tLives var %f\tEnemies total %f\nModel name before update: %s\nModel name after update: %s\n",
			playerOne->getPlayerNumber() + 1, playerOne->getPlayerModel()->getTraitValue(PlayerModelImpl::ACCURACY), model->getTraitValue(PlayerModelImpl::LIVES_VARIATION),
			model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL),	modelName.c_str(), playerOne->getPlayerModel()->getName().c_str() );*/
	}

#endif

	// Calls parent implementation of update, updating all Entities
	Scene::update();

	// Treat playerShots and enemyShots collision and out of bounds
	computeShotsCollision();

	// Treat player-enemy collisions
	computePlayerEnemyCollision();

	// Checks if any enemy is dead or out of bounds
	validateEnemies();
}



void TestScenePlayer::addPlayerShot( Shot* newShot )
{
	// For drawing and updating
	insertEntity( newShot );

	// For collision checking
	_playerShots.push_back( newShot );

	_shotsTotal++;
	_shotsWave++;
}



void TestScenePlayer::addEnemyShot( Shot* newShot )
{
	// For drawing and updating
	insertEntity( newShot );

	// For collision checking
	_enemyShots.push_back( newShot );
}



void TestScenePlayer::removePlayerShot( Shot* shot )
{
	if (shot != NULL)
	{
		removeEntity( shot );
		_playerShots.remove( shot );
	}
}



void TestScenePlayer::removeEnemyShot( Shot* shot )
{
	if (shot != NULL)
	{
		removeEntity( shot );
		_enemyShots.remove( shot );
	}
}



void TestScenePlayer::computeShotsCollision() 
{
	Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
	std::list<Shot*>::iterator shotIt;
	std::vector<Enemy*>::iterator enemyIt;
	bool remove;

	// Player shots colliding with enemies
	for(shotIt = _playerShots.begin(); shotIt != _playerShots.end(); )
	{
		// Checks if inside window boundaries
		if (!(*shotIt)->checkWindowBoundary())
		{
			Shot* remove = *shotIt;
			shotIt++;
			removePlayerShot( remove );
			delete remove;
			continue;
		}

		remove = false;
		clan::CollisionOutline& shot = const_cast<clan::CollisionOutline&>((*shotIt)->getCurrentCollisionOutline());

		// Translates outlines to their current sprite position as outlines start in 0,0
		clan::Vec2f pos = (*shotIt)->getPosition();
		shot.set_translation(pos.x, pos.y);

		for (enemyIt = _enemies.begin(); enemyIt != _enemies.end(); enemyIt++)
		{
			clan::CollisionOutline& object = const_cast<clan::CollisionOutline&>((*enemyIt)->getCurrentCollisionOutline());

			clan::Vec2f posEnemy = (*enemyIt)->getPosition();
			object.set_translation(posEnemy.x, posEnemy.y);

			if (shot.collide( object ))
			{
				// Applies damage to enemy
				computeShotHitEnemy( (*shotIt), (*enemyIt) );
				object.set_translation(0.0f, 0.0f);
				remove = true;
				break;
			}

			object.set_translation(0.0f, 0.0f);
		}

		shot.set_translation(0.0f, 0.0f);

		if (remove)
		{
			Shot* shotRemove = (*shotIt);
			shotIt++;
			removePlayerShot( shotRemove );
			delete shotRemove;
		} 
		else
		{
			shotIt++;
		}

	}

	// As currently there is just one player...
	clan::CollisionOutline& player = const_cast<clan::CollisionOutline&>(playerOne->getCurrentCollisionOutline());

	float scale = GameManager::getInstance()->getPlayerOptions()->hitBoxScale;
	float halfComplementScale = (1.0f - scale)*0.5f;

	// Reduce player hitbox area
	player.set_scale( scale, scale );

	// Translate halfComplementScale*width and halfComplementScale*height
	// Translation is set to the current player position
	player.set_translation( playerOne->getPosition().x + playerOne->getCurrentSprite().get_width()*halfComplementScale,
		playerOne->getPosition().y + playerOne->getCurrentSprite().get_height()*halfComplementScale );


	// Enemies shots colliding with player
	for(shotIt = _enemyShots.begin(); shotIt != _enemyShots.end(); )
	{
		// Checks if inside window boundaries
		if (!(*shotIt)->checkWindowBoundary())
		{
			Shot* remove = *shotIt;
			shotIt++;
			removeEnemyShot( remove );
			delete remove;
			continue;
		}

		clan::CollisionOutline& shot = const_cast<clan::CollisionOutline&>((*shotIt)->getCurrentCollisionOutline());

		clan::Vec2f pos = (*shotIt)->getPosition();
		shot.set_translation(pos.x, pos.y);

		if (shot.collide( player ))
		{
			if (!playerOne->getInvincible())
				computeShotHitPlayer( (*shotIt), playerOne );

			Shot* shotRemove = *shotIt;
			shotIt++;

			removeEnemyShot( shotRemove );
			delete ( shotRemove );
		}
		else
		{
			shot.set_translation(0.0f, 0.0f);
			shotIt++;
		}
	}

	player.set_scale( 1.0f, 1.0f );

	// Returns player outline to 0,0 (drawing uses translation on x,y drawing point)
	player.set_translation(0.0f, 0.0f);
}



void TestScenePlayer::computePlayerEnemyCollision()
{
	Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
	std::vector< Enemy* >::iterator enemyIt;

	// As currently there is just one player...
	clan::CollisionOutline& playerOutline = const_cast<clan::CollisionOutline&>(playerOne->getCurrentCollisionOutline());

	float scale = GameManager::getInstance()->getPlayerOptions()->hitBoxScale;
	float halfComplementScale = (1.0f - scale)*0.5f;

	// Reduce player hitbox area
	playerOutline.set_scale( scale, scale );

	// Translate halfComplementScale*width and halfComplementScale*height
	// Translation is set to the current player position
	playerOutline.set_translation( playerOne->getPosition().x + playerOne->getCurrentSprite().get_width()*halfComplementScale,
		playerOne->getPosition().y + playerOne->getCurrentSprite().get_height()*halfComplementScale );

	// Translation is set to the current player position
	playerOutline.set_translation( playerOne->getPosition().x, playerOne->getPosition().y );

	// Enemies colliding with player
	for(enemyIt = _enemies.begin(); enemyIt != _enemies.end(); )
	{
		clan::CollisionOutline& enemyOutline = const_cast<clan::CollisionOutline&>((*enemyIt)->getCurrentCollisionOutline());

		clan::Vec2f pos = (*enemyIt)->getPosition();
		enemyOutline.set_translation(pos.x, pos.y);

		if (enemyOutline.collide( playerOutline ))
		{
			if (!playerOne->getInvincible())
				computePlayerEnemyCollisionDamage( playerOne, (*enemyIt) );
		}
		
		enemyOutline.set_translation( 0.0f, 0.0f );
		enemyIt++;
	}

	// Returns player outline to 0,0 (drawing uses translation on x,y drawing point)
	playerOutline.set_scale( 1.0f, 1.0f );
	playerOutline.set_translation( 0.0f, 0.0f );
}



void TestScenePlayer::waveBegin()
{
	Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
	_livesStartWave = playerOne->getLives();
	_enemiesWave = 0;
	_enemiesWaveWasted = 0;
	_shotsWave = 0;
	_shotsWaveOnTarget = 0;
	
	_waveOn = true;
}



void TestScenePlayer::waveFinish()
{
	Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
	PlayerModel* model = playerOne->getPlayerModel();

	std::string modelNameBefore = model->getName();

	_livesEndWave = playerOne->getLives();
	
	float livesVariation = (float) (_livesEndWave - _livesStartWave) / (float) _livesStartWave ;
	float accuracyWave = (float)_shotsWaveOnTarget/(float)_shotsWave;
	float enemiesWastedWave = (float)_enemiesWaveWasted/(float)_enemiesWave;
	float enemiesWastedTotal = (float)_enemiesTotalWasted/(float)_enemiesTotal;

	model->updateTrait( PlayerModelImpl::ACCURACY, accuracyWave );
	model->updateTrait( PlayerModelImpl::ENEMIES_WASTED_WAVE, enemiesWastedWave );
	model->updateTrait( PlayerModelImpl::LIVES_VARIATION, livesVariation );
	model->updateTrait( PlayerModelImpl::ENEMIES_WASTED_TOTAL, enemiesWastedTotal );

#if ADAPTIVE
	GameManager::getInstance()->getAIManager()->update();
#endif

	clan::DateTime time = clan::DateTime::get_current_local_time();

	std::ostringstream text;
	text << time.to_long_time_string().c_str();
	
	text << "\nWave ";
	text << _waveNumber;
	text << " finish\n\n";
	text << "Player: ";
	text << playerOne->getPlayerNumber() + 1;
	text << "\nWave stats:\n Accuracy ";
	text << accuracyWave;
	text << "\tLives var ";
	text << livesVariation;
	text << "\tEnemies wave ";
	text << enemiesWastedWave;
	text << "\tEnemies wasted total ";
	text << enemiesWastedTotal;
	text << "\nPlayer model traits:\n Accuracy ";
	text << model->getTraitValue(PlayerModelImpl::ACCURACY);
	text << "\tLives var ";
	text << model->getTraitValue(PlayerModelImpl::LIVES_VARIATION);
	text << "\tEnemies wave ";
	text << model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_WAVE);
	text << "\tEnemies total ";
	text << model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL);
	text << "\nModel name before update: ";
	text << modelNameBefore;
	text << "\nModel name after update: ";
	text << model->getName();
	text << "\n";

	GameManager::getInstance()->getLogger()->log("Update", text.str());

	/*LOGOG_INFO( "\nWave %d Finish: %s\n\nPlayer: %d\nStats:\n Accuracy %f\tLives var %f\tEnemies total %f\nModel name before update: %s\nModel name after update: %s\n",
		_waveNumber, time.to_long_time_string().c_str(), playerOne->getPlayerNumber() + 1, model->getTraitValue(PlayerModelImpl::ACCURACY),
		model->getTraitValue(PlayerModelImpl::LIVES_VARIATION),	model->getTraitValue(PlayerModelImpl::ENEMIES_WASTED_TOTAL), model->getName().c_str(),
		playerOne->getPlayerModel()->getName().c_str() );*/

	_waveNumber++;
	_waveOn = false;
}



void TestScenePlayer::validateEnemies()
{
	Player* playerOne = GameManager::getInstance()->getPlayer( 0 );
	std::vector<Enemy*>::iterator enemyIt;

	for (enemyIt = _enemies.begin(); enemyIt != _enemies.end(); )
	{
		Enemy* enemy = (*enemyIt);

		// Check if enemy is destroyed
		if (enemy->getHealth() <= 0)
		{
			_enemiesTotalWasted++;
			_enemiesWaveWasted++;
			
			playerOne->addToScore( enemy->getPoints() );

			insertEntity( new Explosion( enemy->getPosition().x + enemy->getCurrentSprite().get_width()*0.5f,
				enemy->getPosition().y + enemy->getCurrentSprite().get_height()*0.5f, enemy->getSpeed().x*enemy->getMultiplier(),
				enemy->getSpeed().y*enemy->getMultiplier(), "sprites/explosionMedium" ) );
			
			GameManager::getInstance()->playSoundEffect( GameManager::SFX_EXPLOSION );

			removeEntity( enemy );
			enemyIt = _enemies.erase( enemyIt );
			GameManager::getInstance()->getAIManager()->removeAgent( enemy );
			delete enemy;
		} 
		else
		{
			clan::GraphicContext& gc = GameManager::getInstance()->getWindow()->get_gc();
			// Checks if enemy still above the bottom of the window
			if (enemy->getPosition().y > (float)gc.get_height())
			{
				removeEntity( enemy );
				enemyIt = _enemies.erase( enemyIt );
				GameManager::getInstance()->getAIManager()->removeAgent( enemy );
				delete enemy;
			} 
			else
			{
				enemyIt++;
			}
		}
	}
}



void TestScenePlayer::addWaveEnemy( Enemy* enemy )
{
	// Inserts enemy in AIManager control list
	GameManager::getInstance()->getAIManager()->insertAgent( enemy );

	// Inserts enemy in Scene control list
	insertEntity( enemy );

	// Inserts enemy in Enemies control vector
	_enemies.push_back( enemy );

	_enemiesTotal++;
	_enemiesWave++;
}



void TestScenePlayer::computeShotHitEnemy( Shot* shot, Enemy* enemy )
{
	enemy->setHealth( enemy->getHealth() - shot->getDamage() );
	_shotsWaveOnTarget++;
	_shotsTotalOnTarget++;
}



void TestScenePlayer::computeShotHitPlayer( Shot* shot, Player* player )
{
	player->subtractLives( 1 );
	player->setInvincible( true );
}



void TestScenePlayer::computePlayerEnemyCollisionDamage( Player* player, Enemy* enemy )
{
	// TODO: check if Enemy is of Boss subtype. Bosses should not die on player contact.
	enemy->setHealth( 0 );
	player->subtractLives( 1 );
	player->setInvincible( true );
}



#ifdef _DEBUG
void TestScenePlayer::createDebugEnemy()
{

	clan::Rect windowArea = GameManager::getInstance()->getWindow()->get_viewport();
	TestEnemy* enemy = new TestEnemy( 0.0f, 0.0f, 50.0f, 50.0f, "sprites/enemy1"  );

	// Adjusts enemy position to the horizontal center of the window
	enemy->setPositionX( windowArea.get_width()*0.5f - enemy->getCurrentSprite().get_width()*0.5f );

	addWaveEnemy( enemy );
}
#endif // _DEBUG



void TestScenePlayer::createWave( int i )
{
	Wave wave = _waves[i];

	for (unsigned int i = 0; i < wave.enemies.size(); i++)
	{
		EnemyDescription desc = wave.enemies[i];
		TestEnemy* enemy = new TestEnemy( desc.startPositionX, desc.startPositionY, desc.speedX, desc.speedY, desc.resource );
		enemy->setBehavior( desc.behavior );
		enemy->setAmplitudeLimit( 200.f );
		addWaveEnemy( enemy );
	}

	// Updates enemies to match current observed player model
	GameManager::getInstance()->getAIManager()->updateAgents();
}



void TestScenePlayer::loadScene( std::string sceneFile )
{
	lua_State* l = GameManager::getInstance()->getLuaState();

	int loadResult = luaL_dofile( l, sceneFile.c_str() );

	if(loadResult)
	{
		// Create a console window for text-output if not available
		clan::ConsoleWindow console( "Console", 80, 160 );
		clan::Console::write_line( "\nError loading %1", sceneFile );
		clan::Console::write_line( "\n%1", lua_tostring( l, -1 ) );
		clan::Console::wait_for_key();

		// Pops error message from stack
		lua_pop( l, 1 );
		return;
	}

	lua_getglobal( l, "scene" );

	if (lua_istable( l, -1 ))
	{
		// Gets the number of waves in scene
		size_t waves = lua_objlen( l, -1 );

		// Lua arrays start at 1
		for (unsigned int i = 1; i <= waves; i++)
		{
			Wave wave;

			// Pushes the table index into stack
			lua_pushinteger( l, i );
			// Gets the element i from table wave (index -2)
			lua_gettable(l, -2);

			if (lua_istable( l, -1 ))
			{
				// Gets the number of enemies in current wave
				size_t enemies = lua_objlen( l, -1 );

				for (unsigned int j = 1; j <= enemies; j++)
				{
					// Pushes the table index into stack
					lua_pushinteger( l, j );
					// Gets the element j from table enemy (index -2)
					lua_gettable( l, -2 );

					if(lua_istable( l, -1 ))
					{
						EnemyDescription desc;

						// Getting resource
						lua_pushinteger( l, EDD_SPRITE_RESOURCE );
						lua_gettable( l, -2 );

						desc.resource = lua_tostring( l, -1 );
						lua_pop( l, 1 );

						// Getting start position x
						lua_pushinteger( l, EDD_START_X );
						lua_gettable( l, -2 );

						desc.startPositionX = (float) lua_tonumber( l, -1 );
						lua_pop( l, 1 );

						// Getting start position y
						lua_pushinteger( l, EDD_START_Y );
						lua_gettable( l, -2 );

						desc.startPositionY = (float) lua_tonumber( l, -1 );
						lua_pop( l, 1 );

						// Getting speed x
						lua_pushinteger( l, EDD_SPEED_X );
						lua_gettable( l, -2 );

						desc.speedX = (float) lua_tonumber( l, -1 );
						lua_pop( l, 1 );

						// Getting speed y
						lua_pushinteger( l, EDD_SPEED_Y );
						lua_gettable( l, -2 );

						desc.speedY = (float) lua_tonumber( l, -1 );
						lua_pop( l, 1 );

						// Getting behavior
						lua_pushinteger( l, EDD_BEHAVIOR );
						lua_gettable( l, -2 );

						desc.behavior = (unsigned int) lua_tonumber( l, -1 );
						lua_pop( l, 1 );

						wave.enemies.push_back( desc );

						// Pops the enemy
						lua_pop( l, 1 );
					}
				}

				_waves.push_back( wave );

				// Pops the wave
				lua_pop( l, 1);
			}
		}
	}

	// Pops scene
	lua_pop( l, 1 );
}
