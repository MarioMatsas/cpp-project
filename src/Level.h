#pragma once

#include "GameObject.h"
#include "Obstacle.h"
#include <vector>
#include <list>
#include <string>
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
#endif #include "Player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_health;
	graphics::Brush m_brush_quiver;
	graphics::Brush m_brush_quiver_text;
	graphics::Brush m_brush_score_text;
	int player_score = 0;

	std::vector<GameObject *> *m_static_objects;
	std::list<GameObject *> *m_dynamic_objects;

	// Possible conditions to advance to the next level
	bool coin_condition_active = false;
	bool enemy_condition_active = false;
	bool door_condition_active = true;
	bool advance = false;
	// detect collisions
	void checkCollisions();
	bool check_end_condition();

public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(std::vector<GameObject *> *m_static_objects,
		  std::list<GameObject *> *m_dynamic_objects, const std::string &bg, std::pair<bool, bool> conds, const std::string &name = "Level0");
	~Level() override;
};