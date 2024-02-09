#pragma once
#include "box.h"
#include "GameObject.h"
#include "Config.h"

class Obstacle : public GameObject, public Box {
protected:
	const std::string texture;
	graphics::Brush m_brush;
	graphics::Brush m_brush_debug;

public:
	Obstacle(float x, float y, float w, float h, float r, float g, float b, float a, std::string texture, std::string name);
	void update(float dt) override;
	void draw() override;
	void init() override;
};