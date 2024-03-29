#pragma once
// "Game.h"
#include "GameObject.h"
#include <string>
//#include "Arrow.h"
#include "Config.h"
#include "box.h"
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
#include "vector"
#include "list"
#include "Obstacle.h"
#include "Arrow.h"
#include "Sword.h"

class Player : public GameObject, public Box {
public:
	const float m_accel_horizontal = 20.0f;
	const float m_max_velocity = 5.0f;
	float m_vx = 0.0f;
	bool attacking = false;
	int same_counter = 0;
	int previous_sprite = 0;
	int frameCounter = 0;
	std::vector<std::string> standing_sprites;
	std::vector<std::string> jumping_sprites;
	std::vector<std::string> attack_sprites;
	std::vector<std::string> sprites;
	bool looking_right = true;
	bool looking_left = false;
	bool sword_selected = false;
	bool gun_selected = true;
	Sword* sword_right;
	Sword* sword_left;
	graphics::MouseState mouse;
	double velocityY = 0; // Vertical velocity
	const double gravity = 0.1; // Gravity strength
	int quiver = 15; // amount of arrows available to shoot, 0 <= quiver <= 24
	// should only be reset when restarting a level, not between levels
	// we are not going to limit the enemies likewise, to make it harder
	// (gta also does this I'm pretty sure)
	std::list<Arrow*> arrows;
	std::list<Box*> sword_hits;
	bool jumping = false;
	bool falling = false;
	float speed = 4.0f;
	int health = 6; // 0 to 6
	float length = 0.0;
	float initialVelocityX = 0.0f;
	float initialVelocityY = 0.0f;
	bool up_right = false;
	bool up_left = false;
	bool down_right = false;
	bool down_left = false;
	float tangent = 0.0f;
	float m_initial_x = 0;
	float m_initial_y = 0;
	//graphics::MouseState mouse;
	bool collided = false;
	bool shot = false;
	//float posx_ = WINDOW_WIDTH / 2, posy_ = 550.0f;
	//float posx = WINDOW_WIDTH / 2, posy = WINDOW_HEIGHT / 2;
public:
	//Player();
	Player(float x, float y, float w, float h, std::string name);
	~Player();
	void setPos(int x, int y);
	void update(float dt) override;
	void draw() override;
	void init() override;
	void jump();
	//void shoot();

protected:
	void debugDraw();
};