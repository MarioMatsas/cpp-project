#include "Obstacle.h"
#include "sgg\graphics.h"

Obstacle::Obstacle(float x, float y, float w, float h): Box(x, y, w, h)
{
}

void Obstacle::update()
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
/*
float Obstacle::getX()
{
	return posx;
}

float Obstacle::getY()
{
	return posy;
}

float Obstacle::getHeight()
{
	return height;
}

float Obstacle::getWidth()
{
	return width;
}
*/