#include "Player.h"
#include "graphics.h"
#include <iostream>
/*
Player::Player()
{

}
*/
Player::Player(float x, float y, float w, float h, std::vector<Obstacle*>& obstacles): Box(x, y, w, h), obstaclesList(obstacles)
{
	sword = new Sword(m_pos_x+30, m_pos_y, 25.0f, 7.0f, obstaclesList);
}

void Player::update()
{	
	auto it = bullets.begin();
	while (it != bullets.end()) {
		if ((*it)->get_x() > 700 || (*it)->get_x() < 0 || (*it)->get_y() > 450 || (*it)->get_y() < 0 || (*it)->collision_detected() == true) {
			// Remove the bullet from the list
			delete* it;
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}
	/*
	for (Bullet* bullet : bullets) {
		if (bullet->get_x() > 700 || bullet->get_x() < 0 || bullet->get_y() > 450 || bullet->get_y() < 0 || bullet->collision_detected() == true) {
			std::cout << "deleted" << std::endl;
			// Remove the bullet from the active bullets vector
			auto it = std::find(bullets.begin(), bullets.end(), bullet);
			bullets.erase(it);
			// Delete it and release the heap space
			//delete bullet;
			//bullet = nullptr;
		}

	}
	*/
	
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) {
		if (gun_selected) {
			//std::cout << "shoot" << std::endl;
			Bullet* b = new Bullet(m_pos_x, m_pos_y, m_width, m_height, obstaclesList);
			b->setMouse_x(mouse.cur_pos_x);
			b->setMouse_y(mouse.cur_pos_y);
			bullets.push_back(b);
		}
		else {
			//std::cout << "slash" << std::endl;
			bool ans = sword->collision_detected();
			//std::cout << ans << std::endl;
		}
	}

	if (graphics::getKeyState(graphics::SCANCODE_Q)) {
		// Invert the boolean values
		sword_selected = !sword_selected;
		gun_selected = !gun_selected;
		//if (sword_selected) std::cout << "sword" << std::endl;
		//else std::cout << "gun" << std::endl;

	}
	
	for (Bullet* bullet : bullets) {
		if (bullet->get_shot() == false) {
			bullet->shoot();
		}

		bullet->update();
		bullet->set_shot(true);
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		m_pos_x -= speed * graphics::getDeltaTime() / 20.0f;
		sword->m_pos_x -= speed * graphics::getDeltaTime() / 20.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		m_pos_x += speed * graphics::getDeltaTime() / 20.0f;
		sword->m_pos_x += speed * graphics::getDeltaTime() / 20.0f;
	}
	//if (graphics::getKeyState(graphics::SCANCODE_S)) {
	//	posy += speed * graphics::getDeltaTime() / 10.0f;
	//}
	
	if (graphics::getKeyState(graphics::SCANCODE_W) && jumping == false && falling == false) {
		velocityY = -6.0;
		jumping = true;
		//posy_dummy = posy;
	}

	// Apply gravity until terminal velocity is reached
	if (velocityY < 3.5) velocityY += gravity;
	m_pos_y += velocityY * graphics::getDeltaTime() / 10.0f;
	sword->m_pos_y += velocityY * graphics::getDeltaTime() / 10.0f;

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

	// Check if the player collides with any of the Obstacles and perform needed changes in position
	for (Obstacle* ob : obstaclesList) {
		if (intersect(*ob)) {
			float vertCorrection = intersectDown(*ob);
			float horizCorrection = intersectSideways(*ob);
			//std::cout << vertCorrection << std::endl;
			//std::cout << horizCorrection << std::endl;

			if (vertCorrection != 0) {
				m_pos_y += vertCorrection;
				sword->m_pos_y += vertCorrection;
				velocityY = 0;
				jumping = false;
			}
			else if (horizCorrection != 0) {
				m_pos_x += horizCorrection;
				sword->m_pos_x += horizCorrection;
			}
			 
		}
	}



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

void Player::draw()
{
	// Draw Player
	graphics::Brush br;

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.gradient = true;
	br.outline_opacity = 0;  
	graphics::drawDisk(m_pos_x, m_pos_y, 10.0f, br);

	// Draw Sword
	sword->draw();

	// Draw Bullets
	for (Bullet* bullet : bullets) {
		bullet->draw();
	}
}

void Player::init()
{
}

void Player::jump()
{

}