#include "../StdAfx.h"
#include "titleScene.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool titleScene::Initialize()
{
	// TODO: Add your initialization logic here
	MediaManager.Attach(GraphicsDevice);

	title = GraphicsDevice.CreateSpriteFromFile(_T("title.png"));
	fadeout = GraphicsDevice.CreateSprite(1280, 720, PixelFormat_RGBA8888);
	fadeout->ColorFill(nullptr, Color(0, 0, 0));
	tap = 0;
	sceneflag = 0;
	se= MediaManager.CreateMediaFromFile(_T("gun.mp3"));


	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void titleScene::Finalize()
{
	// TODO: Add your finalization logic here

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int titleScene::Update()
{
    // TODO: Add your update logic here
	KeyboardBuffer keys = Keyboard->GetBuffer();
	if (keys.IsPressed(Keys_Return)) {
		se->Play();
		sceneflag = 1;
	}
	if (sceneflag == 1) {
		tap += 0.004;
		if (tap >= 1) {
			return GAME_SCENE(new GameMain);
		}
	}
	
	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void titleScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	SpriteBatch.Draw(*title, Vector3(0, 0, 0));
	SpriteBatch.Draw(*fadeout, Vector3(0, 0, 0), tap);

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
