// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include "GameScene/SelectScene.hpp"

int GameMain::time = 0;

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

	DefaultFont = GraphicsDevice.CreateDefaultFont();
	
	MediaManager.Attach(GraphicsDevice);


	bgm = MediaManager.CreateMediaFromFile(_T("bgm.mp3"));
	bgm->Play();

	


	time = 60;
	flame = 0;

	//player = GraphicsDevice.CreateSpriteFromFile(_T("Image/Chara.png"));
	skill = GraphicsDevice.CreateSpriteFromFile(_T("Image/skill.png"));

	player_spd = 5.0f;
	oni_spd = player_spd * 1.1f;

	skill_state = false;
	skill_time = 0.0f;
	skill_alpha = 1.0f;
	alpha_flag = false;

	black_flag = false;

	stun_state = false;
	stun_time = 0;

	InputDevice.CreateGamePad(1);


	wall = GraphicsDevice.CreateSpriteFromFile(_T("wall.png"));

	floar = GraphicsDevice.CreateSpriteFromFile(_T("floar.png"));


	fake = GraphicsDevice.CreateSpriteFromFile(_T("fake.png"));

	

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
	map_data_b[8] =  ("#   k                 #######  #");
	map_data_b[9] =  ("#                           #  #");
	map_data_b[10] = ("#                              #");
	map_data_b[11] = ("#   #######    ###  ##         #");
	map_data_b[12] = ("#   #     #    #     #         #");
	map_data_b[13] = ("#   #          #     #         #");
	map_data_b[14] = ("#   ###        #     #      #  #");
	map_data_b[15] = ("#          #                #  #");
	map_data_b[16] = ("#          #               o   #");
	map_data_b[17] = ("################################");

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++)
			dist[y].push_back(0);
	}

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++)
			dist2[y].push_back(0);
	}

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++)
			dist_player[y].push_back(0);
	}

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++)
			dist_AI[y].push_back(0);
	}

	/*player_pos = Vector3(50, 50, 0);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == 'p')
				player_pos = Vector3(x * 50, y * 50, 0);
		}
	}*/


	

	oni_pos = Vector3(50, 50, 0);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == 'o')
				oni_pos = Vector3(x * 50, y * 50, 0);
		}
	}

	/*fake_pos = Vector3(50, 50, 0);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == 'f')
				fake_pos = Vector3(x * 50, y * 50, 0);
		}
	}

	fake2_pos = Vector3(50, 50, 0);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			if (map_data_b[y][x] == 'k')
				fake2_pos = Vector3(x * 50, y * 50, 0);
		}
	}*/

	for (int i = 0; i < 4; i++) {
		mx_k[i] = 0;
		my_k[i] = 0;
		mx_i[i] = 0;
		my_i[i] = 0;

	}

	k_count = 10;
	j_count = 10;
	j = 0;

	k = 0;
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

	int select = SelectScene::GetSelect();

	Vector3 start_Pos[] = { Vector3(50,50,0),Vector3(150,400,0),Vector3(1000,400,0) };

	if (select == 0) {
		player_pos = start_Pos[0];
		fake_pos = start_Pos[1];
		fake2_pos = start_Pos[2];
	}
	if (select == 1) {
		player_pos = start_Pos[1];
		fake_pos = start_Pos[2];
		fake2_pos = start_Pos[0];
	}
	if (select == 2) {
		player_pos = start_Pos[2];
		fake_pos = start_Pos[0];
		fake2_pos = start_Pos[1];
	}



	prev_mx = -1;
	prev_my = -1;


	InputDevice.CreateGamePad(2);

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



int GameMain::Update()
{



	Player();
	ONI();
	AI();
	Fake();
	Fake2();

	flame++;
	if (flame == 60) {
		time -= 1;
		flame = 0;
		if (time == 0) {

			return GAME_SCENE(new clearScene);
		}
	}

	//鬼と逃げる人の当たり判定
	if ((player_pos.x + 35 < oni_pos.x + 15 || player_pos.x + 15 > oni_pos.x + 35 ||
		player_pos.y + 40 < oni_pos.y + 10 || player_pos.y + 10 > oni_pos.y + 40))
	{
	}
	else if (time >= 0)
	{
		return GAME_SCENE(new resultScene);
	}


	return 0;
}




