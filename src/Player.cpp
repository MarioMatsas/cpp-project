#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"
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
#include "util.h"
#include <cstdio>
#include <iostream>

/*
Player::Player()
{

}
*/
// MOUSE POSITION WHEN WINDOW SIZE CHANGES NEEDS TO BE FIXED!!!!!!!!!!!

Player::Player(float x, float y, float w, float h, std::string name) : Box(x, y, w, h), GameObject(name, "Player"), m_initial_x(x), m_initial_y(y)
{
	// Movement sprites
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "2.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "3.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "4.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "5.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "2_left.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "3_left.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "4_left.png");
	sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "5_left.png");

	// Standing sprites
	standing_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "6.png");
	standing_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "6_left.png");

	// Attack sprites
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "7.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "8.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "9.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "10.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "11.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "12.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "13.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "14.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "7_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "8_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "9_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "10_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "11_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "12_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "13_left.png");
	attack_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "14_left.png");

	// Jumping sprites
	jumping_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "15.png");
	jumping_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "16.png");
	jumping_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "15_left.png");
	jumping_sprites.push_back(std::string(ASSET_PATH) + "/" + name + "/" + "16_left.png");
}

Player::~Player()
{
	delete sword_left;
	delete sword_right;

	auto s_it = this->sword_hits.begin();
	while (s_it != this->sword_hits.end())
	{
		delete* s_it;
		this->sword_hits.pop_front();
		s_it = this->sword_hits.begin();
	}
	sword_hits.clear();

	for (auto arrow : arrows)
		delete arrow;
}

void Player::setPos(int x, int y) {
	this->m_pos_x = x;
	this->m_pos_y = y;
}

