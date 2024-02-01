#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "box.h"
#include "Config.h"
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
class Sword : public GameObject, public Box
{
	// std::vector<Obstacle*>& obstaclesList;
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Sword(float x, float y, float w, float h, std::string name);

protected:
	void debugDraw();
};