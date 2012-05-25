/********************************************************************
	created:	2011/12/06
	created:	6:12:2011   19:49
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\TestEntity.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	StaticEntity
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef StaticEntity_h__
#define StaticEntity_h__

#include "Entity.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>

class StaticEntity : public Entity
{
public:
	StaticEntity(float x, float y, std::string resource_id);
	virtual ~StaticEntity();

	virtual void draw();

	virtual void update();

	virtual void setAlpha( float alpha );

protected:
	
private:
	CL_Sprite* _sprite;
	CL_Vec2f _pos;
};

#endif // TestEntity_h__
