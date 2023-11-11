#pragma once
#include "GameObject.h"
#include "Config.h"

class Obstacle : public GameObject{
	float posx = WINDOW_WIDTH / 2, posy = 550.0f;
	float width = 200.0f;
	float height = 50.0f;

public:
	void update() override;
	void draw() override;
	void init() override;
	float getX();
	float getY();
	float getHeight();
	float getWidth();
};