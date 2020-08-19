// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include <fstream>
#define MAZE_WIDTH 32
#define MAZE_HEIGHT 18
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
	time = 120;
	flame = 0;

	//player = GraphicsDevice.CreateSpriteFromFile(_T("Image/Chara.png"));
	skill = GraphicsDevice.CreateSpriteFromFile(_T("Image/skill.png"));

	player_spd = 7.0f;
	oni_spd = player_spd * 1.2f;

	skill_state = false;
	skill_time = 0.0f;
	skill_alpha = 1.0f;
	alpha_flag = false;

	black_flag = false;
	
	InputDevice.CreateGamePad(1);

	//GameTimer.SetFPS(10);
	//int cells[MAZE_WIDTH][MAZE_HEIGHT];

	wall = GraphicsDevice.CreateSpriteFromFile(_T("wall.png"));

	floar = GraphicsDevice.CreateSpriteFromFile(_T("floar.png"));

	player = GraphicsDevice.CreateSpriteFromFile(_T("player.png"));

	oni = GraphicsDevice.CreateSpriteFromFile(_T("oni.png"), Color(255, 255, 255));

	map_data_b[0] =  ("################################");
	map_data_b[1] =  ("#p           #     #          f#");
	map_data_b[2] =  ("#   #        #     #     ####  #");
	map_data_b[3] =  ("#   #     #                    #");
	map_data_b[4] =  ("#   ###   #                    #");
	map_data_b[5] =  ("#     #   #  ##  ###  #######  #");
	map_data_b[6] =  ("#     #  ##        #           #");
	map_data_b[7] =  ("#                              #");
	map_data_b[8] =  ("#                     #######  #");
	map_data_b[9] =  ("#                           #  #");
	map_data_b[10] = ("#                              #");
	map_data_b[11] = ("#   #######    ###  ##         #");
	map_data_b[12] = ("#   #     #    #     #         #");
	map_data_b[13] = ("#   #          #     #         #");
	map_data_b[14] = ("#   ###        #     #      #  #");
	map_data_b[15] = ("#          #                #  #");
	map_data_b[16] = ("#          #               o#  #");
	map_data_b[17] = ("################################");

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++)
			dist[y].push_back(0);
	}

	oni_pos = Vector3(50, 50, 0);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == 'p')
				oni_pos = Vector3(x * 50, y * 50, 0);
		}
	}

	fake_pos = Vector3(50, 50, 0);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == 'o')
				oni_pos = Vector3(x * 50, y * 50, 0);
		}
	}
			if (map_data_b[y][x] == 'f')
				fake_pos = Vector3(x * 50, y * 50, 0);
		}
	}

	k_count = 10;
	k = 0;
	//for (int y = 0; y < 18; y++) {
	//	for (int x = 0; x < 32; x++) {
	//		if (map_data_b[y][x] == ' ')
	//			dist.push_back(Vector3_Distance(player_pos, Vector3(x * 50, y * 50, 0)));


		if (max < dist[i])
		{
			max = dist[i];
		}
		if (min > dist[i])

	prev_mx = -1;
	prev_my = -1;

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

int GameMain::time = 0;

