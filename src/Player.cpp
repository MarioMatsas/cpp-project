#include "Player.h"
#include "graphics.h"
#include <iostream>
/*
Player::Player()
{

}
*/
// MOUSE POSITION WHEN WINDOW SIZE CHANGES NEEDS TO BE FIXED!!!!!!!!!!!

Player::Player(float x, float y, float w, float h, std::string name): Box(x,y,w,h), GameObject(name, "Player")
{
	sword_right = new Sword(m_pos_x + 30, m_pos_y, 25.0f, 7.0f, "right sword");
	sword_left = new Sword(m_pos_x - 30, m_pos_y, 25.0f, 7.0f, "left sword");
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

void Player::update(float dt)
{	
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
			Bullet* b = new Bullet(m_pos_x, m_pos_y, m_width, m_height, "bullet");
			b->setMouse_x(mouse.cur_pos_x);
			b->setMouse_y(mouse.cur_pos_y);
			bullets.push_back(b);
		}
		else {
			//std::cout << "slash" << std::endl;
			//bool ans = sword_right->collision_detected();
			//std::cout << ans << std::endl;
		}
		attacking = true;
	}
	

	if (mouse.button_right_pressed && !mouse.button_left_pressed && !attacking) {
		// Invert the boolean values
		sword_selected = !sword_selected;
		gun_selected = !gun_selected;
		if (sword_selected) std::cout << "sword" << std::endl;
		else std::cout << "gun" << std::endl;
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
	
	for (Bullet* bullet : bullets) {
		if (bullet->get_shot() == false) {
			bullet->shoot();
		}

		bullet->update(dt);
		bullet->set_shot(true);
	}
	
	float prevPosX = m_pos_x;
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A) && !attacking) {
		looking_left = true;
		looking_right = false;
		move = -1.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D) && !attacking) {
		looking_left = false;
		looking_right = true;
		move = 1.0f;
	}
	m_vx = std::min<float>(m_max_velocity, m_vx + graphics::getDeltaTime() * move * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	// friction
	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	// apply static friction threshold
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	m_pos_x += m_vx * graphics::getDeltaTime() / 20.0f;
	sword_right->m_pos_x += m_vx * graphics::getDeltaTime() / 20.0f;
	sword_left->m_pos_x += m_vx * graphics::getDeltaTime() / 20.0f;
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

	if (graphics::getKeyState(graphics::SCANCODE_W) && jumping == false && falling == false && !attacking) {
		velocityY = -3.5;
		jumping = true;
		//posy_dummy = posy;
	}

	// Apply gravity until terminal velocity is reached
	if (velocityY < 3.5) velocityY += gravity;
	m_pos_y += velocityY * graphics::getDeltaTime() / 10.0f;
	sword_right->m_pos_y += velocityY * graphics::getDeltaTime() / 10.0f;
	sword_left->m_pos_y += velocityY * graphics::getDeltaTime() / 10.0f;

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

void Player::draw()
{
	// Draw Player
	graphics::Brush br;

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;
	br.outline_opacity = 1;

	int sprite = previous_sprite;

	if (attacking) {
		if (looking_right) {
			if (gun_selected) {
				if (frameCounter < 18) {
					br.texture = attack_sprites[3];
				}
				else if (frameCounter < 36) {
					br.texture = attack_sprites[4];
				}
				else if (frameCounter < 54) {
					br.texture = attack_sprites[5];
				}
				else if (frameCounter < 72) {
					br.texture = attack_sprites[6];
				}
				else if (frameCounter < 90) {
					br.texture = attack_sprites[7];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
			else if (sword_selected) {
				if (frameCounter < 25) {
					br.texture = attack_sprites[0];
				}
				else if (frameCounter < 50) {
					br.texture = attack_sprites[1];
				}
				else if (frameCounter < 75) {
					br.texture = attack_sprites[2];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
		}
		else {
			if (gun_selected) {
				if (frameCounter < 18) {
					br.texture = attack_sprites[11];
				}
				else if (frameCounter < 36) {
					br.texture = attack_sprites[12];
				}
				else if (frameCounter < 54) {
					br.texture = attack_sprites[13];
				}
				else if (frameCounter < 72) {
					br.texture = attack_sprites[14];
				}
				else if (frameCounter < 90) {
					br.texture = attack_sprites[15];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
			else if (sword_selected) {
				if (frameCounter < 25) {
					br.texture = attack_sprites[8];
				}
				else if (frameCounter < 50) {
					br.texture = attack_sprites[9];
				}
				else if (frameCounter < 75) {
					br.texture = attack_sprites[10];
					frameCounter = 0;
					attacking = false;
				}
				frameCounter++;
			}
		}

	}
	else if (jumping) {
		if (looking_right) {
			if (velocityY < 0) {
				br.texture = jumping_sprites[0];
			}
			else {
				br.texture = jumping_sprites[1];
			}
		}
		else {
			if (velocityY < 0) {
				br.texture = jumping_sprites[2];
			}
			else {
				br.texture = jumping_sprites[3];
			}
		}
	}

	else {
		if (looking_right) {
			if (m_vx == 0) {
				sprite = 0;
				br.texture = standing_sprites[sprite];
			}
			else {
				same_counter = 0;
				if (frameCounter < 12) {
					br.texture = sprites[previous_sprite];
					frameCounter++;
				}
				else {
					sprite = ((int)fmod(100.0f - m_pos_x * 9.0f, sprites.size()) + 7) % 4;
					//std::cout << sprite << std::endl;

					br.texture = sprites[sprite];

					previous_sprite = sprite;
					frameCounter = 0;
				}
			}

		}

		else {

			if (m_vx == 0) {
				sprite = 1;
				br.texture = standing_sprites[sprite];
			}
			else {
				same_counter = 0;
				if (frameCounter < 12) {
					br.texture = sprites[previous_sprite];
					frameCounter++;
				}
				else {
					sprite = ((int)fmod(100.0f - m_pos_x * 9.0f, sprites.size()) + 7) % 4 + 4;
					//std::cout << sprite << std::endl;

					br.texture = sprites[sprite];

					previous_sprite = sprite;
					frameCounter = 0;
				}
			}
		}
	}
	//int sprite = ((int)fmod(100.0f - m_pos_x * 9.0f, sprites.size()) + 9)%5;
	//std::cout << sprite << std::endl;

	// if he is facing to the left
	//25.0f, 50.0f

	graphics::drawRect(m_pos_x, m_pos_y, 25.0f, 50.0f, br);

	// Draw Sword
	sword_right->draw();
	sword_left->draw();

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
