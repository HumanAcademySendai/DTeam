// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include "GameScene/SelectScene.hpp"

int GameMain::time = 0;

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));
	MediaManager.Attach(GraphicsDevice);

	DefaultFont = GraphicsDevice.CreateDefaultFont();
	
	original= GraphicsDevice.CreateSpriteFont(_T("georgia"), 50);
	bgm = MediaManager.CreateMediaFromFile(_T("bgm.mp3"));
	bgm->Play();

	player = GraphicsDevice.CreateSpriteFromFile(_T("akuma.png"));
	fake = GraphicsDevice.CreateSpriteFromFile(_T("akuma2.png"));


	time = 60;
	flame = 0;

	int select = SelectScene::GetSelect();
	Vector3 start_Pos[] = { Vector3(50,50,0), Vector3(500,50,0), Vector3(50,400,0) };

	if (select == 0) {
		player_pos = start_Pos[select];
		fake_pos = start_Pos[1];
		fake2_pos = start_Pos[2];
	}
	if (select == 1) {
		player_pos = start_Pos[select];
		fake_pos = start_Pos[2];
		fake2_pos = start_Pos[0];
	}
	if (select == 2) {
		player_pos = start_Pos[select];
		fake_pos = start_Pos[0];
		fake2_pos = start_Pos[1];
	}





	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here

}

void GameMain::oni()
{
}

void GameMain::kabe()
{
}

void GameMain::cpu1()
{
}

void GameMain::cpu2()
{
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here
	KeyboardBuffer keys = Keyboard->GetBuffer();
	flame++;
	if (flame == 60) {
		time -= 1;
		flame = 0;
		if (time == 55) {
			return GAME_SCENE(new clearScene);
		}
	}
	if (keys.IsPressed(Keys_Return)) {
		return GAME_SCENE(new resultScene);
	}


	return 0;
}


/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();
	SpriteBatch.DrawString(original, Vector2(960, 0),
		Color(0, 0, 255), _T("TIME:%d"), time);

	SpriteBatch.Draw(*player, player_pos);
	SpriteBatch.Draw(*fake, fake_pos);
	


	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
