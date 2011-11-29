/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   8:19
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\Scene.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	Scene
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Scene interface definition
*********************************************************************/

#ifndef Scene_h__
#define Scene_h__

class Scene
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;

protected:
	
private:
};

#endif // Scene_h__