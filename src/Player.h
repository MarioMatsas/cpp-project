#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Config.h"
#include "graphics.h"
#include "vector"

class Game;

class Player : public GameObject {
	std::vector<Bullet*> bullets;
	const Game& game;
	Bullet* b = nullptr;
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
	graphics::MouseState mouse;
	bool collided = false;
	bool shot = false;
	float posx_ = WINDOW_WIDTH / 2, posy_ = 550.0f;
	float width = 200.0f;
	float height = 50.0f;
	float speed = 10.0f;
	float up_velocity = speed;
	float jump_height = 100.0;
	float gravity = 0.5f;
	float posx = WINDOW_WIDTH / 2, posy = WINDOW_HEIGHT / 2;
	float posy_dummy = 0.0f;
	bool jumping = false;
	bool falling = true;
public:
	Player(const Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	//void shoot();
};
