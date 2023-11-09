#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Bullet.h"

class Game {
	friend class Bullet;
	
	bool initialized_obstacle = false;
	//bool initialized_bullet = false;
	Player * player = nullptr;
	Obstacle* obstacle = nullptr;
	//Bullet* bullet = nullptr;
public:
	bool initialized_player = false;
	void update();
	void draw();
	void init();
	Game();
	~Game();
};