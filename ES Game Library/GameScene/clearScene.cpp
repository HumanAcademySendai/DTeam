#include "../StdAfx.h"
#include "TemplateScene.hpp"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool clearScene::Initialize()
{
	// TODO: Add your initialization logic here
	InputDevice.CreateGamePad(1);
	clear = GraphicsDevice.CreateSpriteFromFile(_T("nigekiri.png"));
	InputDevice.CreateGamePad(2);

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void clearScene::Finalize()
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
int clearScene::Update()
{
    // TODO: Add your update logic here
	GamePadBuffer pad = GamePad(0)->GetBuffer();
	KeyboardBuffer keys = Keyboard->GetBuffer();
	GamePadState pad_2 = GamePad(1)->GetState();

	if (keys.IsPressed(Keys_Return)||pad_2.Buttons[9]) {
		return GAME_SCENE(new titleScene);
	}


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void clearScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	SpriteBatch.Begin();
	SpriteBatch.Draw(*clear, Vector3(0, 0, 0));
	


	SpriteBatch.End();


	GraphicsDevice.EndScene();
}