void Player::update(float dt)
{

	/*
	for (Arrow* arrow : arrows) {
		if (arrow->get_x() > 700 || arrow->get_x() < 0 || arrow->get_y() > 450 || arrow->get_y() < 0 || arrow->collision_detected() == true) {
			std::cout << "deleted" << std::endl;
			// Remove the arrow from the active arrows vector
			auto it = std::find(arrows.begin(), arrows.end(), arrow);
			arrows.erase(it);
			// Delete it and release the heap space
			//delete arrow;
			//arrow = nullptr;
		}

	}
	*/

	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed)
	{
		if (gun_selected && (quiver > 0) && ((GameState::getInstance()->real_window_width / GameState::getInstance()->real_window_height) > (WINDOW_WIDTH / WINDOW_HEIGHT) ? (mouse.cur_pos_x > ((GameState::getInstance()->real_window_width - GameState::getInstance()->real_canvas_width) / 2)) && (mouse.cur_pos_x < GameState::getInstance()->real_window_width + ((GameState::getInstance()->real_window_width - GameState::getInstance()->real_canvas_width) / 2)) : (mouse.cur_pos_y > ((GameState::getInstance()->real_window_height - GameState::getInstance()->real_canvas_height) / 2)) && (mouse.cur_pos_y < GameState::getInstance()->real_window_height + ((GameState::getInstance()->real_window_height - GameState::getInstance()->real_canvas_height) / 2))))
		{
			// Play the sound
			graphics::playSound(std::string(ASSET_PATH) + std::string("bow_sound.wav"), 0.8f, false);
			Arrow* b;
			if (((mouse.cur_pos_x - ((REAL_WW - REAL_CW) / 2)) * WINDOW_WIDTH) / REAL_CW - m_pos_x >= 0)
			{
				b = new Arrow(m_pos_x, m_pos_y, m_width, m_height, atan((-(((mouse.cur_pos_y - ((REAL_WH - REAL_CH) / 2)) * WINDOW_HEIGHT) / REAL_CH - m_pos_y)) / (((mouse.cur_pos_x - ((REAL_WW - REAL_CW) / 2)) * WINDOW_WIDTH) / REAL_CW - m_pos_x)), "arrow"); // WHY DOES SGG COUNT Y BACKWARDS???
			}
			else
			{
				b = new Arrow(m_pos_x, m_pos_y, m_width, m_height, M_PI + atan((-(((mouse.cur_pos_y - ((REAL_WH - REAL_CH) / 2)) * WINDOW_HEIGHT) / REAL_CH - m_pos_y)) / (((mouse.cur_pos_x - ((REAL_WW - REAL_CW) / 2)) * WINDOW_WIDTH) / REAL_CW - m_pos_x)), "arrow");
			}
			b->setMouse_x(((mouse.cur_pos_x - ((REAL_WW - REAL_CW) / 2)) * WINDOW_WIDTH) / REAL_CW);
			b->setMouse_y(((mouse.cur_pos_y - ((REAL_WH - REAL_CH) / 2)) * WINDOW_HEIGHT) / REAL_CH);
			arrows.push_back(b);
			quiver--;
		}
		else
		{
			graphics::playSound(std::string(ASSET_PATH) + std::string("sword_sound.wav"), 0.7f, false);
			if (looking_right)
			{
				sword_hits.push_back(new Box(m_pos_x + 30, m_pos_y, 25.0f, 7.0f));
			}
			else
			{
				sword_hits.push_back(new Box(m_pos_x - 30, m_pos_y, 25.0f, 7.0f));
			}
		}
		attacking = true;
	}

	if (mouse.button_right_pressed && !mouse.button_left_pressed && !attacking)
	{
		// Invert the boolean values
		sword_selected = !sword_selected;
		gun_selected = !gun_selected;
		/*
		if (sword_selected)
			std::cout << "sword" << std::endl;
		else
			std::cout << "gun" << std::endl;
		*/
	}
	/*
	if (graphics::getKeyState(graphics::SCANCODE_Q)) {
		// Invert the boolean values
		sword_selected = !sword_selected;
		gun_selected = !gun_selected;
		//if (sword_selected) std::cout << "sword" << std::endl;
		//else std::cout << "gun" << std::endl;

	}
	*/

	for (Arrow* arrow : arrows)
	{
		if (arrow->get_shot() == false)
		{
			arrow->shoot(dt);
		}

		arrow->update(dt);
		arrow->set_shot(true);
	}

	float prevPosX = m_pos_x;
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A) && !attacking)
	{
		looking_left = true;
		looking_right = false;
		move = -1.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D) && !attacking)
	{
		looking_left = false;
		looking_right = true;
		move = 1.0f;
	}
	m_vx = std::min<float>(m_max_velocity, m_vx + dt * move * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	// friction
	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	// apply static friction threshold
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	m_pos_x += m_vx * dt / 20.0f; // graphics::getDeltaTime()
	sword_right->m_pos_x += m_vx * dt / 20.0f;
	sword_left->m_pos_x += m_vx * dt / 20.0f;
	/*
	m_pos_x -= speed * graphics::getDeltaTime() / 20.0f;
	if (looking_right) sword->m_pos_x += -2 * 30;
	looking_left = true;
	looking_right = false;
	sword->m_pos_x -= speed * graphics::getDeltaTime() / 20.0f;
	*/
	/*
	m_pos_x += speed * graphics::getDeltaTime() / 20.0f;
	if (looking_left) sword->m_pos_x += 2 * 30;
	looking_left = false;
	looking_right = true;
	sword->m_pos_x += speed * graphics::getDeltaTime() / 20.0f;
	*/

	if (graphics::getKeyState(graphics::SCANCODE_W) && jumping == false && falling == false && !attacking)
	{
		velocityY = -4.0;
		jumping = true;
		// posy_dummy = posy;
	}

	// Apply gravity until terminal velocity is reached
	if (velocityY < 3.5)
		velocityY += gravity;
	m_pos_y += velocityY * dt / 10.0f;
	sword_right->m_pos_y += velocityY * dt / 10.0f;
	sword_left->m_pos_y += velocityY * dt / 10.0f;

	/*
	if (jumping) {
		if (velocityY < 3.5) velocityY += gravity;
		m_pos_y += velocityY;

		if (m_pos_y >= WINDOW_HEIGHT / 2) jumping = false;
		//posy -= up_velocity * graphics::getDeltaTime() / 7.0f;
		//up_velocity -= gravity;
		//std::cout << up_velocity << std::endl;
		//if (up_velocity <= -speed){
		//	jumping = false;
		//	up_velocity = speed;
		//}
	}
	*/
	/*
	// Check if the player collides with any of the Obstacles and perform needed changes in position
	for (Obstacle* ob : obstaclesList) {
		if (intersect(*ob)) {
			float belowCorrection = intersectDown(*ob);
			if (belowCorrection != 0 && jumping == true && velocityY <= 0) {
				//std::cout << "belowCorrection: "<<belowCorrection << std::endl;
				m_pos_y -= belowCorrection;
				sword->m_pos_y -= belowCorrection;
				velocityY = 0;
			}
		}
	}
	for (Obstacle* ob : obstaclesList) {
		if (intersect(*ob)) {
			float vertCorrection = intersectAbove(*ob);
			if (vertCorrection != 0) {
				m_pos_y += vertCorrection;
				sword->m_pos_y += vertCorrection;
				velocityY = 0;
				jumping = false;
			}

		}
	}
	for (Obstacle* ob : obstaclesList) {
		if (intersect(*ob)) {
			float horizCorrection = intersectSideways(*ob);
			if (horizCorrection != 0 && prevPosX != m_pos_x) {
				m_pos_x += horizCorrection;
				sword->m_pos_x += horizCorrection;
			}
		}
	}
	*/

	/*
	if ((posx > posx_ - width / 2 && posx < posx_ + width / 2) && (posy > posy_ - height / 2 && posy < posy_ + height / 2)) {
		if (jumping == true && up_velocity >= 0) {
			up_velocity = 0;
			posy += 1;
		}
		else if (jumping == true && up_velocity < 0) {
			jumping = false;
			falling = false;
			up_velocity = speed;
		}
		else if (posy < posy_) {
			falling = false;
		}
	}
	else {
		falling = true;
	}
	if (falling && !shot) {
		posy += gravity * graphics::getDeltaTime() / 3.0f;
	}
	*/
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(PLAYER->m_pos_x, PLAYER->m_pos_y, m_width, m_height, debug_brush);

	graphics::setFont(std::string(ASSET_PATH) + "JetBrainsMono-Thin.ttf");
	char x[10];
	char y[10];
	char x_mouse[10];
	char y_mouse[10];
	SPRINTF(x, "%5.2f", m_pos_x);
	SPRINTF(y, "%5.2f", m_pos_y);
	graphics::getMouseState(mouse);
	SPRINTF(x_mouse, "%d", ((mouse.cur_pos_x - ((REAL_WW - REAL_CW) / 2)) * WINDOW_WIDTH) / REAL_CW);
	SPRINTF(y_mouse, "%d", ((mouse.cur_pos_y - ((REAL_WH - REAL_CH) / 2)) * WINDOW_HEIGHT) / REAL_CH);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_pos_x - m_width / 2, m_pos_y + m_height / 2, 16, x, debug_brush);
	graphics::drawText(m_pos_x - m_width / 2, m_pos_y + m_height / 2 - 16, 16, y, debug_brush);
	graphics::drawText((((mouse.cur_pos_x - ((GameState::getInstance()->real_window_width - GameState::getInstance()->real_canvas_width) / 2)) * WINDOW_WIDTH) / GameState::getInstance()->real_canvas_width), ((((mouse.cur_pos_y - ((GameState::getInstance()->real_window_height - GameState::getInstance()->real_canvas_height) / 2)) * WINDOW_HEIGHT) / GameState::getInstance()->real_canvas_height)), 16, x_mouse, debug_brush);
	graphics::drawText((((mouse.cur_pos_x - ((GameState::getInstance()->real_window_width - GameState::getInstance()->real_canvas_width) / 2)) * WINDOW_WIDTH) / GameState::getInstance()->real_canvas_width) + 32, ((((mouse.cur_pos_y - ((GameState::getInstance()->real_window_height - GameState::getInstance()->real_canvas_height) / 2)) * WINDOW_HEIGHT) / GameState::getInstance()->real_canvas_height)), 16, y_mouse, debug_brush);
}

