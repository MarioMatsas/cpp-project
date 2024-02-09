#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <thread>
#include "GameObject.h"
#include "Obstacle.h"
#include "Enemy.h"
#include <chrono>
#include "util.h"
using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
    if (m_curr_lvl_ptr)
        delete m_curr_lvl_ptr;
}

GameState* GameState::getInstance()
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
    if (m_curr_lvl == 1)
    {
        std::vector<GameObject*>* m_static_objects = new std::vector<GameObject*>();
        std::list<GameObject*>* m_dynamic_objects = new std::list<GameObject*>();

        // Statics
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 35 / 2, WINDOW_WIDTH, 35, 0.15f, 0.3f, 0.15f, 0.0f, "floor.png", "Main Platform"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, 225, 200, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle2"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, 400, 80, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle3"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 225, WINDOW_HEIGHT / 2 + 70, 150, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle4"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 225, WINDOW_HEIGHT / 2 + 70, 150, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle5"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 35 / 2 - 60, 80, 110, 0.5f, 0.15f, 0.3f, 0.0f, "door_asset.png", "Door"));

        // Dynamics
        m_dynamic_objects->push_back(
            new Obstacle(287, 285, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin1"));
        m_dynamic_objects->push_back(
            new Obstacle(737, 285, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin2"));

        m_dynamic_objects->push_back(new Enemy(512, 180,
            25, 50, "Enemy",
            &Enemy::noMovement, false));
        if (!m_player)
        {
            m_player = new Player(60, WINDOW_HEIGHT - 35 / 2 - 60, 25, 50, "Player");
        }
        m_player->init();

        m_curr_lvl_ptr = new Level(m_static_objects, m_dynamic_objects, "nature.png", { false, false }, "1.lvl");
        m_curr_lvl_ptr->init();
    }

    // Start level 2
    if (m_curr_lvl == 2)
    {
        std::vector<GameObject*>* m_static_objects = new std::vector<GameObject*>();
        std::list<GameObject*>* m_dynamic_objects = new std::list<GameObject*>();

        // Statics
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 35 / 2, WINDOW_WIDTH, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "Main Platform"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 4 + 5, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle2"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 4 + 5, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle3"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2 - 5, 125, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle5"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT / 2 - 5, 125, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle5"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 150, WINDOW_HEIGHT / 2 + 50, 125, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle5"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 50, 125, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle6"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 120, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle7"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT - 120, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle8"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 35 / 2 - 60, 80, 110, 0.5f, 0.0f, 0.5f, 0.0f, "door_asset.png", "Door"));

        // Dynamics
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 350, WINDOW_HEIGHT / 4 + 5 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 350, WINDOW_HEIGHT / 4 + 5 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 450, WINDOW_HEIGHT / 2 - 5 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 450, WINDOW_HEIGHT / 2 - 5 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 2 + 50 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 + 50 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2 - 5 - 35 / 2,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 + 400, WINDOW_HEIGHT / 2 - 5 - 35 / 2,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_player->init();

        m_curr_lvl_ptr = new Level(m_static_objects, m_dynamic_objects, "background_lvl.png", { false, false }, "2.lvl");
        m_curr_lvl_ptr->init();
    }

    // Start level 3
    if (m_curr_lvl == 3)
    {
        std::vector<GameObject*>* m_static_objects = new std::vector<GameObject*>();
        std::list<GameObject*>* m_dynamic_objects = new std::list<GameObject*>();

        // Statics
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 35 / 2, WINDOW_WIDTH, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "Main Platform"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 4 + 30, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle2"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 4 + 30, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle3"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle4"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 2 + 50, 75, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle5"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 + 50, 75, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle6"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 120, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle7"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT - 120, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle8"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 35 / 2 - 60, 80, 110, 0.5f, 0.0f, 0.5f, 0.0f, "door_asset.png", "Door"));

        // Dynamics
        m_dynamic_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 35, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin"));
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 4 + 30 - 35 / 2,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 4 + 30 - 35 / 2,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 150,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_player->init();

        m_curr_lvl_ptr = new Level(m_static_objects, m_dynamic_objects, "background_lvl.png", { false, false }, "3.lvl");
        m_curr_lvl_ptr->init();
    }

    // Start level 4
    if (m_curr_lvl == 4)
    {

        std::vector<GameObject*>* m_static_objects = new std::vector<GameObject*>();
        std::list<GameObject*>* m_dynamic_objects = new std::list<GameObject*>();

        // Statics
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 35 / 2, WINDOW_WIDTH, 35, 0.15f, 0.3f, 0.15f, 0.0f, "floor.png", "Main Platform"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT / 4 + 5, 200, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle1"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 4 + 5, 200, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle2"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 25, 200, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle3"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 225, WINDOW_HEIGHT / 2 + 70, 50, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle4"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 225, WINDOW_HEIGHT / 2 + 70, 50, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle5"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 120, 200, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle6"));
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT - 120, 200, 35, 0.5f, 0.15f, 0.3f, 0.15f, "floor.png", "obstacle7"));

        // Dynamics
        m_dynamic_objects->push_back(
            new Obstacle(287, 285, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin1"));
        m_dynamic_objects->push_back(
            new Obstacle(737, 285, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin2"));
        m_dynamic_objects->push_back(
            new Obstacle(812, 90, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin3"));
        m_dynamic_objects->push_back(
            new Obstacle(212, 90, 20, 20, 1.0f, 1.0f, 1.0f, 0.0f, "coin_asset.png", "Coin3"));

        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2, 190,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_dynamic_objects->push_back(new Enemy(860, 90,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_dynamic_objects->push_back(new Enemy(200, 90,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_player->init();

        m_curr_lvl_ptr = new Level(m_static_objects, m_dynamic_objects, "StarryNight.png", { true, true }, "4.lvl");
        m_curr_lvl_ptr->init();

    }

    return true;
}

void GameState::draw()
{
    graphics::Brush br;
    switch (m_curr_lvl)
    {
    case -1:
        br.texture = std::string(ASSET_PATH) + "main_menu.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
        break;

    case 0:
        br.texture = std::string(ASSET_PATH) + "controls_screen.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
        break;
    case 5:
        br.texture = std::string(ASSET_PATH) + "end_screen.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
        break;
    default:
        if (!m_curr_lvl_ptr)
        {
            if (m_player != nullptr)
                m_player->setActive(false);
            br.texture = std::string(ASSET_PATH) + "loading_screen.png";
            graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
            return;
        }
        m_curr_lvl_ptr->draw();
        break;
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
    switch (m_curr_lvl)
    {
    case -1:
        if (first_time_start)
        {
            score = 0; // Make sure to reset the score
            graphics::playMusic(std::string(ASSET_PATH) + std::string("medieval_theme.wav"), 0.6f, true, 500);
            first_time_end = true;
            first_time_start = false;
        }
        graphics::getMouseState(mouse);
        if (mouse.button_left_pressed)
        {
            // Move onto the controls screen
            m_curr_lvl = 0;
            break;
        }
    case 0:
        graphics::getMouseState(mouse);
        if (mouse.button_left_pressed)
        {
            // Move onto the first level
            m_curr_lvl = 1;
            graphics::stopMusic(500);
        }
        break;
    case 5:
        if (first_time_end)
        {
            graphics::playMusic(std::string(ASSET_PATH) + std::string("ending_theme.wav"), 0.5f, true, 1000);
            first_time_end = false;
            first_time_start = true;
        }
        graphics::getMouseState(mouse);
        if (mouse.button_left_pressed)
        {
            // Go to main screen
            m_curr_lvl = -1;
            graphics::stopMusic(500);
        }
        break;
    default:
        if (!m_curr_lvl_ptr)
        {
            // Go to the next level
            std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(1500));
            init();
            return;
        }

        m_curr_lvl_ptr->update(dt);

        m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
        break;
    }
}

void GameState::resize(int new_w, int new_h)
{
    if ((new_w / new_h) > (WINDOW_WIDTH / WINDOW_HEIGHT))
    {
        // letterbox horizontally
        real_canvas_height = new_h;
        real_canvas_width = ((new_h * WINDOW_WIDTH) / WINDOW_HEIGHT);
    }
    else
    {
        // letterbox vertically
        real_canvas_width = new_w;
        real_canvas_height = ((new_w * WINDOW_HEIGHT) / WINDOW_WIDTH);
    }

    real_window_height = new_h;
    real_window_width = new_w;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
    return m_asset_path + asset;
}

std::string GameState::getAssetDir()
{
    return m_asset_path;
}

GameState* GameState::m_unique_instance = nullptr;