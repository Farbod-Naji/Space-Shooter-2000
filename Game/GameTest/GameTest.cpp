//------------------------------------------------------------------------
// GameTest.cpp
#include "stdafx.h"

#include <windows.h> 
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>

#include "app\app.h"

#include "Farbod's Code/Map/Map.h"
#include "Farbod's Code/Points_Vectors.h"
#include "Farbod's Code/Map/Tile.h"

#include "Farbod's Code/Object.h"

#include "Farbod's Code/Ships/PlayerShip.h"
#include "Farbod's Code/Ships/PlayerBullets.h"

#include "Farbod's Code/Ships/EnemyShips.h"
#include "Farbod's Code/Ships/EnemyBullet.h"

#define NumOfDivisions 6

// --------------------------------

static Map* map;

static PlayerShip* player = new PlayerShip;

static std::vector <PlayerBullets*> playerBullets;

static std::vector <EnemyShips*> enemyShips;

static std::vector <EnemyBullet*> enemyBullets;

// -------------------------------

static float g_deathTimer = 0.0f;

static float g_enemySpawnTime = 2.5f;

static float g_enemytimer = 0.0f;

unsigned int g_numofdefeatedenemies = 0;


static bool g_gameStarted = false;

static bool g_playerDied = false;

static bool g_gameOver = false;

static unsigned int g_playerLifes = 3;

static unsigned int g_numberOfWaves = 0;

static unsigned int g_score = 0;


// --------------------------------

bool checkCollision(Object* obj1, Object* obj2) {

	bool inLane1 = obj1->IsInLane(), inLane2 = obj2->IsInLane();

	if (inLane1 == inLane2) {

		if (inLane1 == false) { //both in cubic arena


			if (obj1->EqualLanes(obj2)) {
				return true;
			}
		}

		if (inLane1 == true) { //both out of cubic area
			float distance1, distance2;

			distance1 = obj1->GetLinearDistance();
			distance2 = obj2->GetLinearDistance();

			if (obj1->EqualLanes(obj2)) {
				if (abs(distance1 - distance2) < 20.0f) {
					return true;
				}
				return false;
			}

		}
	}

	return false;
}

void playerHit() {
	if (g_playerLifes > 0) {
		g_playerLifes--;
	}
	if (g_playerLifes == 0) {
		g_gameOver = true;
	}

	g_playerDied = true;
}


void spawnEnemy(float dt) {
	g_enemytimer += dt;
	if (g_enemytimer > g_enemySpawnTime) {
		//enemyShips.push_back(new EnemyShips(NumOfDivisions, 4));
		g_enemytimer = 0.0f;
		
		unsigned int leftOrRight, lane;

		leftOrRight = rand() % 2;

		if (leftOrRight == 0) { //left
			lane = rand() % NumOfDivisions;

			enemyShips.push_back(new EnemyShips(lane, NumOfDivisions));
		}
		else { //right
			lane = rand() % NumOfDivisions;

			enemyShips.push_back(new EnemyShips(NumOfDivisions, lane));
		}
	}
}

void resolveCollision() {

	for (unsigned int i = 0; i < playerBullets.size(); i++) {
		for (unsigned int j = 0; j < enemyBullets.size(); j++) {
			if (i < playerBullets.size()) {
				if (checkCollision(playerBullets[i], enemyBullets[j])) {
					PlayerBullets* test1 = playerBullets[i];
					playerBullets.erase(playerBullets.begin() + i);
					delete test1;

					EnemyBullet* test2 = enemyBullets[j];
					enemyBullets.erase(enemyBullets.begin() + j);
					delete test2;

					if (playerBullets.size() != 0) i--;
					if (enemyBullets.size() != 0) j--;

				}
			}
		}
	}

	
	for (unsigned int i = 0; i < playerBullets.size(); i++) {
		for (unsigned int j = 0; j < enemyShips.size(); j++) {
				if (i < playerBullets.size()){
					if (checkCollision(playerBullets[i], enemyShips[j])) {
   						PlayerBullets* test1 = playerBullets[i];
						playerBullets.erase(playerBullets.begin() + i);
						delete test1;

						EnemyShips* test2 = enemyShips[j];
						enemyShips.erase(enemyShips.begin() + j);
						delete test2;

						g_score += 100;
						g_numofdefeatedenemies++;
					
						if (g_numofdefeatedenemies > 10) {
							g_numofdefeatedenemies = 0;
							g_numberOfWaves++;
							if (g_enemySpawnTime > 1.0f) {
								g_enemySpawnTime -= 0.5f;
							}
							else if (g_enemySpawnTime > 0.1f) {
								g_enemySpawnTime -= 0.1f;
							}
						}



 						if (playerBullets.size() != 0) i--;
						if (enemyShips.size() != 0) j--;

				}
			}
		}
	}



	for (unsigned int i = 0; i < playerBullets.size(); i++) {
		if (playerBullets[i]->GetLinearDistance() > 1000.0f) { //outside the screen
			PlayerBullets* test1 = playerBullets[i];
			playerBullets.erase(playerBullets.begin() + i);
			delete test1;

			if (playerBullets.size() != 0) i--;
		}
	}


	for (unsigned int i = 0; i < enemyBullets.size() ; i++) {
		if (enemyBullets[i]->IsStopped()) { //outside the screen
			EnemyBullet* test1 = enemyBullets[i];
			enemyBullets.erase(enemyBullets.begin() + i);
			delete test1;
			
			if (enemyBullets.size() != 0) i--;
		}
	}


	for (unsigned int i = 0; i < enemyBullets.size() ; i++) {
		if (checkCollision(enemyBullets[i], player)) {
			EnemyBullet* test1 = enemyBullets[i];
			enemyBullets.erase(enemyBullets.begin() + i);
			delete test1;

			if (enemyBullets.size() != 0) i--;

			playerHit();
		}
	}


	for (unsigned int i = 0; i < enemyShips.size() ; i++) {
		if (checkCollision(enemyShips[i], player)) {
			EnemyShips* test1 = enemyShips[i];
			enemyShips.erase(enemyShips.begin() + i);
			delete test1;

			if (enemyShips.size() != 0) i--;

			playerHit();
		}
	}
}

