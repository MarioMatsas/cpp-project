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

        // TODO: these can be automated by loading from a file!
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
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT - 150,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_player = new Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 25, 50, "Player");
        m_player->init();

        m_curr_lvl_ptr = new Level(m_static_objects, m_dynamic_objects, "background_lvl.png", { true, false }, "1.lvl");
        m_curr_lvl_ptr->init();

        // graphics::preloadBitmaps(getAssetDir());
        // graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
    }
    if (m_curr_lvl == 2) {
        // Delete he previous level before starting anew
        //delete m_curr_lvl_ptr;


        std::vector<GameObject*>* m_static_objects = new std::vector<GameObject*>();
        std::list<GameObject*>* m_dynamic_objects = new std::list<GameObject*>();

        // TODO: these can be automated by loading from a file!
        // Statics
        m_static_objects->push_back(
            new Obstacle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 35 / 2, WINDOW_WIDTH, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "Main Platform"));
        //m_static_objects->push_back(
        //	new Obstacle(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 4 + 30, 200, 35, 0.5f, 0.0f, 0.5f, 0.0f, "floor.png", "obstacle2"));
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
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 + 300, WINDOW_HEIGHT - 150,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_dynamic_objects->push_back(new Enemy(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT - 150,
            25, 50, "Enemy",
            &Enemy::dumbMovement, false));
        m_player = new Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 25, 50, "Player");
        m_player->init();

        m_curr_lvl_ptr = new Level(m_static_objects, m_dynamic_objects, "background_lvl.png", { false, false }, "1.lvl");
        m_curr_lvl_ptr->init();

        // graphics::preloadBitmaps(getAssetDir());
        // graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");
    }
    if (m_curr_lvl == 3) {
        // Print a gameover screen, and send user back to main menu
        graphics::stopMessageLoop();
    }
    // Start level 2
    // Start level 3
    // Start level 4
    // Start level 5 - BOSS FIGHT

    return true;
}

void GameState::draw()
{
    graphics::Brush br;
    switch (m_curr_lvl)
    {
    case -1:
        br.texture = std::string(ASSET_PATH) + "main_menu_screen.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
        break;

    case 0:
        br.texture = std::string(ASSET_PATH) + "controls_screen.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
        break;

    default:
        if (!m_curr_lvl_ptr) {
            init();
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
            init();
        }
        break;
    default:
        if (!m_curr_lvl_ptr) {
            init();
            return;
        }

        m_curr_lvl_ptr->update(dt);

        m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
        break;
    }
}

void GameState::resize(int new_w, int new_h) {
    if ((new_w / new_h) > (WINDOW_WIDTH / WINDOW_HEIGHT)) {
        // letterbox horizontally
        real_canvas_height = new_h;
        real_canvas_width = ((new_h * WINDOW_WIDTH) / WINDOW_HEIGHT);
    }
    else {
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