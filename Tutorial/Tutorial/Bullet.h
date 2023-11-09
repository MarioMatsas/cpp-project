#pragma once
#include "GameObject.h"
#include "Config.h"
#include "graphics.h"

class Bullet : GameObject{
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
	float posx_b = WINDOW_WIDTH / 2, posy_b = WINDOW_HEIGHT / 2;
	float posy_dummy = 0.0f;
	bool jumping = false;
	bool falling = true;
public:
	void update() override;
	void draw() override;
	void init() override;
	~Bullet();
	void shoot();
	void setMouse_x(float pos_x);
	void setMouse_y(float pos_y);
	float get_x();
	float get_y();
	void set_x(float pos_x);
	void set_y(float pos_y);
	void set_shot(bool s);
	bool get_shot();
	//const Game& game
	bool collision_detected(int num);
};