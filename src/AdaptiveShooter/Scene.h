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

	/**
	 * Calls each of _entities destructor
	 */
	virtual ~Scene();

	virtual void draw();

	virtual void update();

	/**
	 * Inserts an Entity in list control.
	 * 
	 * @param[in]  entity	Pointer to entity to add
	 */
	void insertEntity(Entity* entity);

	/**
	 *	Removes an Entity from the control list. Does not call entity's destructor.
	 * 
	 * @param[in]  entity	Pointer to entity to remove
	 */
	void removeEntity(Entity* entity);

	/**
	 * Gets an Entity from the control list
	 * 
	 * @param[in]  i		Position of the entity in the list
	 * @return	  Entity*	Pointer to the entity.
	 */
	Entity* getEntity(unsigned int i);

	/**
	 * Gets the pointer to the next scene
	 * 
	 * @return	  Scene*
	 */
	Scene* getNextScene();

	/**
	 * Sets next scene
	 * @param	  next
	 */
	void setNextScene(Scene* next);

	/**
	 * Inserts an entity into the post update delete list
	 * 
	 * @param[in]	entity	Entity to be deleted
	 */
	void pushEntityToDelete(Entity* entity);

protected:
	/**
	 * Changes to the next scene in the stack
	 */
	void changeToNextScene();

	std::list< Entity* > _entities; // List of scene Entities (Enemies, etc.)
	std::list< Entity* > _deleteEntities; // List of Entities to be deleted after update
	SceneState _sceneState;
	Scene *_nextScene;
private:
};

#endif // Scene_h__