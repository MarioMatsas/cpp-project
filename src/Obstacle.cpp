#include "Obstacle.h"
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

Obstacle::Obstacle(float x, float y, float w, float h, float r, float g, float b, float a, std::string texture, std::string name) : Box(x, y, w, h), GameObject(name, "Obstacle"), texture(texture)
{
	SETCOLOR(m_brush.fill_color, r, g, b);
	m_brush.outline_opacity = a;
	m_brush.texture = std::string(ASSET_PATH) + texture;
}

void Obstacle::update(float dt)
{
}

void Obstacle::draw()
{

	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush);

	if (m_state->m_debugging)
	{
		m_brush_debug.fill_opacity = 0.1f;
		SETCOLOR(m_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
		SETCOLOR(m_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
		graphics::drawRect(m_pos_x, m_pos_y,
			m_width, m_height,
			m_brush_debug);
		graphics::setFont(std::string(ASSET_PATH) + "JetBrainsMono-Thin.ttf");
		char x[10];
		char y[10];
		sprintf_s(x, "%5.2f", m_pos_x);
		sprintf_s(y, "%5.2f", m_pos_y);
		SETCOLOR(m_brush_debug.fill_color, 1, 0, 0);
		m_brush_debug.fill_opacity = 1.0f;
		graphics::drawText(m_pos_x - m_width / 2,
			m_pos_y + m_height / 2,
			16, x, m_brush_debug);
		graphics::drawText(
			m_pos_x - m_width / 2,
			m_pos_y + m_height / 2 - 18, 16, y,
			m_brush_debug);
	}
}

void Obstacle::init()
{
}