#pragma once

#include "ESGLib.h"
#include "GameScene/GameScene.hpp"

class GameMain : public CGameScene {
public:
	GameMain()
	{
//		ContentRootDirectory(_T("Content"));
	}

	virtual ~GameMain()
	{
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

		Finalize();
	}

public:
	virtual bool Initialize();

	virtual int  Update();
	virtual void Draw();

private:
	void Finalize();
	FONT DefaultFont;
	void ONI();
	void kabe();
	void cpu1();
	void cpu2();
	void Player();
	cstring map_data_b[18];


public:
	static int GetTime() { return time; }
	
private:
	// ïœêîêÈåæ
	static int time;

	FONT original;

	float flame;

	SPRITE player;
	float player_spd;

	SPRITE skill;
	bool skill_state;
	float skill_time;
	float skill_alpha;
	bool alpha_flag;

	bool black_flag;

	SPRITE oni;
	Vector3 oni_pos;
	float oni_spd;

	// ä÷êîêÈåæ
	SPRITE wall;
	SPRITE floar;
	//SPRITE player;
	Vector3 player_pos;
	Color cl;


	std::vector<float> dist;

	// ä÷êîêÈåæ
	/*string map_data[18];*/
	float max;
	float min;
	float normal;
	int mm[408];

};
