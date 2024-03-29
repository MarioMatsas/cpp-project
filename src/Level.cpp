#include "Level.h"
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
#include "Enemy.h"
#include "Player.h"
#include "util.h"

Level::Level(std::vector<GameObject*>* m_static_objects,
             std::list<GameObject*>* m_dynamic_objects, const std::string& bg,
             std::pair<bool, bool> conds, const std::string& name)
    : GameObject(name),
      m_static_objects(m_static_objects),
      m_dynamic_objects(m_dynamic_objects),
      coin_condition_active(conds.first),
      enemy_condition_active(conds.second) {
    // Initialing all the brushes and setting all their needed parameters to fit
    // our needs
    m_brush_background.outline_opacity = 0.0f;
    m_brush_background.texture = std::string(ASSET_PATH) + bg;

    m_brush_health.fill_opacity = 1.0f;
    m_brush_health.outline_opacity = 0.0f;
    SETCOLOR(m_brush_health.fill_color, 1.0f, 1.0f, 1.0f)
    m_brush_health.texture = std::string(ASSET_PATH) + "Hearts/6.png";

    m_brush_score.fill_opacity = 1.0f;
    m_brush_score.outline_opacity = 0.0f;
    SETCOLOR(m_brush_score.fill_color, 1.0f, 1.0f, 1.0f)
    m_brush_score.texture = std::string(ASSET_PATH) + "coin_asset.png";

    m_brush_quiver.fill_opacity = 1.0f;
    m_brush_quiver.outline_opacity = 0.0f;
    SETCOLOR(m_brush_quiver.fill_color, 1.0f, 1.0f, 1.0f)
    m_brush_quiver.texture = std::string(ASSET_PATH) + "Arrow.png";

    m_brush_sword.fill_opacity = 1.0f;
    m_brush_sword.outline_opacity = 0.0f;
    SETCOLOR(m_brush_quiver.fill_color, 1.0f, 1.0f, 1.0f)
    m_brush_sword.texture = std::string(ASSET_PATH) + "sword.png";

    SETCOLOR(m_brush_quiver_text.fill_color, 1.0f, 1.0f, 1.0f);
    SETCOLOR(m_brush_score_text.fill_color, 1.0f, 1.0f, 1.0f);

    // Initialize all the objects in the dynamic list
    for (auto& p_go : *m_dynamic_objects) p_go->init();
}

Level::~Level() {
    for (auto& p_go : *m_static_objects) delete p_go;
    for (auto& p_go : *m_dynamic_objects) delete p_go;
}

void Level::init() {
    // Initializing all the dynamic and static objects
    for (auto& p_go : *m_static_objects) {
        if (p_go) p_go->init();
    }

    for (auto& p_go : *m_dynamic_objects) {
        if (p_go) p_go->init();
    }
}
void Level::draw() {
    // If the player dies draw the option screen
    if (PLAYER->health <= 0) {
        graphics::Brush br;
        br.texture = std::string(ASSET_PATH) + "GameOver.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH,
                           WINDOW_HEIGHT, br);
        graphics::playSound(
            std::string(ASSET_PATH) + std::string("player_damage_sound.wav"),
            0.0f, false);  // hack
        graphics::stopMusic();
        return;
    }
    // Draw background
    graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH,
                       WINDOW_HEIGHT, m_brush_background);

    // Draw statics and dynamics
    for (int i = 0; i < m_static_objects->size(); i++) {
        if ((*m_static_objects)[i]->m_class == "Obstacle") {
            Obstacle* g_ob = dynamic_cast<Obstacle*>((*m_static_objects)[i]);
            g_ob->draw();
        }
    }
    for (auto& g_ob : *m_dynamic_objects) {
        if (g_ob->m_class == "Obstacle" && g_ob->isActive()) g_ob->draw();
        if (g_ob->m_class == "Enemy" && g_ob->isActive()) g_ob->draw();
    }

    // Draw the hearts
    graphics::drawRect(WINDOW_WIDTH / 14, WINDOW_HEIGHT / 16, 108, 34,
                       m_brush_health);

    // Draw the quiver and the counter
    m_brush_quiver.outline_opacity = 0.0f;
    graphics::drawRect(WINDOW_WIDTH * 0.9, WINDOW_HEIGHT / 16, 151.0f / 3,
                       151.0f / 3, m_brush_quiver);

    graphics::setFont(std::string(ASSET_PATH) + "din1451alt.ttf");

    graphics::drawText(WINDOW_WIDTH * 0.93, WINDOW_HEIGHT / 16 + 151.0f / 9,
                       151.0f / 3, std::to_string(PLAYER->quiver),
                       m_brush_quiver_text);

    // Draw quiver or sword showing selection
    // Depending on the weapon sleected, the icon is shown
    if (PLAYER->gun_selected && PLAYER->quiver > 0) {
        graphics::drawRect(WINDOW_WIDTH / 1.2, WINDOW_HEIGHT / 16, 151.0f / 3,
                           151.0f / 3, m_brush_quiver);
    } else {
        graphics::drawRect(WINDOW_WIDTH / 1.2, WINDOW_HEIGHT / 16, 151.0f / 3,
                           151.0f / 3, m_brush_sword);
    }

    graphics::setFont(std::string(ASSET_PATH) + "din1451alt.ttf");

    graphics::drawText(WINDOW_WIDTH / 5.5, WINDOW_HEIGHT / 10.25, 151.0f / 3,
                       std::to_string(m_state->score), m_brush_score_text);

    graphics::drawRect(WINDOW_WIDTH / 6.5, WINDOW_HEIGHT / 16, 151.0f / 3,
                       151.0f / 3, m_brush_score);

    // draw player
    if (m_state->getPlayer()->isActive()) m_state->getPlayer()->draw();
}

