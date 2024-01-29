#pragma once
#include "Config.h"
#include <string>
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

class GameState
{
private:
	static GameState* m_unique_instance;

	const std::string m_asset_path = "assets\\";

	const float m_canvas_width = WINDOW_WIDTH;
	const float m_canvas_height = WINDOW_HEIGHT;

	class Level* m_curr_lvl_ptr = 0;
	class Player* m_player = 0;
	int score = 0;
	int m_curr_lvl = -1; // -1: start screen
	//  0: tutorial screen
	//  1-4: levels

	graphics::MouseState mouse;

	GameState();

public:
	bool m_debugging = false;
	int real_canvas_width = WINDOW_WIDTH;
	int real_canvas_height = WINDOW_HEIGHT;
	int real_window_width = WINDOW_WIDTH;
	int real_window_height = WINDOW_HEIGHT;

	~GameState();
	static GameState* getInstance();

	bool init();
	void draw();
	void update(float dt);
	void resize(int new_w, int new_h);

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	class Player* getPlayer() { return m_player; }

	friend class Level;
};