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
#pragma once

#include "Entity.h"

class StaticEntity : public Entity
{
public:
	StaticEntity(float x, float y, std::string resource_id);
	virtual ~StaticEntity();

	virtual void draw();

	virtual void update();

protected:
	
private:
};
