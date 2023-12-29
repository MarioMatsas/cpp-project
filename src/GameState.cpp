#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <thread>
#include "GameObject.h"
#include "Obstacle.h"
#include "Enemy.h"
#include <chrono>
using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
	if (m_current_level)
		delete m_current_level;
}

GameState *GameState::getInstance()
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

bool GameState::init()
{
	// Start level 1
	if (level_1_active)
	{
		std::vector<Obstacle *> *m_static_objects = new std::vector<Obstacle *>();
		std::list<GameObject *> *m_dynamic_objects = new std::list<GameObject *>();
		m_static_objects->push_back(
			new Obstacle(WINDOW_WIDTH / 2, 300, 700, 35, "floor.png", "obstacle1"));
		m_static_objects->push_back(
			new Obstacle(WINDOW_WIDTH / 2 + 20, 300, 35, 200, "floor.png", "obstacle2"));
		m_static_objects->push_back(
			new Obstacle(WINDOW_WIDTH / 2, 100, 400, 35, "floor.png", "obstacle3"));
		m_static_objects->push_back(
			new Obstacle(WINDOW_WIDTH / 2 + 200, 300, 35, 200, "floor.png", "obstacle4"));

		m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4,
											   25, 50, "Enemy",
											   &Enemy::dumbMovement));
		m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
											   25, 50, "Enemy",
											   &Enemy::dumbMovement));
		m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8,
											   25, 50, "Enemy",
											   &Enemy::dumbMovement));

		std::cout << m_static_objects->size() << std::endl;

		m_current_level = new Level(m_static_objects, m_dynamic_objects, "1.lvl");
		m_current_level->init();

		m_player = new Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 25, 50, "Player");
		m_player->init();

		// graphics::preloadBitmaps(getAssetDir());
		// graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
	}
	// Start level 2
	// Start level 3
	// Start level 4
	// Start level 5 - BOSS FIGHT

	return true;
}

void GameState::draw()
{
	// Draw the main menu
	if (main_menu_active)
	{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "main_menu_screen.png";
		graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
	}

	// Draw the controls
	else if (controls_screen_active)
	{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "controls_screen.png";
		graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
	}
	// Finaly draw the current level
	else
	{
		if (!m_current_level)
			return;

		m_current_level->draw();
	}
}

void GameState::update(float dt)
{
	// Skip an update if a long delay is detected
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;
	// Avoid too quick updates
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	}

	// Check if the we are at the main menu
	if (main_menu_active)
	{
		graphics::getMouseState(mouse);
		if (mouse.button_left_pressed)
		{
			// Move onto the controls screen
			main_menu_active = false;
			controls_screen_active = true;
		}
	}
	else if (controls_screen_active)
	{
		graphics::getMouseState(mouse);
		if (mouse.button_left_pressed)
		{
			// Move onto the first level
			controls_screen_active = false;
			level_1_active = true;
			init();
		}
	}
	else
	{
		if (!m_current_level)
			return;

		m_current_level->update(dt);

		m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	}
}

std::string GameState::getFullAssetPath(const std::string &asset)
{
	return m_asset_path + asset;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

GameState *GameState::m_unique_instance = nullptr;