#include "Obstacle.h"
#include "graphics.h"

void Obstacle::update()
{
}

void Obstacle::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 0.5f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.5f;

	graphics::drawRect(posx, posy, width, height, br);
}

void Obstacle::init()
{
}

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
