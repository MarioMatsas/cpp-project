#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "box.h"
#include "Config.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
#include "sgg/graphics.h"
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#include "graphics.h"
#endif
#elif __linux__
#include "graphics.h"
#else
#error "Unknown compiler"
#endif


class Arrow : public GameObject, public Box {
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
	float theta = 0.0;
	float speed = 8.0f;
	bool collided = false;
	bool shot = false;

public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Arrow(float x, float y, float w, float h, float theta, std::string name);
	~Arrow();
	void shoot(float dt);
	void setMouse_x(float pos_x);
	void setMouse_y(float pos_y);
	float get_x();
	float get_y();
	void set_shot(bool s);
	bool get_shot();
};