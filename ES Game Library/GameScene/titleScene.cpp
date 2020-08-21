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

	pict= GraphicsDevice.CreateSpriteFromFile(_T("pict.png"));
	chara_x = 0;
	spy = GraphicsDevice.CreateSpriteFromFile(_T("Spy.png"));
	escape = GraphicsDevice.CreateSpriteFromFile(_T("escape.png"));
	spy_x = -1600;
	escape_x = 1600;

	alpha = 0;
	alpha_flag = true;




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
	GamePadBuffer pad = GamePad(0)->GetBuffer();

	if (alpha_flag == true && alpha >= 255) {
		alpha_flag = false;
	}
	if (alpha_flag == false && alpha <= 0) {
		alpha_flag = true;
	}

	if (alpha_flag) {
		alpha += 3;
	}
	else {
		alpha -= 3;
	}

	spy_x += 30;
	escape_x -= 30;
	if (spy_x >= 0) {
		spy_x = 0;
		escape_x = 0;
	}

	if (keys.IsPressed(Keys_Return)) {
		//se->Play();
		sceneflag = 1;
	}
	if (sceneflag == 1) {
		chara_x += 45;
		if (chara_x>=1400){
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
	SpriteBatch.Draw(*pict, Vector3(chara_x, 600, 0));

	SpriteBatch.Draw(*spy, Vector3(spy_x, 0, 0));
	SpriteBatch.Draw(*escape, Vector3(escape_x, 0, 0));


	SpriteBatch.DrawString(original, _T("PRESS ENTER "), Vector2(550, 750),
		Color(200, 0, 50,alpha) );

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
