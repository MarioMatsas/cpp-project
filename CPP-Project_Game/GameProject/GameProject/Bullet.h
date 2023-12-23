#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "box.h"
#include "Config.h"
#include "sgg\graphics.h"

class Bullet : public GameObject, public Box {
	//std::vector<Obstacle*>& obstaclesList;
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
	float speed = 8.0f;
	bool collided = false;
	bool shot = false;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Bullet(float x, float y, float w, float h, std::string name);
	~Bullet();
	void shoot();
	void setMouse_x(float pos_x);
	void setMouse_y(float pos_y);
	float get_x();
	float get_y();
	void set_shot(bool s);
	bool get_shot();
	bool collision_detected(std::vector<Obstacle*>& obstaclesList);
};