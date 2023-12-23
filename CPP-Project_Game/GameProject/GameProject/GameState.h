#pragma once

#include <string>

class GameState
{
private:
	static GameState* m_unique_instance;

	const std::string m_asset_path = "assets\\";

	const float m_canvas_width = 750.0f;
	const float m_canvas_height = 400.0f;

	class Level* m_current_level = 0;
	class Player* m_player = 0;

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
};