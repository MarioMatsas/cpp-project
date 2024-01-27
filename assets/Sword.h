#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "box.h"
#include "Config.h"
#include "sgg/graphics.h"

class Sword : public GameObject, public Box {
	//std::vector<Obstacle*>& obstaclesList;
public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	Sword(float x, float y, float w, float h, std::string name);

protected:
	void debugDraw();
};