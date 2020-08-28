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
	void Player();
	void Fake();
	void Fake2();
	void Fake3();
	void Fake4();
	void AI();
	cstring map_data_b[18];
	FONT newfont;

public:
	static int GetTime() { return time; }
	
private:
	// ïœêîêÈåæ

	static int time;

	FONT original;

	float flame;
	//player
	SPRITE player;
	SPRITE playerwalk;
	SPRITE playerwin;
	Vector3 player_pos;
	float p_flame_x,p_flame_y;
	int p_walk_flag;
	float player_spd;
	float player_state;
	int player_count;
	float down_flame;

	//skil
	SPRITE skill;
	bool skill_state;
	float skill_time;
	float skill_alpha;
	bool alpha_flag;
	bool fake_flag;
	int abc;
	bool black_flag;
	float invisible_state;
	float invisible_time;
	float invisible_alpha;
	float randam_skil;
	float randam[5];
	float skil_time;
	float âzëO;
	
	//oni
	SPRITE oni;
	Vector3 oni_pos;
	float oni_alpha;
	float oni_spd;
	float stun_time;
	float oni_count;
	bool stun_state;

	SPRITE onipunch;
	float oni_flame_x, oni_flame_y;
	float punch_state;

	int oni_state;
	float win_flame;
	float win_time;

	SPRITE lose;
	float lose_flame;
	float lose_time;

	// ä÷êîêÈåæ
	SPRITE wall;
	SPRITE floar;
	SPRITE fake;
	SPRITE bg;
	SPRITE ton;
	SPRITE down;
	SPRITE oniwin;
	SPRITE isu;
	Vector3 change;
	Color cl;
	float anime;

	//direction
	float direc;
	float direc2;
	float direc3;
	float direc4;
	float direc5;
	float direc6;
	

	float a_alfa;
	
	int f;
	float speed = 5;
	//AI
	Vector3 fake_pos;
	Vector3 fake2_pos;
	Vector3 fake3_pos;
	Vector3 fake4_pos;
	int k_count;
	int k;
	int j;
	int j_count;
	int h, h_count;
	int g, g_count;
	int a,b;
	int AI_count;

	MEDIA bgm;
	MEDIA skil;
	MEDIA mission;
	SOUND se;

	MEDIA skillse;
	MEDIA stunse;


	std::vector<float> dist[18];
	std::vector<float> dist2[18];
	std::vector<float> dist3[18];
	std::vector<float> dist4[18];
	std::vector<float> dist_player[18];
	std::vector<float> dist_AI[18];

	// ä÷êîêÈåæ
	/*string map_data[18];*/
	float max,max2;
	float min, min2;
	float normal;
	float normal2;
	float sw_f = 0;
	
	

	int mx_k[4],my_k[4];
	int  mx_i[4], my_i[4];
	int  mx_h[4], my_h[4];
	int  mx_g[4], my_g[4];

	int prev_mx, prev_my;
	int prev_mx2, prev_my2;

	int pad2_direction;
	int pad_direction;
};
