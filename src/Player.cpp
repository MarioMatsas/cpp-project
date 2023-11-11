#include "Player.h"
#include "Bullet.h"
#include "graphics.h"
#include "Game.h"
#include <iostream>
Player::Player(const Game& mygame)
	:game(mygame)
{
	
}
void Player::update()
{
	std::cout << game.initialized_player<< std::endl;
	for (Bullet* bullet : bullets) {
		if (bullet->get_x() > 450 || bullet->get_x() < 0 || bullet->get_y() > 700 || bullet->get_y() < 0 || bullet->collision_detected(1) == true) {
			// Remove the bullet from the active bullets vector
			auto it = std::find(bullets.begin(), bullets.end(), bullet);
			bullets.erase(it);
			// Delete it and release the heap space
			delete bullet;
			//bullet = nullptr;
		}

	}
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		b = new Bullet();
		b->setMouse_x(mouse.cur_pos_x);
		b->setMouse_y(mouse.cur_pos_y);
		b->set_x(posx);
		b->set_y(posy);
		bullets.push_back(b);
		//std::cout << mouse.cur_pos_x << std::endl;
		//std::cout << mouse.cur_pos_y << std::endl;
		//shoot();
	}
	for (Bullet* bullet : bullets) {
		if (bullet->get_shot() == false) {
			bullet->shoot();
		}

		bullet->update();
		bullet->set_shot(true);
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		posx -= speed*graphics::getDeltaTime()/20.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		posx += speed * graphics::getDeltaTime()/20.0f;
	}
	//if (graphics::getKeyState(graphics::SCANCODE_S)) {
	//	posy += speed * graphics::getDeltaTime() / 10.0f;
	//}
	if (graphics::getKeyState(graphics::SCANCODE_W) && jumping == false  && falling == false) {
		jumping = true;
		//posy_dummy = posy;
	}
	if (jumping) {
		posy -= up_velocity * graphics::getDeltaTime() / 7.0f;
		up_velocity -= gravity;
		//std::cout << up_velocity << std::endl;
		//if (up_velocity <= -speed){
		//	jumping = false;
		//	up_velocity = speed;
		//}
	}
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
	
}

void Player::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.gradient = true;
	br.outline_opacity = 0;
	graphics::drawDisk(posx, posy, 10.0f, br);
	graphics::drawRect(300.0f, 500.0f, 20.0f, 20.0f, br);

	for (Bullet* bullet : bullets) {
		bullet->draw();
	}
}

void Player::init()
{
}