void Level::update(float dt) {
    // Check to start playing the music
    if (first_time) {
        graphics::playMusic(
            std::string(ASSET_PATH) + std::string("castle_music.wav"), 0.05f,
            true, 1000);
        first_time = false;
    }
    // If the player dies give the user the option to retry or restart the game
    if (PLAYER->health <= 0) {
        if (graphics::getKeyState(graphics::SCANCODE_Y) &&
            !graphics::getKeyState(graphics::SCANCODE_N)) {
            m_state->m_curr_lvl_ptr = nullptr;
            delete this;
            return;
        } else if (graphics::getKeyState(graphics::SCANCODE_N) &&
                   !graphics::getKeyState(graphics::SCANCODE_Y)) {
            // Go back to main screen
            m_state->first_time_start = true;
            m_state->m_curr_lvl = -1;
            delete m_state->m_player;
            m_state->m_player = nullptr;
            m_state->m_curr_lvl_ptr = nullptr;
            delete this;
            return;
        }
    }

    // Update all dynamic objects and the player as long as they are active
    if (m_state->getPlayer()->isActive()) m_state->getPlayer()->update(dt);

    for (auto& g_ob : *m_dynamic_objects) {
        if (g_ob->isActive()) g_ob->update(dt);
    }

    // Check the collisions
    checkCollisions();

    // Check if the player can advance and if so make the needed deletions
    if (advance == true) {
        auto ht = PLAYER->arrows.begin();
        while (ht != PLAYER->arrows.end()) {
            delete *ht;
            ht = PLAYER->arrows.erase(ht);
        }

        auto s_it = PLAYER->sword_hits.begin();
        while (s_it != PLAYER->sword_hits.end()) {
            delete *s_it;
            s_it = PLAYER->sword_hits.erase(s_it);
        }

        if (PLAYER->sword_right) delete PLAYER->sword_right;
        if (PLAYER->sword_left) delete PLAYER->sword_left;
        m_state->m_curr_lvl += 1;
        m_state->m_curr_lvl_ptr = nullptr;
        delete this;
        advance = false;
        return;
    }

    m_brush_health.texture = std::string(ASSET_PATH) + "Hearts/" +
                             std::to_string(PLAYER->health) + ".png";

    GameObject::update(dt);
}

