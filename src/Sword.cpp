#include "Sword.h"
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
#include "util.h"
#include <iostream>

void Sword::update(float dt)
{
}

void Sword::debugDraw()
{
	graphics::Brush debug_brush;
	debug_brush.fill_color[0] = 0.15f;
	debug_brush.fill_color[1] = 0.7f;
	debug_brush.fill_color[2] = 0.5f;

	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, debug_brush);

	graphics::setFont(std::string(ASSET_PATH) + "JetBrainsMono-Thin.ttf");
	/* we don't need that since it's always the same relative to the player.
	char x[10];
	char y[10];
	sprintf(x, "%5.2f", m_pos_x);
	sprintf(y, "%5.2f", m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_pos_x - m_width/2, m_pos_y + m_height/2, 16, x, debug_brush);
	graphics::drawText(m_pos_x - m_width/2, m_pos_y - m_height/2, 16, y, debug_brush);
	*/
}

void Sword::draw()
{
	if (m_state->m_debugging)
		debugDraw();
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