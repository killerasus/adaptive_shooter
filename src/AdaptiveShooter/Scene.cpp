/********************************************************************
	created:	2011/12/06
	created:	6:12:2011   18:22
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\Scene.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	Scene
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Scene.h"
#include "GameManager.h"

Scene::Scene() : _nextScene( NULL )
{}

Scene::~Scene()
{
	for (std::list<Entity*>::iterator it = _entities.begin(); it != _entities.end(); )
	{
		delete (*it);
		it = _entities.erase( it );
	}
}

void Scene::insertEntity( Entity* entity)
{ _entities.push_back(entity); }

void Scene::removeEntity( Entity* entity )
{ _entities.remove( entity ); }

Entity* Scene::getEntity( unsigned int i )
{
	Entity* ret = NULL;
	int j = 0;

	for ( std::list<Entity*>::iterator it = _entities.begin(); it != _entities.end(); it++, j++ )
	{
		if ( j == i )
		{
			ret = *it;
			break;
		}
	}

	return ret;
}

void Scene::draw()
{
	for ( std::list<Entity*>::iterator it = _entities.begin(); it != _entities.end(); it++ )
	{
		(*it)->draw();
	}
}

void Scene::update()
{
	for ( std::list<Entity*>::iterator it = _entities.begin(); it != _entities.end(); it++ )
		(*it)->update();

	// Deletes entities pushed into _deleteEntities list
	for ( std::list<Entity*>::iterator it = _deleteEntities.begin(); it!= _deleteEntities.end(); it++)
		removeEntity( (*it) );

	_deleteEntities.clear();
}

Scene* Scene::getNextScene()
{ return _nextScene; }

void Scene::setNextScene( Scene* next )
{ _nextScene = next; }

void Scene::changeToNextScene()
{
	GameManager* manager = GameManager::getInstance();
	manager->popScene();
	manager->pushScene( _nextScene );
}

void Scene::pushEntityToDelete( Entity* entity )
{ _deleteEntities.push_back( entity ); }
