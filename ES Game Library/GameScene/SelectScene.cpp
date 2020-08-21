#include "../StdAfx.h"
#include "TemplateScene.hpp"

int SelectScene:: selectNo= 0;

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load any non-graphic
/// related content.  Calling base.Initialize will enumerate through any components
/// and initialize them as well.
/// </summary>
bool SelectScene::Initialize()
{
	// TODO: Add your initialization logic here
	selectNo = 0;
	limit = 0;
	InputDevice.CreateGamePad(1);



	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void SelectScene::Finalize()
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
int SelectScene::Update()
{
    // TODO: Add your update logic here
	KeyboardBuffer keys = Keyboard->GetBuffer();
	GamePadState pad = GamePad(0)->GetState();
	limit += 1;
	if (keys.IsPressed(Keys_Return)|| (pad.Buttons[3])) {
		return GAME_SCENE(new GameMain);
	}
	if (keys.IsPressed(Keys_Z)) {
		selectNo = 0;
	}
	if (keys.IsPressed(Keys_X)) {
		selectNo = 1;
	}
	if (keys.IsPressed(Keys_C)) {
		selectNo = 2;
	}

	


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void SelectScene::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	GraphicsDevice.EndScene();
}
