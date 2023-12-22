#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Bullet.h"

class Game {
	std::vector<Obstacle*> obstacleList = {};
	bool initialized_obstacle = false;
	//bool initialized_bullet = false;
	Player * player = nullptr;
	Obstacle* obstacle1 = nullptr;
	Obstacle* obstacle2 = nullptr;
	Obstacle* obstacle3 = nullptr;
	Obstacle* obstacle4 = nullptr;
	//Bullet* bullet = nullptr;
public:
	bool initialized_player = false;
	void update();
	void draw();
	void init();
	void check_colisions();
	Game();
	~Game();
};