// --------------------------------

void Init()
{
	srand(static_cast<int>(time(0)));
	std::vector <std::vector <Tile*>> g_Map;

	float XOffSet = 210.0f;

	Point Up(500.0f + XOffSet, 280.0f);
	Point Left(180.0f + XOffSet, 190.0f);
	Point Down(500.0f + XOffSet, 20.0f);
	Point Right(820.0f + XOffSet, 190.0f);


	map = new Map(Right, Up, Left, Down, NumOfDivisions);

	Object::DefineMap(map);
}


void Update(float deltaTime)
{
	deltaTime = (deltaTime / 1000.0f); //convert to seconds
	if (g_gameOver) {
		//close the window
	}
	else if (g_playerDied)
	{
		g_deathTimer += deltaTime;
		if (g_deathTimer > 3.0f) {
			if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false))
			{
				g_playerDied = false;
			}
			for (unsigned int i = 0; i < playerBullets.size(); i++) {
				delete playerBullets[i];
			}
			playerBullets.clear();
			for (unsigned int i = 0; i < enemyShips.size(); i++) {
				delete enemyShips[i];
			}
			enemyShips.clear();
			for (unsigned int i = 0; i < enemyBullets.size(); i++) {
				delete enemyBullets[i];
			}
			enemyBullets.clear();
			player->SetPosition(0, 0);
		}
	}
	else {
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
		{
			player->SetSpeed(0, 1);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
		{
			player->SetSpeed(0, -1);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
		{
			player->SetSpeed(-1, 0);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
		{
			player->SetSpeed(1, 0);
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, false))
		{
			std::vector <PlayerBullets*> temp1 = player->Shoot();

			playerBullets.insert(playerBullets.end(), temp1.begin(), temp1.end());
			g_gameStarted = true;
		}

		player->Update(deltaTime);

		for (unsigned int i = 0; i < playerBullets.size(); i++) {
			playerBullets[i]->Update(deltaTime);
		}

		unsigned int xPos, yPos;

		player->GetTilePosition(xPos, yPos);

		for (unsigned int i = 0; i < enemyShips.size(); i++) {
 			std::vector <EnemyBullet*> temp2 = enemyShips[i]->Update(deltaTime, xPos, yPos);
			enemyBullets.insert(enemyBullets.end(), temp2.begin(), temp2.end());
		}

		for (unsigned int i = 0; i < enemyBullets.size(); i++) {
			enemyBullets[i]->Update(deltaTime);
		}

		resolveCollision();

		if (g_gameStarted) spawnEnemy(deltaTime);
	}
}


void Render()
{
	if (!g_gameStarted) { //if game has not started
		App::Print(420, 640, "The goal of the game is to stay alive as long as possible.");
	
		App::Print(420, 600, "Dodge the Enemy Spaceship bullets and shoot them and back.");
		 
		App::Print(420, 560, "move with ARROW KEYS and shoot with SPACE (can hold).");

		App::Print(600, 520, "Press SPACE to Start.");
	}

	else if (g_gameOver) {
		App::Print(600, 560, "Game Over!!!");
		App::Print(600, 520, "please close the window.");
	}

	else if ((g_playerDied) && (g_deathTimer > 3.0f)) {
		App::Print(600, 560, "you died!!!");
		App::Print(600, 520, "Press SPACE to Restart.");
	}


	App::Print(1300, 750, (std::string)("Score = " + std::to_string(g_score)) );
	App::Print(1300, 700, (std::string)("Wave = " + std::to_string(g_numberOfWaves)) );
	App::Print(10, 750, (std::string)("Life = " + std::to_string(g_playerLifes)) );


	map->Render();

	player->Render();

	for (int i = 0; i < playerBullets.size(); i++) {
		playerBullets[i]->Render();
	}

	for (int i = 0; i < enemyShips.size(); i++) {
		enemyShips[i]->Render();
	}

	for (int i = 0; i < enemyBullets.size(); i++) {
		enemyBullets[i]->Render();
	}



}

void Shutdown()
{	
	delete map;
	delete player;

	for (unsigned int i = 0; i < playerBullets.size(); i++) {
		delete playerBullets[i];
	}	
	for (unsigned int i = 0; i < enemyShips.size(); i++) {
		delete enemyShips[i];
	}
	for (unsigned int i = 0; i < enemyBullets.size(); i++) {
		delete enemyBullets[i];
	}
}

