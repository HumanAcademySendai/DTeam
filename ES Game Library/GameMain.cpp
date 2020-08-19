// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

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
	DefaultFont = GraphicsDevice.CreateDefaultFont();
	
	original= GraphicsDevice.CreateSpriteFont(_T("georgia"), 50);
	bgm = MediaManager.CreateMediaFromFile(_T("bgm.mp3"));
	bgm->Play();

	time = 60;
	flame = 0;


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

void GameMain::player()
{
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


	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
