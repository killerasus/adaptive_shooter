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

#include "Entity.h"
#include <list>

class Scene
{
public:

	enum SceneState
	{
		SS_RUNNING = 0,
		SS_COMPLETED
	};

	Scene();
	virtual ~Scene();

	virtual void draw();

	virtual void update();

	void insertEntity(Entity* entity);

	void removeEntity(Entity* entity);

	Entity* getEntity(unsigned int i);

	Scene* getNextScene();

	void setNextScene(Scene* next);

protected:
	void changeToNextScene();

	std::list< Entity* > _entities;
	SceneState _sceneState;
	Scene *_nextScene;
private:
};

#endif // Scene_h__