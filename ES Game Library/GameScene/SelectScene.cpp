#include "../StdAfx.h"
#include "SelectScene.hpp"

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
	MediaManager.Attach(GraphicsDevice);
	selectNo = 0;
	InputDevice.CreateGamePad(2);
	bg = GraphicsDevice.CreateSpriteFromFile(_T("select.png"));
	bg2 = GraphicsDevice.CreateSpriteFromFile(_T("select2.png"));
	bg3 = GraphicsDevice.CreateSpriteFromFile(_T("select3.png"));

	bgm = MediaManager.CreateMediaFromFile(_T("bgm_maoudamashii_cyber29.mp3"));
	bgm->Play();
	state = 0;

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
	GamePadState pad_2 = GamePad(1)->GetState();

	if (state == 0) {
		if (keys.IsPressed(Keys_Return) || pad_2.Buttons[9]) {
			state = 1;
		}
	}
	else if (state == 1) {
		if (keys.IsPressed(Keys_Return) || pad_2.Buttons[9]) {
			state = 2;
		}
	}
	else if (state == 2) {
		if (s_s == 1) {
		if (keys.IsPressed(Keys_Return) || pad_2.Buttons[9]) {

			return GAME_SCENE(new GameMain);
		}
	}
	}
	if (keys.IsPressed(Keys_M) || pad_2.Buttons[0]) {
		selectNo = 0;
		s_s = 1;
	}
	if (keys.IsPressed(Keys_K) || pad_2.Buttons[1]) {
		selectNo = 1;
		s_s = 1;
	}
	if (keys.IsPressed(Keys_O) || pad_2.Buttons[2]) {
		selectNo = 2;
		s_s = 1;
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
	SpriteBatch.Begin();

	if (state == 0) {
		SpriteBatch.Draw(*bg, Vector3(0, 0, 0));
	}
	else if(state == 1){
		SpriteBatch.Draw(*bg2, Vector3(0, 0, 0));
	}
	else if (state == 2) {
		SpriteBatch.Draw(*bg3, Vector3(0, 0, 0));
	}
	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