void GameMain::ONI()
{
	KeyboardState key = Keyboard->GetState();

	int nx = (int)((oni_pos.x + 50) / 50);
	int ny = (int)((oni_pos.y + 50) / 50);

	//if (key.IsKeyUp(Keys_A)){
		if (key.IsKeyDown(Keys_D)) {
			oni_pos.x += oni_spd;

			int mx = (int)(oni_pos.x / 50);
			int my = (int)(oni_pos.y / 50);

			if (map_data_b[my][mx + 1] == '#')
				oni_pos.x = mx * 50;


			int py = (int)oni_pos.y % 50;
			if (py != 0) {
				if (py < 10)
					oni_pos.y = ((int)oni_pos.y / 50 + 0) * 50;
				else if (py > 40)
					oni_pos.y = ((int)oni_pos.y / 50 + 1) * 50;
				else if (map_data_b[my + 1][mx + 1] == '#')
					oni_pos.x = mx * 50;
			}
		}
	//}

	//if (key.IsKeyUp(Keys_D)) {
		else if (key.IsKeyDown(Keys_A)) {
			oni_pos.x -= oni_spd;

				int mx = (int)(oni_pos.x / 50);
				int my = (int)(oni_pos.y / 50);

				if (map_data_b[my][mx] == '#')
					oni_pos.x = (mx + 1) * 50;


				int py = (int)oni_pos.y % 50;
			if (py != 0) {
				if (py < 10)
					oni_pos.y = ((int)oni_pos.y / 50 + 0) * 50;
				else if (py > 40)
					oni_pos.y = ((int)oni_pos.y / 50 + 1) * 50;
				else if (map_data_b[my + 1][mx] == '#')
					oni_pos.x = (mx + 1) * 50;
			}
		}
	//}

	//if (key.IsKeyUp(Keys_D) && key.IsKeyUp(Keys_A)) {
		else if (key.IsKeyDown(Keys_S)) {
			oni_pos.y += oni_spd;

			int mx = (int)(oni_pos.x / 50);
			int my = (int)(oni_pos.y / 50);

			if (map_data_b[my + 1][mx] == '#')
				oni_pos.y = my * 50;


			int px = (int)oni_pos.x % 50;
			if (px != 0) {
				if (px < 10)
					oni_pos.x = ((int)oni_pos.x / 50 + 0) * 50;
				else if (px > 40)
					oni_pos.x = ((int)oni_pos.x / 50 + 1) * 50;
				else if (map_data_b[my + 1][mx + 1] == '#')
					oni_pos.y = my * 50;
			}
		}
	//}

	//if (key.IsKeyUp(Keys_D) && key.IsKeyUp(Keys_A)) {
		else if (key.IsKeyDown(Keys_W)) {
			oni_pos.y -= oni_spd;

			int mx = (int)(oni_pos.x / 50);
			int my = (int)(oni_pos.y / 50);

			if (map_data_b[my][mx] == '#')
				oni_pos.y = (my + 1) * 50;


			int px = (int)oni_pos.x % 50;
			if (px != 0) {
				if (px < 10)
					oni_pos.x = ((int)oni_pos.x / 50 + 0) * 50;
				else if (px > 40)
					oni_pos.x = ((int)oni_pos.x / 50 + 1) * 50;
				else if (map_data_b[my][mx + 1] == '#')
					oni_pos.y = (my + 1) * 50;
			}
		}
	//}
}

void GameMain::kabe()
{
}

