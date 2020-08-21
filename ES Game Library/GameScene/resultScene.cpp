#include "../StdAfx.h"
#include "resultScene.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool resultScene::Initialize()
{
	// TODO: Add your initialization logic here
	InputDevice.CreateGamePad(1);
	owari= GraphicsDevice.CreateSpriteFromFile(_T("tukamaru.png"));
	original = GraphicsDevice.CreateSpriteFont(_T("georgia"), 50);
	InputDevice.CreateGamePad(1);
	InputDevice.CreateGamePad(2);

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void resultScene::Finalize()
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
int resultScene::Update()
{
    // TODO: Add your update logic here
	KeyboardBuffer keys = Keyboard->GetBuffer();
	GamePadBuffer pad_2 = GamePad(1)->GetBuffer();
	if (keys.IsPressed(Keys_Return)||pad_2.IsPressed(GamePad_Button10)) 
	{
		return GAME_SCENE(new titleScene);
	}


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void resultScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	SpriteBatch.Draw(*owari, Vector3(0, 0, 0));

	SpriteBatch.DrawString(original, Vector2(960, 0),
		Color(0, 0, 255), _T("Žc‚è:%d"), GameMain::GetTime());



	SpriteBatch.End();


	GraphicsDevice.EndScene();
}
