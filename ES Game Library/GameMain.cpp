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
	//GameTimer.SetFPS(10);
	//int cells[MAZE_WIDTH][MAZE_HEIGHT];

	wall = GraphicsDevice.CreateSpriteFromFile(_T("wall.png"));

	floar = GraphicsDevice.CreateSpriteFromFile(_T("floar.png"));

	oni = GraphicsDevice.CreateSpriteFromFile(_T("player.png"));

	fake = GraphicsDevice.CreateSpriteFromFile(_T("fake.png"));

	map_data_b[0] = ("################################");
	map_data_b[1] = ("#p           #     #          f#");
	map_data_b[2] = ("#   #        #     #     ####  #");
	map_data_b[3] = ("#   #     #                    #");
	map_data_b[4] = ("#   ###   #                    #");
	map_data_b[5] = ("#     #   #  ##  ###  #######  #");
	map_data_b[6] = ("#     #  ##        #           #");
	map_data_b[7] = ("#                              #");
	map_data_b[8] = ("#                     #######  #");
	map_data_b[9] = ("#                           #  #");
	map_data_b[10] = ("#                              #");
	map_data_b[11] = ("#   #######    ###  ##         #");
	map_data_b[12] = ("#   #     #    #     #         #");
	map_data_b[13] = ("#   #          #     #         #");
	map_data_b[14] = ("#   ###        #     #      #  #");
	map_data_b[15] = ("#          #                #  #");
	map_data_b[16] = ("#          #                   #");
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
			if (map_data_b[y][x] == 'f')
				fake_pos = Vector3(x * 50, y * 50, 0);
		}
	}

	//for (int y = 0; y < 18; y++) {
	//	for (int x = 0; x < 32; x++) {
	//		if (map_data_b[y][x] == ' ')
	//			dist.push_back(Vector3_Distance(player_pos, Vector3(x * 50, y * 50, 0)));


	//	}
	//}

	//max = dist[0];
	//min = dist[0];
	//normal = 0;

	//for (int i = 0; i < dist.size(); i++) {

	//	if (max < dist[i])
	//	{
	//		max = dist[i];
	//	}
	//	if (min > dist[i])

	//	{
	//		min = dist[i];
	//	}
	//}


	std::ifstream infile("map.txt");
	std::string filename;

	//int i = 0;
	//while (true) {
	//	getline(infile, filename);
	//	if (infile.eof())
	//		break;
	//	map_data[i] = filename;
	//	i++;
	//}

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

	if (key.IsKeyDown(Keys_Right)) {
		oni_pos.x += speed;

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
	if (key.IsKeyDown(Keys_Left)) {
		oni_pos.x -= speed;

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
		/*	if ((int)player_pos.x % 50 == 0) {
				if (map_data_b[my][mx - 1] != '#')
					player_pos.x -= 5;
			}
			else {
				if (map_data_b[my][mx] != '#')
					player_pos.x -= 5;
			}*/

	}
	if (key.IsKeyDown(Keys_Down)) {
		oni_pos.y += speed;

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
		/*if ((int)player_pos.y % 50 == 0) {
			if (map_data_b[my + 1][mx] != '#')
				player_pos.y += 50;
		}
		else {
			if (map_data_b[my][mx] != '#')
				player_pos.y += 50;
		}*/

	}
	if (key.IsKeyDown(Keys_Up)) {
		oni_pos.y -= speed;

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
		/*if ((int)player_pos.y % 50 == 0) {
			if (map_data_b[my - 1][mx] != '#')
				player_pos.y -= 50;
		} else {
			if (map_data_b[my][mx] != '#')
				player_pos.y -= 50;
		}*/
	}

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
	int k = 0;
	float max = 0;
	float k_count = 0;
	//		if (dist[my][mx] != 0) {

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

	//		}

	if (k == 1) {

		fake_pos.y -= 50;

	}
	if (k == 2) {

		fake_pos.y += 50;

	}
	if (k == 3) {

		fake_pos.x += 50;

	}
	if (k == 4) {

		fake_pos.x -= 50;

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

	SpriteBatch.Draw(*oni, oni_pos);

	SpriteBatch.Draw(*fake, fake_pos);

	/*for (int y = 0; y < 18; y++) {
		for (int x = 0; x < dist[y].size(); x++) {
			SpriteBatch.DrawString(DefaultFont, Vector2(x * 48, y * 16), Color(0, 0, 0), _T("%01.3f"), dist[y][x]);
		}
	}*/


	//SpriteBatch.DrawString(DefaultFont, Vector2(0, 0), Color(0, 0, 0), _T("%03f"), player_pos.x);

	//SpriteBatch.DrawString(DefaultFont, Vector2(1000, 0), Color(0, 0, 0), _T("%03f"), dist[0]);
	/*for (int i = 0; i < dist.size(); i++) {
		switch (mm[i]) {
		case 1 :


	}*/
	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
