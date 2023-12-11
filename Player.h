#pragma once
// "Game.h"
#include "GameObject.h"
//#include "Bullet.h"
#include "Config.h"
#include "box.h"
#include "graphics.h"
#include "vector"
#include "list"
#include "Obstacle.h"
#include "Bullet.h"
#include "Sword.h"

class Player : public GameObject, public Box{
	bool sword_selected = false;
	bool gun_selected = true;
	Sword* sword;
	graphics::MouseState mouse;
	std::vector<Obstacle*>& obstaclesList;
	double velocityY = 0; // Vertical velocity
	const double gravity = 0.1; // Gravity strength
	std::list<Bullet*> bullets;
	bool jumping = false;
	bool falling = false;
	float speed = 6.0f;
	//const Game& game;
	float length = 0.0;
	float initialVelocityX = 0.0f;
	float initialVelocityY = 0.0f;
	bool up_right = false;
	bool up_left = false;
	bool down_right = false;
	bool down_left = false;
	float tangent = 0.0f;
	float mouse_x = 0.0;
	float mouse_y = 0.0;
	//graphics::MouseState mouse;
	bool collided = false;
	bool shot = false;
	//float posx_ = WINDOW_WIDTH / 2, posy_ = 550.0f;
	//float posx = WINDOW_WIDTH / 2, posy = WINDOW_HEIGHT / 2;
public:
	//Player();
	Player(float x, float y, float w, float h, std::vector<Obstacle*>& obstacles);
	void update() override;
	void draw() override;
	void init() override;
	void jump();
	//void shoot();
};