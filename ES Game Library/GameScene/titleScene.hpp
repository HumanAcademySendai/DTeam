#pragma once

#include "GameScene.hpp"
#include "../ESGLib.h"

class titleScene : public CGameScene {
public:
	titleScene()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~titleScene()
	{
		Finalize();

#ifdef _INC_SQUIRREL
		Squirrel.ReleaseAllScripts();
#endif
#ifdef _INC_NUI
		NUI.ReleaseAllKinects();
#endif
#ifdef _INC_LIVE2D
		Live2D.ReleaseAllModels();
#endif
#ifdef _INC_EFFEKSEER
		Effekseer.ReleaseAllEffects();
#endif
#ifdef _INC_DIRECT2D
		Direct2D.ReleaseAllResources();
#endif
		MediaManager.ReleaseAllMedia();

		SoundDevice.ReleaseAllMusics();
		SoundDevice.ReleaseAllSounds();

		GraphicsDevice.ReleaseAllRenderTargets();
		GraphicsDevice.ReleaseAllStateBlocks();
		GraphicsDevice.ReleaseAllFonts();
		GraphicsDevice.ReleaseAllSprites();
		GraphicsDevice.ReleaseAllAnimationModels();
		GraphicsDevice.ReleaseAllModels();
		GraphicsDevice.ReleaseAllVertexBuffers();
		GraphicsDevice.ReleaseAllEffects();
	}

	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();

private:
	// 変数宣言
	SPRITE title;
	SPRITE fadeout;
	SPRITE spy;
	SPRITE escape;
	SPRITE pict;
	float chara_x;
	float spy_x,escape_x;


	float tap;

	int sceneflag;

	MEDIA se;
	MEDIA bgm;

	FONT original;
	Color Bcolor;
	bool alpha_flag;
	int alpha;




	// 関数プロトタイプ

};