void GameMain::cpu1()
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
	KeyboardState key = Keyboard->GetState();
	// TODO: Add your update logic here

	int nx = (int)((oni_pos.x + 50) / 50);
	int ny = (int)((oni_pos.y + 50) / 50);

	//if (key.IsKeyUp(Keys_Down) && key.IsKeyUp(Keys_Left) && key.IsKeyUp(Keys_Up)) {
		if (key.IsKeyDown(Keys_Right)) {
			player_pos.x += player_spd;

			int mx = (int)(player_pos.x / 50);
			int my = (int)(player_pos.y / 50);

			if (map_data_b[my][mx + 1] == '#')
				player_pos.x = mx * 50;


			int py = (int)player_pos.y % 50;
			if (py != 0) {
				if (py < 10)
					player_pos.y = ((int)player_pos.y / 50 + 0) * 50;
				else if (py > 40)
					player_pos.y = ((int)player_pos.y / 50 + 1) * 50;
				else if (map_data_b[my + 1][mx + 1] == '#')
					player_pos.x = mx * 50;
			}
		}
	//}
	/*if ((int)player_pos.x % 50 == 0) {
		if (map_data_b[my][mx + 1] != '#') {
			player_pos.x += 5;
		}
	}
	else {
		if (map_data_b[my][mx] != '#')
			player_pos.x += 5;
	}
}*/
	//if (key.IsKeyUp(Keys_Right) && key.IsKeyUp(Keys_Down) && key.IsKeyUp(Keys_Up)) {
		else if (key.IsKeyDown(Keys_Left)) {
			player_pos.x -= player_spd;

			int mx = (int)(player_pos.x / 50);
			int my = (int)(player_pos.y / 50);

			if (map_data_b[my][mx] == '#')
				player_pos.x = (mx + 1) * 50;


			int py = (int)player_pos.y % 50;
			if (py != 0) {
				if (py < 10)
					player_pos.y = ((int)player_pos.y / 50 + 0) * 50;
				else if (py > 40)
					player_pos.y = ((int)player_pos.y / 50 + 1) * 50;
				else if (map_data_b[my + 1][mx] == '#')
					player_pos.x = (mx + 1) * 50;
			}
			/*	if ((int)player_pos.x % 50 == 0) {
					if (map_data_b[my][mx - 1] != '#')
						player_pos.x -= 5;
				}
				else {
					if (map_data_b[my][mx] != '#')
						player_pos.x -= 5;
				}*/

		}
	//}

	//if (key.IsKeyUp(Keys_Right) && key.IsKeyUp(Keys_Left) && key.IsKeyUp(Keys_Up)) {
		else if (key.IsKeyDown(Keys_Down)) {
			player_pos.y += player_spd;

			int mx = (int)(player_pos.x / 50);
			int my = (int)(player_pos.y / 50);

			if (map_data_b[my + 1][mx] == '#')
				player_pos.y = my * 50;


			int px = (int)player_pos.x % 50;
			if (px != 0) {
				if (px < 10)
					player_pos.x = ((int)player_pos.x / 50 + 0) * 50;
				else if (px > 40)
					player_pos.x = ((int)player_pos.x / 50 + 1) * 50;
				else if (map_data_b[my + 1][mx + 1] == '#')
					player_pos.y = my * 50;
			}
			/*if ((int)player_pos.y % 50 == 0) {
				if (map_data_b[my + 1][mx] != '#')
					player_pos.y += 50;
			}
			else {
				if (map_data_b[my][mx] != '#')
					player_pos.y += 50;
			}*/

		}
	//}

	//if (key.IsKeyUp(Keys_Right) && key.IsKeyUp(Keys_Left) && key.IsKeyUp(Keys_Down)) {
		else if (key.IsKeyDown(Keys_Up)) {
			player_pos.y -= player_spd;

			int mx = (int)(player_pos.x / 50);
			int my = (int)(player_pos.y / 50);

			if (map_data_b[my][mx] == '#')
				player_pos.y = (my + 1) * 50;


			int px = (int)player_pos.x % 50;
			if (px != 0) {
				if (px < 10)
					player_pos.x = ((int)player_pos.x / 50 + 0) * 50;
				else if (px > 40)
					player_pos.x = ((int)player_pos.x / 50 + 1) * 50;
				else if (map_data_b[my][mx + 1] == '#')
					player_pos.y = (my + 1) * 50;
			}
			/*if ((int)player_pos.y % 50 == 0) {
				if (map_data_b[my - 1][mx] != '#')
					player_pos.y -= 50;
			} else {
				if (map_data_b[my][mx] != '#')
					player_pos.y -= 50;
			}*/
		}
	//}

	//Vector3 pos = player_pos;
	//
	//if (key.IsKeyDown(Keys_Right))
	//{
	//	pos = Vector3_Right;
	//	player_pos += Vector3_Normalize(pos) * 5;
	//
	//}
	//if (key.IsKeyDown(Keys_Left))
	//{
	//	pos = -Vector3_Right;
	//	player_pos += Vector3_Normalize(pos) * 5;
	//
	//}
	//if (key.IsKeyDown(Keys_Up))
	//{
	//	pos = -Vector3_Up;
	//	player_pos += Vector3_Normalize(pos) * 5;
	//
	//}
	//if (key.IsKeyDown(Keys_Down))
	//{
	//	pos = Vector3_Up;
	//	player_pos += Vector3_Normalize(pos) * 5;
	//
	//}

	//	dist.clear();
	int mx = oni_pos.x / 50;
	int my = oni_pos.y / 50;
	if (mx != prev_mx || my != prev_my) {
		max = FLT_MIN;
		min = FLT_MAX;
		for (int y = 0; y < 18; y++) {
			for (int x = 0; x < map_data_b[y].size(); x++) {
				if (map_data_b[y][x] != '#') {
					dist[y][x] = Vector3_Distance(oni_pos, Vector3(x * 50, y * 50, 0));

					if (max < dist[y][x])
					{
						max = dist[y][x];
					}
					if (min > dist[y][x])
					{
						min = dist[y][x];
					}
				}
				else {
					dist[y][x] = -1;
				}
			}
		}

		normal = max - min;
		for (int y = 0; y < 18; y++) {
			for (int x = 0; x < map_data_b[y].size(); x++) {
				if (dist[y][x] >= 0)
					dist[y][x] = ((dist[y][x] - min) / normal);
				else
					dist[y][x] = 0;
			}
		}

		prev_mx = mx;
		prev_my = my;
	}

	//for (int i = 0; i < dist.size(); i++) {
	//	dist[i] = 1.0 - (dist[i] - min) / normal;
	//	
	//}
	//for (int i = 0; i < dist.size(); i++) {
	//	(int)mm[i] = dist[i] * 10;
	//}
	//for (int y = 0; y < 18; y++) {
	//	for (int x = 0; x < 32; x++) {
	//		if (map_data_b[y][x] == ' ') {
	//			for (int i = 0; i < dist.size(); i++)
	//				map_data[y][x] = mm[i];

	//		}
	//	}
	//}
	//if (key.IsKeyDown(Keys_Up)|| key.IsKeyDown(Keys_Right)|| key.IsKeyDown(Keys_Left)|| key.IsKeyDown(Keys_Down)) {
	/*{
		int mx = (int)(fake_pos.x / 50);
		int my = (int)(fake_pos.y / 50);


		if (sw_f == 0) {
			if (map_data_b[my + 1][mx] != '#')
				fake_pos.y += 5;
			else {
				sw_f = 1;
			}
		}

		if (sw_f == 1) {
			if (map_data_b[my][mx] != '#') {
				fake_pos.y -= 5;
			}
			else {
				sw_f = 0;
			}
		}
	}*/

	Fake();


	return 0;
}