void Player::draw()
{

	// Draw Player
	graphics::Brush br;

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;
	br.outline_opacity = 0.0f;

	int sprite = previous_sprite;

	if (attacking)
	{
		if (looking_right)
		{
			if (gun_selected)
			{
				if (frameCounter < 18)
				{
					br.texture = attack_sprites[3];
				}
				else if (frameCounter < 36)
				{
					br.texture = attack_sprites[4];
				}
				else if (frameCounter < 54)
				{
					br.texture = attack_sprites[5];
				}
				else if (frameCounter < 72)
				{
					br.texture = attack_sprites[6];
				}
				else if (frameCounter < 90)
				{
					br.texture = attack_sprites[7];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
			else if (sword_selected)
			{
				if (frameCounter < 25)
				{
					br.texture = attack_sprites[0];
				}
				else if (frameCounter < 50)
				{
					br.texture = attack_sprites[1];
				}
				else if (frameCounter < 75)
				{
					br.texture = attack_sprites[2];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
		}
		else
		{
			if (gun_selected)
			{
				if (frameCounter < 18)
				{
					br.texture = attack_sprites[11];
				}
				else if (frameCounter < 36)
				{
					br.texture = attack_sprites[12];
				}
				else if (frameCounter < 54)
				{
					br.texture = attack_sprites[13];
				}
				else if (frameCounter < 72)
				{
					br.texture = attack_sprites[14];
				}
				else if (frameCounter < 90)
				{
					br.texture = attack_sprites[15];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
			else if (sword_selected)
			{
				if (frameCounter < 25)
				{
					br.texture = attack_sprites[8];
				}
				else if (frameCounter < 50)
				{
					br.texture = attack_sprites[9];
				}
				else if (frameCounter < 75)
				{
					br.texture = attack_sprites[10];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
		}
	}
	else if (jumping)
	{
		if (looking_right)
		{
			if (velocityY < 0)
			{
				br.texture = jumping_sprites[0];
			}
			else
			{
				br.texture = jumping_sprites[1];
			}
		}
		else
		{
			if (velocityY < 0)
			{
				br.texture = jumping_sprites[2];
			}
			else
			{
				br.texture = jumping_sprites[3];
			}
		}
	}

	else
	{
		if (looking_right)
		{
			if (m_vx == 0)
			{
				sprite = 0;
				br.texture = standing_sprites[sprite];
			}
			else
			{
				same_counter = 0;
				if (frameCounter < 12)
				{
					br.texture = sprites[previous_sprite];
					frameCounter++;
				}
				else
				{
					sprite = ((int)fmod(100.0f - m_pos_x * 9.0f, sprites.size()) + 7) % 4; // what the fuck are you talking about Jesse

					br.texture = sprites[sprite];

					previous_sprite = sprite;
					frameCounter = 0;
				}
			}
		}

		else
		{

			if (m_vx == 0)
			{
				sprite = 1;
				br.texture = standing_sprites[sprite];
			}
			else
			{
				same_counter = 0;
				if (frameCounter < 12)
				{
					br.texture = sprites[previous_sprite];
					frameCounter++;
				}
				else
				{
					sprite = ((int)fmod(100.0f - m_pos_x * 9.0f, sprites.size()) + 7) % 4 + 4;
					// std::cout << sprite << std::endl;
					br.texture = sprites[sprite];

					previous_sprite = sprite;
					frameCounter = 0;
				}
			}
		}
	}
	// int sprite = ((int)fmod(100.0f - m_pos_x * 9.0f, sprites.size()) + 9)%5;
	// std::cout << sprite << std::endl;

	// if he is facing to the left
	// 25.0f, 50.0f

	graphics::drawRect(m_pos_x, m_pos_y, 25.0f, 50.0f, br);

	// Draw Sword
	sword_right->draw();
	sword_left->draw();

	// Draw arrows
	for (Arrow* arrow : arrows)
	{
		arrow->draw();
	}

	if (m_state->m_debugging)
		debugDraw();
}

void Player::init()
{
	health = 6;
	quiver = 50;
	m_pos_x = m_initial_x;
	m_pos_y = m_initial_y;
	sword_right = new Sword(m_pos_x + 30, m_pos_y, 25.0f, 7.0f, "right sword");
	sword_left = new Sword(m_pos_x - 30, m_pos_y, 25.0f, 7.0f, "left sword");
}

void Player::jump()
{
}