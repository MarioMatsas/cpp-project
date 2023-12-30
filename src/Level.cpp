#include "Level.h"
#include <graphics.h>
#include "Enemy.h"
#include "Player.h"
#include "util.h"

Level::Level(std::vector<GameObject *> *m_static_objects,
             std::list<GameObject *> *m_dynamic_objects, const std::string &name) : GameObject(name), m_static_objects(m_static_objects), m_dynamic_objects(m_dynamic_objects)
{
    m_brush_background.outline_opacity = 0.0f;
    m_brush_background.texture = std::string(ASSET_PATH) + "background_lvl.png";

    m_brush_health.fill_opacity = 1.0f;
    m_brush_health.outline_opacity = 0.0f;
    SETCOLOR(m_brush_health.fill_color, 1.0f, 1.0f, 1.0f)
    m_brush_health.texture = std::string(ASSET_PATH) + "Hearts/6.png";

    for (auto &p_go : *m_dynamic_objects)
        p_go->init();
}

Level::~Level()
{
    for (auto &p_go : *m_static_objects)
        delete p_go;
    for (auto &p_go : *m_dynamic_objects)
        delete p_go;
}

void Level::init()
{
    for (auto &p_go : *m_static_objects)
    {
        if (p_go)
            p_go->init();
    }

    for (auto &p_go : *m_dynamic_objects)
    {
        if (p_go)
            p_go->init();
    }
}
void Level::draw()
{
    if (PLAYER->health <= 0)
    {
        graphics::Brush br;
        br.texture = std::string(ASSET_PATH) + "GameOver.png";
        graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, br);
        return;
    }
    graphics::drawRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH,
                       WINDOW_HEIGHT, m_brush_background);
    for (int i = 0; i < m_static_objects->size(); i++)
    {
        if ((*m_static_objects)[i]->m_class == "Obstacle")
        {
            Obstacle *g_ob = dynamic_cast<Obstacle *>((*m_static_objects)[i]);
            g_ob->draw();
        }
    }
    for (auto &g_ob : *m_dynamic_objects)
    {
        if (g_ob->m_class == "Enemy" && g_ob->isActive())
            g_ob->draw();
    }

    graphics::drawRect(WINDOW_WIDTH / 14, WINDOW_HEIGHT / 16, 108, 34,
                       m_brush_health);

    // draw player
    if (m_state->getPlayer()->isActive())
        m_state->getPlayer()->draw();
}

void Level::update(float dt)
{
    if (PLAYER->health <= 0)
    {
        if (graphics::getKeyState(graphics::SCANCODE_Y) && !graphics::getKeyState(graphics::SCANCODE_N))
        {
            m_state->m_curr_lvl_ptr = nullptr;
            delete this;
            return;
        }
        else if (graphics::getKeyState(graphics::SCANCODE_N) && !graphics::getKeyState(graphics::SCANCODE_Y))
        {
            graphics::stopMessageLoop();
        }
    }

    if (m_state->getPlayer()->isActive())
        m_state->getPlayer()->update(dt);

    for (auto &g_ob : *m_dynamic_objects)
    {
        if (g_ob->isActive())
            g_ob->update(dt);
    }

    checkCollisions();

    // TODO: add a check here for reaching some milestone to switch levels.
    // in that case, I think just incrementing m_curr_lvl will be enough!

    m_brush_health.texture = std::string(ASSET_PATH) + "Hearts/" +
                             std::to_string(PLAYER->health) + ".png";

    GameObject::update(dt);
}

