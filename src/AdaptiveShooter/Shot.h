/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   13:20
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Shot.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Shot
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#ifndef Shot_h__
#define Shot_h__

#include "DynamicEntity.h"

class Shot : public DynamicEntity
{
public:
	Shot(std::string resource);
	
	Shot(float x, float y, float speedX, float speedY, std::string resource);
	
	Shot(CL_Vec2f& position, CL_Vec2f& speed, std::string resource);

	virtual ~Shot();

	virtual void draw();

	virtual void update();

protected:
	
private:
};

#endif // Shot_h__
