#include "Sword.h"
#include "graphics.h"
#include <iostream>

void Sword::update(float dt)
{
}

void Sword::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 0.15f;
	br.fill_color[1] = 0.7f;
	br.fill_color[2] = 0.5f;

	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, br);
}

void Sword::init()
{
}

Sword::Sword(float x, float y, float w, float h, std::string name) : Box(x, y, w, h), GameObject(name)
{
}

/*
bool Sword::collision_detected()
{
	// Check for any collion with Obstacles
	for (Obstacle* ob : obstaclesList) {
		if (intersect(*ob)) {
			return true;

		}
	}
	return false;

}
*/