void Level::checkCollisions()
{
    // Bullet collisions / Out of bounds check

    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         ++it)
    {
        if (!((*it)->isActive()))
            continue;
        if (!((*it)->m_class == "Enemy"))
            continue;
        Enemy *g_ob = dynamic_cast<Enemy *>(*it);
        auto jt = g_ob->bullets.begin();
        while (jt != g_ob->bullets.end())
        {
            if ((*jt)->get_x() > WINDOW_WIDTH || (*jt)->get_x() < 0 ||
                (*jt)->get_y() > WINDOW_HEIGHT || (*jt)->get_y() < 0 ||
                (*jt)->collision_detected(*m_static_objects) == true)
            {
                // Remove the bullet from the list
                delete *jt;
                PLAYER->health--;
                jt = g_ob->bullets.erase(jt);
            }
            else
            {
                ++jt;
            }
        }
    }

    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         ++it)
    {
        if (!((*it)->isActive()))
            continue;
        if (!((*it)->m_class == "Enemy"))
            continue;
        Enemy *g_ob = dynamic_cast<Enemy *>(*it);

        auto jt = m_state->getPlayer()->bullets.begin();
        while (jt != m_state->getPlayer()->bullets.end())
        {
            if ((*jt)->get_x() > WINDOW_WIDTH || (*jt)->get_x() < 0 ||
                (*jt)->get_y() > WINDOW_HEIGHT || (*jt)->get_y() < 0 ||
                (*jt)->collision_detected(*m_static_objects) == true)
            {
                // Remove the bullet from the list
                delete *jt;
                g_ob->health--;
                if (g_ob->health == 0)
                {
                    it = m_dynamic_objects->erase(it);
                    delete g_ob;
                }
                jt = m_state->getPlayer()->bullets.erase(jt);
            }
            else
            {
                ++jt;
            }
        }
    }
    // Sword collisions

    // Player, Enemy obstacle collisions
    for (GameObject *s_ob : *m_static_objects)
    {
        if (!(s_ob->m_class == "Obstacle"))
            continue;
        Obstacle *ob = dynamic_cast<Obstacle *>(s_ob);
        if (m_state->getPlayer()->intersect(*ob))
        {
            float belowCorrection = m_state->getPlayer()->intersectDown(*ob);
            if (belowCorrection != 0 && m_state->getPlayer()->jumping == true &&
                m_state->getPlayer()->velocityY <= 0)
            {
                // std::cout << "belowCorrection: "<<belowCorrection <<
                // std::endl;
                m_state->getPlayer()->m_pos_y -= belowCorrection;
                m_state->getPlayer()->sword_right->m_pos_y -= belowCorrection;
                m_state->getPlayer()->sword_left->m_pos_y -= belowCorrection;
                m_state->getPlayer()->velocityY = 0;
            }
        }
        for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
             ++it)
        {
            if (!((*it)->isActive()))
                continue;
            if (!((*it)->m_class == "Enemy"))
                continue;
            Enemy *g_ob = dynamic_cast<Enemy *>(*it);
            if (g_ob->intersect(*ob))
            {
                float belowCorrection = g_ob->intersectDown(*ob);
                if (belowCorrection != 0 && g_ob->jumping == true &&
                    g_ob->velocityY <= 0)
                {
                    // std::cout << "belowCorrection: "<<belowCorrection <<
                    // std::endl;
                    g_ob->m_pos_y -= belowCorrection;
                    g_ob->sword_right->m_pos_y -= belowCorrection;
                    g_ob->sword_left->m_pos_y -= belowCorrection;
                    g_ob->velocityY = 0;
                }
            }
        }
    }

    // Player <-> Enemy collisions (we move Enemy)
    // we are ignoring Enemy <-> Enemy collisions since they're on the same
    // "team"

    for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
         ++it)
    {
        if (!((*it)->isActive()))
            continue;
        if (!((*it)->m_class == "Enemy"))
            continue;
        Enemy *g_ob = dynamic_cast<Enemy *>(*it);
        if (g_ob->intersect(*m_state->getPlayer()))
        {
            float horizCorrection =
                g_ob->intersectSideways(*m_state->getPlayer());
            if (horizCorrection != 0)
            {
                g_ob->m_pos_x += horizCorrection;
                g_ob->sword_right->m_pos_x += horizCorrection;
                g_ob->sword_left->m_pos_x += horizCorrection;
            }
        }
    }

    for (GameObject *s_ob : *m_static_objects)
    {
        if (!(s_ob->m_class == "Obstacle"))
            continue;
        Obstacle *ob = dynamic_cast<Obstacle *>(s_ob);
        if (m_state->getPlayer()->intersect(*ob))
        {
            float vertCorrection = m_state->getPlayer()->intersectAbove(*ob);
            if (vertCorrection != 0)
            {
                m_state->getPlayer()->m_pos_y += vertCorrection;
                m_state->getPlayer()->sword_right->m_pos_y += vertCorrection;
                m_state->getPlayer()->sword_left->m_pos_y += vertCorrection;
                m_state->getPlayer()->velocityY = 0;
                m_state->getPlayer()->jumping = false;
            }
        }
        for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
             ++it)
        {
            if (!((*it)->isActive()))
                continue;
            if (!((*it)->m_class == "Enemy"))
                continue;
            Enemy *g_ob = dynamic_cast<Enemy *>(*it);
            if (g_ob->intersect(*ob))
            {
                float vertCorrection = g_ob->intersectAbove(*ob);
                if (vertCorrection != 0)
                {
                    g_ob->m_pos_y += vertCorrection;
                    g_ob->sword_right->m_pos_y += vertCorrection;
                    g_ob->sword_left->m_pos_y += vertCorrection;
                    g_ob->velocityY = 0;
                    g_ob->jumping = false;
                }
            }
        }
    }
    for (GameObject *s_ob : *m_static_objects)
    {
        if (!(s_ob->m_class == "Obstacle"))
            continue;
        Obstacle *ob = dynamic_cast<Obstacle *>(s_ob);
        if (m_state->getPlayer()->intersect(*ob))
        {
            float horizCorrection =
                m_state->getPlayer()->intersectSideways(*ob);
            if (horizCorrection != 0)
            {
                m_state->getPlayer()->m_pos_x += horizCorrection;
                m_state->getPlayer()->sword_right->m_pos_x += horizCorrection;
                m_state->getPlayer()->sword_left->m_pos_x += horizCorrection;
            }
        }
        for (auto it = m_dynamic_objects->begin(); it != m_dynamic_objects->end();
             ++it)
        {
            if (!((*it)->isActive()))
                continue;
            if (!((*it)->m_class == "Enemy"))
                continue;
            Enemy *g_ob = dynamic_cast<Enemy *>(*it);
            if (g_ob->intersect(*ob))
            {
                float horizCorrection = g_ob->intersectSideways(*ob);
                if (horizCorrection != 0)
                {
                    g_ob->m_pos_x += horizCorrection;
                    g_ob->sword_right->m_pos_x += horizCorrection;
                    g_ob->sword_left->m_pos_x += horizCorrection;
                }
            }
        }
    }
    /*
    for (auto& block : m_static_objects)
    {
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectDown(*block))
            {
                    m_state->getPlayer()->m_pos_y += offset;

                    // add sound event
                    if (m_state->getPlayer()->velocityY > 1.0f)
                            graphics::playSound(m_state->getFullAssetPath("Metal2.wav"),
    1.0f);

                    m_state->getPlayer()->velocityY = 0.0f;

                    break;
            }
    }

    for (auto& block : m_static_objects)
    {
            float offset = 0.0f;
            if (offset = m_state->getPlayer()->intersectSideways(*block))
            {
                    m_state->getPlayer()->m_pos_x += offset;

                    m_state->getPlayer()->m_vx = 0.0f;
                    break;
            }

    }
    */
}