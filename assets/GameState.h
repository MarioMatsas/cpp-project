#pragma once
#include "Config.h"
#include <string>
#include "sgg/graphics.h"

class GameState
{
private:
	static GameState* m_unique_instance;

	const std::string m_asset_path = "assets\\";

	const float m_canvas_width = WINDOW_WIDTH;
	const float m_canvas_height = WINDOW_HEIGHT;

	class Level* m_curr_lvl_ptr = 0;
	class Player* m_player = 0;

	int m_curr_lvl = -1; // -1: start screen
	//  0: tutorial screen
	//  1-4: levels

	graphics::MouseState mouse;

	GameState();

public:
	bool m_debugging = false;

public:
	~GameState();
	static GameState* getInstance();

	bool init();
	void draw();
	void update(float dt);

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	class Player* getPlayer() { return m_player; }

	friend class Level;
};