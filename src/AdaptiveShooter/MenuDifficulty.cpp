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

MenuDifficulty::MenuDifficulty() : Menu()
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
	insertEntity( easy );
	insertEntity( normal );
	insertEntity( hard );

	// Inserting into menu items
	_menuItems.push_back( easy );
	_menuItems.push_back( normal );
	_menuItems.push_back( hard );
}




MenuDifficulty::~MenuDifficulty()
{

}



#ifdef _DEBUG
/*Override*/
void MenuDifficulty::draw()
{
	Menu::draw();

	CL_GraphicContext gc = GameManager::getInstance()->getWindow()->get_gc();

	std::ostringstream menuText;
	menuText.precision( 4 );

	for (int i = 0; i < _menuItems.size(); i++)
	{
		menuText << "Menu item " << i << " state: " << _menuItems[i]->getSelected() << std::endl;
	}

	std::string drawableText = menuText.str();
	float textX = 640.0f - _font->get_text_size(gc, drawableText).width - 10.f; 
	float textY = 110.0f;

	_font->draw_text(gc, textX, textY, drawableText, CL_Colorf::red);
}
#endif



void MenuDifficulty::ExecuteState()
{
	switch (getMenuState())
	{
	case DIFFICULTY_EASY:
		break;
	case DIFFICULTY_NORMAL:
		break;
	case DIFFICULTY_HARD:
		break;
	default:
		break;
	}

	changeToNextScene();
}
