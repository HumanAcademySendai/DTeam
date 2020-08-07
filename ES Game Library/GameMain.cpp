// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	player = GraphicsDevice.CreateSpriteFromFile(_T("Image/Chara.png"));
	skill = GraphicsDevice.CreateSpriteFromFile(_T("Image/map.png"));

	player_x = 640 - 128;
	player_y = 360 - 96;
	player_spd = 8.0f;

	skill_state = false;
	skill_time = 0.0f;
	skill_alpha = 1.0f;
	alpha_flag = false;

	black_flag = false;
	ligth_flag = false;

	InputDevice.CreateGamePad(1);

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
	GamePadState pad = GamePad(0)->GetState();
	KeyboardState key = Keyboard->GetState();
	GamePadBuffer pad_buffer = GamePad(0)->GetBuffer();
	KeyboardBuffer key_buffer = Keyboard->GetBuffer();

	// 逃げる人の移動
    if (key.IsKeyDown(Keys_Right) || pad.Buttons[2] != 0)
	{
		player_x += player_spd;
	}
	if (key.IsKeyDown(Keys_Left) || pad.Buttons[0] != 0)
	{
		player_x -= player_spd;
	}

	if (key.IsKeyDown(Keys_Down) || pad.Buttons[1] != 0)
	{
		player_y +=player_spd;
	}
	if (key.IsKeyDown(Keys_Up) || pad.Buttons[3] != 0)
	{
		player_y -= player_spd;
	}

	// 逃げる人のスキル(暗転)
	if(black_flag == false)
	{
		if (key_buffer.IsPressed(Keys_Space) || pad_buffer.IsPressed(GamePad_Button6))
		{
			skill_state = true;
			alpha_flag = true;
			black_flag = true;
		}
	}

	if (skill_state == true)
	{
		skill_time += 1.0f;

		if (skill_time > 60.0f)
		{
			skill_alpha -= 0.008f;
		}

		if (skill_alpha < 0.0f)
		{
			skill_state = false;
			skill_time = 0.0f;
			skill_alpha = 1.0f;
		}
	}

	else if (skill_time < 0)
	{
		skill_state = false;
		skill_time = 0.0f;
		alpha_flag = false;
		skill_alpha = 1.0f;
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

	SpriteBatch.Draw(*player, Vector3(player_x, player_y, 0.0f));

	if (skill_state == true)
	{
		SpriteBatch.Draw(*skill, Vector3(0.0f, 0.0f, -10.0f), skill_alpha);
	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
