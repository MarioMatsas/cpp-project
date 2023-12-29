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

	std::vector<Obstacle *> *m_static_objects;
	std::list<GameObject *> *m_dynamic_objects;

	// add some collidable blocks
	std::vector<std::string> m_block_names; // WHY?
	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	// dedicated method to draw a block
	// void drawBlock(int i);

	void game_over();

	// detect collisions
	void checkCollisions();

public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(std::vector<Obstacle *> *m_static_objects,
		  std::list<GameObject *> *m_dynamic_objects, const std::string &name = "Level0");
	~Level() override;
};
