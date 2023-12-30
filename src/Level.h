#pragma once

#include "GameObject.h"
#include "Obstacle.h"
#include <vector>
#include <list>
#include <string>
#include <graphics.h>
#include "Player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_health;

	std::vector<GameObject *> *m_static_objects;
	std::list<GameObject *> *m_dynamic_objects;

	void game_over();

	// detect collisions
	void checkCollisions();

public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(std::vector<GameObject *> *m_static_objects,
		  std::list<GameObject *> *m_dynamic_objects, const std::string &name = "Level0");
	~Level() override;
};