void GameMain::ONI()
{
	KeyboardState key = Keyboard->GetState();
	GamePadState pad_1 = GamePad(0)->GetState();
	GamePadState pad_2 = GamePad(1)->GetState();

	int nx = (int)((oni_pos.x + 50) / 50);
	int ny = (int)((oni_pos.y + 50) / 50);

	if (stun_state == false)
	{
		if (key.IsKeyDown(Keys_D) || pad_1.X > 0) {
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

		else if (key.IsKeyDown(Keys_A) || pad_1.X < 0) {
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

		else if (key.IsKeyDown(Keys_S) || pad_1.Y > 0) {
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

		else if (key.IsKeyDown(Keys_W) || pad_1.Y < 0) {
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
	}

		int mx = (int)(oni_pos.x / 50);
		int my = (int)(oni_pos.y / 50);
		//脅威マップ
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


		for (int i = 3; i > 0; i--) {
			dist[my_k[i]][mx_k[i]] = 0;
			dist_player[my_k[i]][mx_k[i]] = 0;
		}
		for (int i = 3; i > 0; i--) {
			mx_k[i] = mx_k[i - 1];
			my_k[i] = my_k[i - 1];
		}


	//}
		//



		

		/*for (int y = 0; y < 18; y++) {
			for (int x = 0; x < map_data_b[y].size(); x++) {
				if (dist2[y][x] >= 0)
					dist2[y][x] = dist_player[y][x] * 0.4 + dist[y][x] * 0.6;
				else
					dist2[y][x] = 0;
			}
		}*/


}



void GameMain::Player()
{
	KeyboardState key = Keyboard->GetState();
	KeyboardBuffer key_buffer = Keyboard->GetBuffer();
	GamePadState pad_2 = GamePad(1)->GetState();
	GamePadBuffer pad_buffer = GamePad(1)->GetBuffer();

	if (key.IsKeyDown(Keys_Right) || pad_2.X > 0) {
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
		

	else if (key.IsKeyDown(Keys_Left) || pad_2.X < 0) {
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
	}

		else if (key.IsKeyDown(Keys_Down) || pad_2.Y > 0) {
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
		}

		else if (key.IsKeyDown(Keys_Up) || pad_2.Y < 0) {
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
	}


	if (black_flag == false)
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
	

	int mx = player_pos.x / 50;
	int my = player_pos.y / 50;

	if (mx != prev_mx2 || my != prev_my2) {
		max2 = FLT_MIN;
		min2 = FLT_MAX;
		for (int y = 0; y < 18; y++) {
			for (int x = 0; x < map_data_b[y].size(); x++) {
				if (map_data_b[y][x] != '#') {
					dist_player[y][x] = Vector3_Distance(player_pos, Vector3(x * 50, y * 50, 0));

					if (max2 < dist_player[y][x])
					{
						max2 = dist_player[y][x];
					}
					if (min2 > dist_player[y][x])
					{
						min2 = dist_player[y][x];
					}
				}
				else {
					dist_player[y][x] = -1;
				}
			}
		}

		normal2 = max2 - min2;
		for (int y = 0; y < 18; y++) {
			for (int x = 0; x < map_data_b[y].size(); x++) {
				if (dist_player[y][x] >= 0)
					dist_player[y][x] = 1.0 -((dist_player[y][x] - min2) / normal2);
				else
					dist_player[y][x] = 0;
			}
		}

	
		

		prev_mx2 = mx;
		prev_my2 = my;
	}

	for (int i = 3; i > 0; i--) {
		dist[my_i[i]][mx_i[i]] = 0;
		dist_player[my_i[i]][mx_i[i]] = 0;
	}
	for (int i = 3; i > 0; i--) {
		mx_i[i] = mx_i[i - 1];
		my_i[i] = my_i[i - 1];
	}

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

		k = 0;

		if (dist_AI[my - 1][mx] > max) {
			max = dist_AI[my - 1][mx];
			k = 1;
		}
		if (dist_AI[my + 1][mx] > max) {
			max = dist_AI[my + 1][mx];
			k = 2;

		}

		if (dist_AI[my][mx + 1] > max) {
			max = dist_AI[my][mx + 1];
			k = 3;

		}

		if (dist_AI[my][mx - 1] > max) {
			max = dist_AI[my][mx - 1];
			k = 4;
		}

		if (k != 0) {

				
			for (int i = 3; i > 0; i--) {
				dist[my_k[i]][mx_k[i]] = 0;
				dist_player[my_k[i]][mx_k[i]] = 0;
			}
			for (int i = 3; i > 0; i--) {
				mx_k[i] = mx_k[i - 1];
				my_k[i] = my_k[i - 1];
			}


			mx_k[0] = mx;
			my_k[0] = my;

				
			k_count = 0;
		}
	}
	
	

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


	// 鬼とデコイの当たり判定
	if ((oni_pos.x + 35 < fake_pos.x + 15 || oni_pos.x + 15 > fake_pos.x + 35 ||
		oni_pos.y + 40 < fake_pos.y + 10 || oni_pos.y + 10 > fake_pos.y + 40)) {
	}
	else if (time >= 0) {

		stun_state = true;
	}
	if (stun_state == true) {

		stun_time += 1.0f;

	}

	if (stun_time >= 120.0f) {

		stun_state = false;
		stun_time = 0.0f;
	}

	

	
	

}

void GameMain::Fake2() {

	KeyboardState key = Keyboard->GetState();


	//	if (key.IsKeyDown(Keys_Up) || key.IsKeyDown(Keys_Right) || key.IsKeyDown(Keys_Left) || key.IsKeyDown(Keys_Down)) {
	int mx = (int)(fake2_pos.x / 50);
	int my = (int)(fake2_pos.y / 50);

	float max2 = 0;


	if (j_count == 10) {


		j = 0;

		if (dist2[my - 1][mx] > max2) {
			max2 = dist2[my - 1][mx];
			j = 1;
		}
		if (dist2[my + 1][mx] > max2) {
			max2 = dist2[my + 1][mx];
			j = 2;

		}

		if (dist2[my][mx + 1] > max2) {
			max2 = dist2[my][mx + 1];
			j = 3;

		}

		if (dist2[my][mx - 1] > max2) {
			max2 = dist2[my][mx - 1];
			j = 4;
		}

		if (j != 0) {
		

			for (int i = 3; i > 0; i--) {
				dist[my_i[i]][mx_i[i]] = 0;
				dist_player[my_i[i]][mx_i[i]] = 0;
			}
			for (int i = 3; i > 0; i--) {
				mx_i[i] = mx_i[i - 1];
				my_i[i] = my_i[i - 1];
			}
			mx_i[0] = mx;
			my_i[0] = my;
			
			j_count = 0;
		}
	}

	//		}

	if (j == 1) {

		fake2_pos.y -= 5;
		j_count++;
	}
	if (j == 2) {

		fake2_pos.y += 5;
		j_count++;
	}
	if (j == 3) {
		fake2_pos.x += 5;
		j_count++;
	}

	if (j == 4) {

		fake2_pos.x -= 5;
		j_count++;
	}

	// 鬼とデコイの当たり判定
	if ((oni_pos.x + 35 < fake2_pos.x + 15 || oni_pos.x + 15 > fake2_pos.x + 35 ||
		oni_pos.y + 40 < fake2_pos.y + 10 || oni_pos.y + 10 > fake2_pos.y + 40)){
	}
	else if (time >= 0){

		stun_state = true;
	}
	if (stun_state == true){

		stun_time += 1.0f;
		
	}

		if (stun_time >= 120.0f){

			stun_state = false;
			stun_time = 0.0f;
		}
}

void GameMain::AI()
{
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++) {
			if (dist2[y][x] >= 0)
				dist2[y][x] = dist_player[y][x] * 0.4 + dist[y][x] * 0.6;
			else
				dist2[y][x] = 0;
		}
	}

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < map_data_b[y].size(); x++) {
			if (dist_AI[y][x] >= 0)
				dist_AI[y][x] = dist_player[y][x] * 0.2 + dist[y][x] * 0.8;
			else
				dist_AI[y][x] = 0;
		}
	}

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
	SpriteBatch.Draw(*fake, fake2_pos);

	SpriteBatch.Draw(*player, player_pos);

	/*for (int y = 0; y < 18; y++) {
		for (int x = 0; x < dist[y].size(); x++) {
			SpriteBatch.DrawString(DefaultFont, Vector2(x * 48, y * 16), Color(0, 0, 0), _T("%01.3f"), dist_AI[y][x]);
		}
	}*/


	//SpriteBatch.DrawString(DefaultFont, Vector2(0, 0), Color(0, 0, 0), _T("%03f"), player_pos.x);

	//SpriteBatch.DrawString(DefaultFont, Vector2(1000, 0), Color(0, 0, 0), _T("%03f"), dist[0]);
	/*for (int i = 0; i < dist.size(); i++) {
		switch (mm[i]) {
		case 1 :


	}*/

	SpriteBatch.DrawString(DefaultFont, Vector2(960, 0),
		Color(0, 0, 255), _T("TIME:%d"), time);
	

	if (skill_state == true)
	{
		SpriteBatch.Draw(*skill, Vector3(0.0f, 0.0f, -10.0f), skill_alpha);
	}



	SpriteBatch.Draw(*player, player_pos);
	SpriteBatch.Draw(*fake, fake_pos);
	


	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
