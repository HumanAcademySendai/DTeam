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
	InputDevice.CreateGamePad(1);

	title = GraphicsDevice.CreateSpriteFromFile(_T("title.png"));
	fadeout = GraphicsDevice.CreateSprite(1600, 900, PixelFormat_RGBA8888);
	fadeout->ColorFill(nullptr, Color(0, 0, 0));
	tap = 0;
	sceneflag = 0;
	se= MediaManager.CreateMediaFromFile(_T("click.mp3"));
	original= GraphicsDevice.CreateSpriteFont(_T("georgia"), 80);


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
	GamePadState pad = GamePad(0)->GetState();

	if (keys.IsPressed(Keys_Return)|| (pad.Buttons[3])) {
		se->Play();
		sceneflag = 1;
	}
	if (sceneflag == 1) {
		tap += 0.004;
		if (tap >= 1) {
			return GAME_SCENE(new SelectScene);
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

	//SpriteBatch.DrawString(original, Vector2(550, 800),
		//Color(255, 0, 100), _T("PRESS ENTER TO START"));

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
