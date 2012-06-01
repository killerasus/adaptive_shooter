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

FadingScene::FadingScene():_fadein(0.0f),_fadeout(0.0f),_waittime(0.0f),_mode(FM_NO_FADE),_fadingState(FS_COMPLETED),_backgroundColor(0,0,0),_timer(0.0f)
{
	_sceneState = SS_RUNNING;
}

FadingScene::FadingScene( float fadein, float fadeout, float waittime, FadingMode mode ):_fadein(fadein),_fadeout(fadeout),_waittime(waittime),_mode(mode),_backgroundColor(0,0,0),_timer(0.0f)
{
	_sceneState = SS_RUNNING;

	switch(mode)
	{
		case FM_NO_FADE:
			_fadingState = FS_COMPLETED;
			break;
		case FM_FADE_IN:
			_fadingState = FS_FADE_IN;
			break;
		case FM_FADE_OUT:
			_fadingState = FS_FADE_OUT;
			break;
		case FM_FADE_INOUT:
			_fadingState = FS_FADE_IN;
			break;
		default:
			_fadingState = FS_COMPLETED;
			_sceneState = SS_COMPLETED;
	}
}

FadingScene::~FadingScene()
{

}

void FadingScene::SetBackgroundColor( CL_Color color )
{
	_backgroundColor = color;
}

CL_Color FadingScene::GetBackgroundColor()
{
	return _backgroundColor;
}

/* Override */
void FadingScene::update()
{
	if (_sceneState == SS_COMPLETED)
	{
		changeToNextScene();
	}

	float alpha = 1;

	if(_fadingState != FS_COMPLETED)
	{
		_timer += GameManager::getInstance()->getDeltaTime();

		switch(_fadingState)
		{
			case FS_FADE_IN:
				if (_timer >= _fadein)
				{
					if (_mode == FM_FADE_IN)
					{
						_fadingState = FS_COMPLETED;
						_sceneState = SS_COMPLETED;
					} 
					else
					{
						_fadingState = FS_WAITING;
					}//if

					_timer = 0.0f;
				}
				else
				{
					//alpha = 1 - _timer/_fadein;
					alpha = _timer/_fadein;
				}//if

				break;

			case FS_FADE_OUT:
				if (_timer >= _fadeout)
				{
					_fadingState = FS_COMPLETED;
					_sceneState = SS_COMPLETED;
					_timer = 0.0f;
					alpha = 0.0f;
				}
				else
				{
					alpha = 1 - _timer/_fadeout;
				}//if

				break;
			case FS_WAITING:
				if (_timer >= _waittime)
				{
					_fadingState = FS_FADE_OUT;
					_timer = 0.0f;
				}//if

				break;
			case FS_COMPLETED:
				//For compiler warnings
			default:
				/* default */
				break;
		}//switch-case
	}
	else
	{
		if (_mode == FM_FADE_IN)
		{
			alpha = 1.0f;
		} 
		else
		{
			alpha = 0.0f;
		}//if
	}//if

	for (std::vector<Entity*>::iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		(*it)->setAlpha(alpha);
		(*it)->update();
	}

}


void FadingScene::SetFadeMode( FadingMode mode )
{
	_mode = mode;
}

FadingScene::FadingMode FadingScene::GetFadeMode()
{
	return _mode;
}

