/********************************************************************
	created:	2011/12/06
	created:	6:12:2011   19:51
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\TestEntity.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	TestEntity
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "TestEntity.h"
#include "GameManager.h"

TestEntity::TestEntity(float x, float y, std::string resource_id):_pos(x,y)
{
	GameManager* manager = GameManager::GetInstance();
	CL_GraphicContext gc = manager->GetWindow()->get_gc();

	_sprite = new CL_Sprite(gc, resource_id, manager->GetResourceManager());
}

TestEntity::~TestEntity()
{
	delete _sprite;
}

void TestEntity::draw()
{
	_sprite->draw(GameManager::GetInstance()->GetWindow()->get_gc(), _pos.x, _pos.y);
}

void TestEntity::update()
{
	_sprite->update();
}

void TestEntity::SetAlpha( float alpha )
{
	_sprite->set_alpha(alpha);
}
