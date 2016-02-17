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

class FadingScene : virtual public Scene
{
public:

	enum FadingMode {
		FM_NO_FADE = 0,
		FM_FADE_IN,
		FM_FADE_OUT,
		FM_FADE_INOUT
	};

	FadingScene();
	FadingScene(float fadein, float fadeout, float waittime, FadingScene::FadingMode mode);
	virtual ~FadingScene();

	void SetBackgroundColor(clan::Color color);
	clan::Color GetBackgroundColor();
	void SetFadeInTime(float time_ms);
	float GetFadeInTime();
	void SetFadeOutTime(float time_ms);
	float GetFadeOutTime();
	void SetWaitTime(float time_ms);
	float GetWaitTime();
	void SetFadeMode(FadingScene::FadingMode mode);
	FadingScene::FadingMode GetFadeMode();

	/* overrides */
	virtual void update();

protected:
	enum FadingState {
		FS_FADE_IN = 0,
		FS_FADE_OUT,
		FS_WAITING,
		FS_COMPLETED
	};
	
private:
	clan::Color _backgroundColor;
	float _fadein;
	float _fadeout;
	float _waittime;
	float _timer;
	FadingMode _mode;
	FadingState _fadingState;
};

#endif // FadingScene_h__
