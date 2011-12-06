/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   11:51
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\FadingScene.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	FadingScene
	file ext:	cpp
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Implementation of the FadingScene class
*********************************************************************/
#include "FadingScene.h"
#include "GameManager.h"

FadingScene::FadingScene():_fadein(0.0f),_fadeout(0.0f),_waittime(0.0f)
{

}

FadingScene::FadingScene( std::string imageResource, float fadein, float fadeout, float waittime ):_fadein(fadein),_fadeout(fadeout),_waittime(waittime)
{
	_sprite = new CL_Sprite(GameManager::GetInstance()->GetWindow()->get_gc(), imageResource, GameManager::GetInstance()->GetResourceManager());
}

FadingScene::~FadingScene()
{
	delete _sprite;
}

void FadingScene::SetBackgroundColor( CL_Color color )
{

}

CL_Color FadingScene::GetBackgroundColor()
{
	return CL_Color(0,0,0);
}

void FadingScene::draw()
{

}

void FadingScene::update()
{

}
