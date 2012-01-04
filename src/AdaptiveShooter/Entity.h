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

class Entity
{
public:

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void SetAlpha( float alpha ) = 0;

protected:
	
private:
};

#endif // Entity_h__
