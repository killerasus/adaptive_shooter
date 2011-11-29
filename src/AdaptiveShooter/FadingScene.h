/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   11:27
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter\FadingScene.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertação\AdaptiveShooter\src\AdaptiveShooter
	file base:	FadingScene
	file ext:	h
	author:		Bruno Baère Pederassi Lomba de Araujo
	
	purpose:	Definition of the FadingScene class
*********************************************************************/

#ifndef FadingScene_h__
#define FadingScene_h__

#include "Scene.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"

class FadingScene : public Scene
{
public:
	FadingScene();
	FadingScene(std::string imageResource, float fadein, float fadeout, float waittime);
	virtual ~FadingScene();

	enum SceneState {
		FADE_IN = 0,
		NO_FADE,
		FADE_OUT,
		COMPLETED
	};

	void SetBackgroundColor(CL_Color color);
	CL_Color GetBackgroundColor();
	void SetFadeInTime(float time_ms);
	float GetFadeInTime();
	void SetFadeOutTime(float time_ms);
	float GetFadeOutTime();
	void SetWaitTime(float time_ms);
	float GetWaitTime();

	virtual void draw();
	virtual void update();

protected:
	
private:
	CL_Color _backgroundColor;
	CL_Sprite* _sprite;
	float _fadein;
	float _fadeout;
	float _waittime;
	SceneState _state;
};

#endif // FadingScene_h__