void Level::checkCollisions() {
    // Out of bounds for Player arrows
    // Player
    auto ht = PLAYER->arrows.begin();
    while (ht != PLAYER->arrows.end()) {
        if ((*ht)->m_pos_x > WINDOW_WIDTH || (*ht)->m_pos_x < 0 ||
            (*ht)->m_pos_y > WINDOW_HEIGHT || (*ht)->m_pos_y < 0) {
            delete *ht;
            ht = PLAYER->arrows.erase(ht);
        } else {
            ++ht;
        }
    }

    // Check if the enemy has hit the player and make all the needing changes
    // after the fact

    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         ++it) {
        if (!((*it)->isActive())) continue;
        if (!((*it)->m_class == "Enemy")) continue;
        Enemy* g_ob = dynamic_cast<Enemy*>(*it);
        auto s_it = g_ob->sword_hits.begin();
        while (s_it != g_ob->sword_hits.end()) {
            if ((*s_it)->intersect(*PLAYER)) {
                delete *s_it;
                s_it = g_ob->sword_hits.erase(s_it);
                PLAYER->health--;
                if (PLAYER->isActive())
                    graphics::playSound(
                        std::string(ASSET_PATH) +
                            std::string("player_damage_sound.wav"),
                        0.5f, false);
            } else {
                ++s_it;
            }
        }
        s_it = g_ob->sword_hits.begin();
        while (s_it != g_ob->sword_hits.end()) {
            delete *s_it;
            g_ob->sword_hits.pop_front();
            s_it = g_ob->sword_hits.begin();
        }
        g_ob->sword_hits.clear();
        auto jt = g_ob->arrows.begin();
        while (jt != g_ob->arrows.end()) {
            if ((*jt)->intersect(*PLAYER)) {
                // Remove the arrow from the list
                delete *jt;
                PLAYER->health--;
                if (PLAYER->isActive())
                    graphics::playSound(
                        std::string(ASSET_PATH) +
                            std::string("player_damage_sound.wav"),
                        0.5f, false);
                jt = g_ob->arrows.erase(jt);
            } else if ((*jt)->m_pos_x > WINDOW_WIDTH || (*jt)->m_pos_x < 0 ||
                       (*jt)->m_pos_y > WINDOW_HEIGHT || (*jt)->m_pos_y < 0) {
                delete *jt;
                jt = g_ob->arrows.erase(jt);
            } else {
                ++jt;
            }
        }
    }

    // Check if the player has collected a coin
    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         it++) {
        if (!((*it)->isActive())) continue;
        if ((*it)->m_class == "Obstacle") {
            Obstacle* g_ob = dynamic_cast<Obstacle*>(*it);

            // Simply delete the coin that the player collected
            if (m_state->getPlayer()->intersect(*g_ob)) {
                // Increase the score
                m_state->score += COIN_POINTS;
                delete g_ob;
                it = m_dynamic_objects->erase(it);
                if (it == m_dynamic_objects->end())
                    break;  // Avoid the extra iteration
            }
        }
        // Check if the player has hit an enemy
        if (!((*it)->m_class == "Enemy")) continue;
        Enemy* g_ob = dynamic_cast<Enemy*>(*it);

        auto s_it = PLAYER->sword_hits.begin();
        while (s_it != PLAYER->sword_hits.end()) {
            if ((*s_it)->intersect(*g_ob)) {
                delete *s_it;
                s_it = PLAYER->sword_hits.erase(s_it);
                g_ob->health--;
                if (PLAYER->isActive())
                    graphics::playSound(
                        std::string(ASSET_PATH) +
                            std::string("enemy_damage_sound.wav"),
                        0.5f, false);

                if (g_ob->health == 0) {
                    // Increase the score
                    m_state->score += ENEMY_POINTS;

                    delete g_ob;
                    it = m_dynamic_objects->erase(it);
                }
            } else {
                ++s_it;
            }
        }

        auto jt = m_state->getPlayer()->arrows.begin();
        while (jt != m_state->getPlayer()->arrows.end()) {
            if ((*jt)->intersect(*g_ob)) {
                delete *jt;
                g_ob->health--;
                if (PLAYER->isActive())
                    graphics::playSound(
                        std::string(ASSET_PATH) +
                            std::string("enemy_damage_sound.wav"),
                        0.5f, false);
                jt = m_state->getPlayer()->arrows.erase(jt);

                if (g_ob->health == 0) {
                    // Increase the score
                    m_state->score += ENEMY_POINTS;

                    delete g_ob;
                    it = m_dynamic_objects->erase(it);
                }
            } else {
                ++jt;
            }
        }
        if (it == m_dynamic_objects->end()) break;  // Avoid the extra iteration
    }
    // Delete player sword hits
    auto s_it = PLAYER->sword_hits.begin();
    while (s_it != PLAYER->sword_hits.end()) {
        delete *s_it;
        PLAYER->sword_hits.pop_front();
        s_it = PLAYER->sword_hits.begin();
    }
    PLAYER->sword_hits.clear();

    // Out of bounds for Player
    if (m_state->getPlayer()->m_pos_x < 0) {
        m_state->getPlayer()->m_pos_x = 0;
        m_state->getPlayer()->initialVelocityX = 0;
    } else if (m_state->getPlayer()->m_pos_x > WINDOW_WIDTH) {
        m_state->getPlayer()->m_pos_x = WINDOW_WIDTH;
        m_state->getPlayer()->initialVelocityX = 0;
    }

    // Out of bounds for Enemies
    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         ++it) {
        if (!((*it)->isActive())) continue;
        if (!((*it)->m_class == "Enemy")) continue;
        Enemy* g_ob = dynamic_cast<Enemy*>(*it);
        if (g_ob->m_pos_x < 0) {
            g_ob->m_pos_x = 0;
            g_ob->initialVelocityX = 0;
        } else if (g_ob->m_pos_x > WINDOW_WIDTH) {
            g_ob->m_pos_x = WINDOW_WIDTH;
            g_ob->initialVelocityX = 0;
        }
    }

    // Player / Enemy obstacle collisions
    for (GameObject* s_ob : *m_static_objects) {
        if (!(s_ob->m_class == "Obstacle")) continue;
        Obstacle* ob = dynamic_cast<Obstacle*>(s_ob);
        if (m_state->getPlayer()->intersect(*ob) || m_state->m_curr_lvl == 4) {
            // Check if the conditions have been met
            bool cond = check_end_condition();
            if (cond && (ob->m_name == "Door" || m_state->m_curr_lvl == 4)) {
                graphics::stopMusic(200);
                if (PLAYER->isActive() && m_state->m_curr_lvl != 4)
                    graphics::playSound(
                        std::string(ASSET_PATH) + std::string("door_sound.wav"),
                        0.5f, false);
                advance = true;
                return;
            }

            float belowCorrection = m_state->getPlayer()->intersectDown(*ob);
            if (belowCorrection != 0 && m_state->getPlayer()->jumping == true &&
                m_state->getPlayer()->velocityY <= 0) {
                m_state->getPlayer()->m_pos_y -= belowCorrection;
                m_state->getPlayer()->sword_right->m_pos_y -= belowCorrection;
                m_state->getPlayer()->sword_left->m_pos_y -= belowCorrection;
                m_state->getPlayer()->velocityY = 0;
            }
        }
        for (auto it = m_dynamic_objects->begin();
             it != m_dynamic_objects->end(); ++it) {
            if (!((*it)->isActive())) continue;
            if (!((*it)->m_class == "Enemy")) continue;
            Enemy* g_ob = dynamic_cast<Enemy*>(*it);
            if (g_ob->intersect(*ob)) {
                float belowCorrection = g_ob->intersectDown(*ob);
                if (belowCorrection != 0 && g_ob->jumping == true &&
                    g_ob->velocityY <= 0) {
                    g_ob->m_pos_y -= belowCorrection;
                    g_ob->sword_right->m_pos_y -= belowCorrection;
                    g_ob->sword_left->m_pos_y -= belowCorrection;
                    g_ob->velocityY = 0;
                }
            }
        }
    }
    for (GameObject* s_ob : *m_static_objects) {
        if (!(s_ob->m_class == "Obstacle")) continue;
        Obstacle* ob = dynamic_cast<Obstacle*>(s_ob);
        if (m_state->getPlayer()->intersect(*ob)) {
            float horizCorrection =
                m_state->getPlayer()->intersectSideways(*ob);

            if (((horizCorrection < 0 && horizCorrection > -20) ||
                 (horizCorrection > 0 && horizCorrection < 20)) &&
                m_state->getPlayer()->velocityY > 0 &&
                (*ob).m_name != "Main Platform") {
                m_state->getPlayer()->m_pos_x += horizCorrection;
                m_state->getPlayer()->sword_right->m_pos_x += horizCorrection;
                m_state->getPlayer()->sword_left->m_pos_x += horizCorrection;
                m_state->getPlayer()->initialVelocityX = 0;
            }
        }
        for (auto it = m_dynamic_objects->begin();
             it != m_dynamic_objects->end(); ++it) {
            if (!((*it)->isActive())) continue;
            if (!((*it)->m_class == "Enemy")) continue;
            Enemy* g_ob = dynamic_cast<Enemy*>(*it);
            if (g_ob->intersect(*ob)) {
                float horizCorrection = g_ob->intersectSideways(*ob);
                if (((horizCorrection < 0 && horizCorrection > -20) ||
                     (horizCorrection > 0 && horizCorrection < 20)) &&
                    g_ob->velocityY > 0 && (*ob).m_name != "Main Platform") {
                    g_ob->m_pos_x += horizCorrection;
                    g_ob->sword_right->m_pos_x += horizCorrection;
                    g_ob->sword_left->m_pos_x += horizCorrection;
                }
            }
        }
    }
    for (GameObject* s_ob : *m_static_objects) {
        if (!(s_ob->m_class == "Obstacle")) continue;
        Obstacle* ob = dynamic_cast<Obstacle*>(s_ob);
        if (m_state->getPlayer()->intersect(*ob)) {
            float vertCorrection = m_state->getPlayer()->intersectAbove(*ob);
            if (vertCorrection != 0) {
                m_state->getPlayer()->m_pos_y += vertCorrection;
                m_state->getPlayer()->sword_right->m_pos_y += vertCorrection;
                m_state->getPlayer()->sword_left->m_pos_y += vertCorrection;
                m_state->getPlayer()->velocityY = 0;
                m_state->getPlayer()->jumping = false;
            }
        }
        for (auto it = m_dynamic_objects->begin();
             it != m_dynamic_objects->end(); ++it) {
            if (!((*it)->isActive())) continue;
            if (!((*it)->m_class == "Enemy")) continue;
            Enemy* g_ob = dynamic_cast<Enemy*>(*it);
            if (g_ob->intersect(*ob)) {
                float vertCorrection = g_ob->intersectAbove(*ob);
                if (vertCorrection != 0) {
                    g_ob->m_pos_y += vertCorrection;
                    g_ob->sword_right->m_pos_y += vertCorrection;
                    g_ob->sword_left->m_pos_y += vertCorrection;
                    g_ob->velocityY = 0;
                    g_ob->jumping = false;
                }
            }
        }
    }

    // Player <-> Enemy collisions (we move Enemy)
    // we are ignoring Enemy <-> Enemy collisions since they're on the same
    // "team"
    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         ++it) {
        if (!((*it)->isActive())) continue;
        if (!((*it)->m_class == "Enemy")) continue;
        Enemy* g_ob = dynamic_cast<Enemy*>(*it);
        if (g_ob->intersect(*m_state->getPlayer())) {
            float horizCorrection =
                g_ob->intersectSideways(*m_state->getPlayer());
            if (horizCorrection != 0) {
                g_ob->m_pos_x += horizCorrection;
                g_ob->sword_right->m_pos_x += horizCorrection;
                g_ob->sword_left->m_pos_x += horizCorrection;
            }
        }
    }
}

// See if the conditions to advance to the next level have been met
bool Level::check_end_condition() {
    // Check if the coins have been collected
    if (coin_condition_active) {
        for (auto it = m_dynamic_objects->begin();
             it != m_dynamic_objects->end(); ++it) {
            if (!((*it)->isActive())) continue;
            if (((*it)->m_class == "Obstacle")) return false;
        }
    }

    // Check if all the enemies have been defeated
    if (enemy_condition_active) {
        for (auto it = m_dynamic_objects->begin();
             it != m_dynamic_objects->end(); ++it) {
            if (!((*it)->isActive())) continue;
            if (((*it)->m_class == "Enemy")) return false;
        }
    }
    return true;
}