void GameMain::Fake()
{
	KeyboardState key = Keyboard->GetState();

	//	if (key.IsKeyDown(Keys_Up) || key.IsKeyDown(Keys_Right) || key.IsKeyDown(Keys_Left) || key.IsKeyDown(Keys_Down)) {
	int mx = (int)(fake_pos.x / 50);
	int my = (int)(fake_pos.y / 50);
	int prev_mx = 0;
	int prev_my = 0;
	
	float max = 0;
	
	
		if (k_count == 10) {
	Player();
	ONI();

	GamePadState pad = GamePad(0)->GetState();
	KeyboardState key = Keyboard->GetState();
	GamePadBuffer pad_buffer = GamePad(0)->GetBuffer();
	KeyboardBuffer key_buffer = Keyboard->GetBuffer();

	// ì¶Ç∞ÇÈêlÇÃà⁄ìÆ
   

			if (dist[my - 1][mx] > max) {
				max = dist[my - 1][mx];
				k = 1;
			}
			if (dist[my + 1][mx] > max) {
				max = dist[my + 1][mx];
				k = 2;

			}

			if (dist[my][mx + 1] > max) {
				max = dist[my][mx + 1];
				k = 3;

			}

			if (dist[my][mx - 1] > max) {
				max = dist[my][mx - 1];
				k = 4;
			}

			if (k != 0)
				dist[my][mx] = 0;

			k_count = 0;
		}
	
	//		}

	if (k == 1) {

		fake_pos.y -= 5;
		k_count++;
	}
	if (k == 2) {

		fake_pos.y += 5;
		k_count++;
	}
	if (k == 3) {

		fake_pos.x += 5;
		k_count++;
	}
	if (k == 4) {

		fake_pos.x -= 5;
		k_count++;
	}


	//ãSÇ∆ì¶Ç∞ÇÈêlÇÃìñÇΩÇËîªíË
	if ((player_pos.x + 35 < oni_pos.x + 15 || player_pos.x + 15 > oni_pos.x + 35 ||
		player_pos.y + 40 < oni_pos.y + 10 || player_pos.y + 10 > oni_pos.y + 40))
	{
	}
	else if (time >= 0)
	{
		return GAME_SCENE(new resultScene);
	}

	//		}

	//	}
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

	//for (int y = 0; y < 18; y++) {
	//	/*for (int x = 0; x < 32; x++)*/ {
	//		if (map_data[y] == "0") {
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == '#') {
				SpriteBatch.Draw(*wall, Vector3(x * 50, y * 50, 0), RectWH(0, 0, 50, 50));
			}
			else {

				SpriteBatch.Draw(*floar, Vector3(x * 50, y * 50, 0), RectWH(0, 0, 50, 50));


			}
		}
	}



	SpriteBatch.Draw(*fake, fake_pos);

	SpriteBatch.Draw(*oni, oni_pos);

	if (skill_state == true)
	{
		SpriteBatch.Draw(*skill, Vector3(0.0f, 0.0f, -10.0f), skill_alpha);
	}

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
