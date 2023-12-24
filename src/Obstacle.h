#pragma once
#include "box.h"
#include "GameObject.h"
#include "Config.h"

class Obstacle : public GameObject, public Box {
	//float posx = WINDOW_WIDTH / 2, posy = 300.0f;
	//float width = 200.0f;
	//float height = 50.0f;

public:
	Obstacle(float x, float y, float w, float h, std::string name);
	void update(float dt) override;
	void draw() override;
	void init() override;
	/*
	float getX();
	float getY();
	float getHeight();
	float getWidth();
	*/
};