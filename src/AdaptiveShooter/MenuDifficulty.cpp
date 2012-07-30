/********************************************************************
	created:	2012/07/25
	created:	25:7:2012   12:35
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\MenuDifficulty.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	MenuDifficulty
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include <iostream>
#include <sstream>

#include "GameManager.h"
#include "MenuDifficulty.h"
#include "MenuItem.h"

MenuDifficulty::MenuDifficulty() : Menu(), FadingScene( 0.0f, 1000.f, 0.0f, FadingScene::FM_FADE_OUT ), _isFading( false )
{
#ifdef _DEBUG
	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();
	_font = new CL_Font( gc, "Tahoma", 14 );
#endif // _DEBUG

	

	MenuItem* easy = new MenuItem( 170.f, 5.f, "menu/easy_selected", "menu/easy_notselected" );
	MenuItem* normal = new MenuItem( 170.f, easy->getPosition().y + easy->getCurrentSprite()->get_height() + 10.f,
		"menu/normal_selected", "menu/normal_notselected" );
	MenuItem* hard = new MenuItem( 170.f, normal->getPosition().y + normal->getCurrentSprite()->get_height() + 10.f,
		"menu/hard_selected", "menu/hard_notselected" );

	easy->setSelected( true );

	// Delegating delete to Scene
	Scene::insertEntity( easy );
	Scene::insertEntity( normal );
	Scene::insertEntity( hard );

	// Inserting into menu items
	_menuItems.push_back( easy );
	_menuItems.push_back( normal );
	_menuItems.push_back( hard );
}




MenuDifficulty::~MenuDifficulty()
{

}



/*Override*/
void MenuDifficulty::draw()
{
	if (!_isFading)
	{
		Menu::draw();
	}
	else
	{
		FadingScene::draw();
	}


#ifdef _DEBUG
	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();

	std::ostringstream menuText;
	menuText.precision( 4 );

	for (unsigned int i = 0; i < _menuItems.size(); i++)
	{
		menuText << "Menu item " << i << " state: " << _menuItems[i]->getSelected() << std::endl;
	}

	std::string drawableText = menuText.str();
	float textX = 640.0f - _font->get_text_size(gc, drawableText).width - 10.f; 
	float textY = 110.0f;

	_font->draw_text(gc, textX, textY, drawableText, CL_Colorf::red);
#endif
}



/*Override*/
void MenuDifficulty::update()
{
	if (!_isFading)
	{
		Menu::update();
	} 
	else
	{
		FadingScene::update();
	}
}



void MenuDifficulty::ExecuteState()
{
	AIManager* aiManager = GameManager::getInstance()->getAIManager();
	std::vector<PlayerModel*> *playerModels = aiManager->copyPlayerModelVector();

	switch (getMenuState())
	{
	case DIFFICULTY_EASY:
		aiManager->setCurrentReferenceModel( (*playerModels)[0] );
		aiManager->getCurrentPlayerModel()->setName("Easy");
		aiManager->getCurrentPlayerModel()->setTraitsToReferenceAverage( (*playerModels)[0] );
		break;
	case DIFFICULTY_NORMAL:
		aiManager->setCurrentReferenceModel( (*playerModels)[1] );
		aiManager->getCurrentPlayerModel()->setName("Normal");
		aiManager->getCurrentPlayerModel()->setTraitsToReferenceAverage( (*playerModels)[1] );
		break;
	case DIFFICULTY_HARD:
		aiManager->setCurrentReferenceModel( (*playerModels)[2] );
		aiManager->getCurrentPlayerModel()->setName("Hard");
		aiManager->getCurrentPlayerModel()->setTraitsToReferenceAverage( (*playerModels)[2] );
		break;
	default:
		break;
	}

	aiManager->updateAgents();
	_isFading = true;
	delete playerModels;
}
