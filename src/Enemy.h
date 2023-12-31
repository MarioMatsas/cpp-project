#pragma once
#include "GameObject.h"
#include <string>
#include "Config.h"
#include "box.h"
#include "graphics.h"
#include "vector"
#include "list"
#include "Obstacle.h"
#include "Arrow.h"
#include "Sword.h"

class Enemy : public GameObject, public Box
{
protected:
	graphics::Brush m_brush;
	graphics::Brush m_brush_debug;

public:
	const float m_accel_horizontal = 20.0f;
	const float m_max_velocity = 5.0f;
	float m_vx = 0.0f;
	int health = 6; // 0 to 6
	bool attacking = false;
	int same_counter = 0;
	int frameCounter = 0;
	int previous_sprite = 0;
	int dt_sum = 0;
	std::vector<std::string> standing_sprites;
	std::vector<std::string> jumping_sprites;
	std::vector<std::string> attack_sprites;
	std::vector<std::string> sprites;
	bool looking_right = true;
	bool looking_left = false;
	bool sword_selected = false;
	bool gun_selected = true;
	Sword *sword_right;
	Sword *sword_left;
	double velocityY = 0;		// Vertical velocity
	const double gravity = 0.1; // Gravity strength
	std::list<Arrow *> arrows;
	std::vector<Box *> sword_hits;
	typedef std::pair<graphics::scancode_t, graphics::scancode_t> (Enemy::*DecFn)();
	DecFn movement;
	bool jumping = false;
	bool falling = false;
	float speed = 4.0f;
	// const Game& game;
	float length = 0.0;
	float initialVelocityX = 0.0f;
	float initialVelocityY = 0.0f;
	bool up_right = false;
	bool up_left = false;
	bool down_right = false;
	bool down_left = false;
	float tangent = 0.0f;
	bool collided = false;
	bool shot = false;

public:
	// Enemy();
	Enemy(float x, float y, float w, float h, std::string name, DecFn func);
	std::pair<graphics::scancode_t, graphics::scancode_t> dumbMovement(void);
	~Enemy();
	bool should_I_shoot();
	bool should_I_thrust();
	void update(float dt) override;
	void draw() override;
	void init() override;
	void jump();
	// void shoot();

protected:
	void debugDraw();
};
