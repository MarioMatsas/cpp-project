#include "Obstacle.h"
#include "graphics.h"

Obstacle::Obstacle(float x, float y, float w, float h, std::string name) : Box(x, y, w, h), GameObject(name)
{
}

void Obstacle::update(float dt)
{
}

void Obstacle::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 0.5f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.5f;
	br.outline_opacity = 1;
	br.texture = std::string(ASSET_PATH) + "floor.png";

	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, br);
}

void Obstacle::init()
{
}
