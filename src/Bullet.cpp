#include "Bullet.h"
#include "Level.h"
#include <iostream>

void Bullet::update(float dt)
{
	// Depending on the positionof the players mouse, we change the position of the bullet to simulate it's firing
	if (up_right) {
		m_pos_y -= initialVelocityY;
		m_pos_x += initialVelocityX;
	}
	else if (up_left) {
		m_pos_y -= initialVelocityY;
		m_pos_x -= initialVelocityX;
	}
	else if (down_left) {
		m_pos_y += initialVelocityY;
		m_pos_x -= initialVelocityX;
	}
	else if (down_right) {
		m_pos_y += initialVelocityY;
		m_pos_x += initialVelocityX;
	}
}

void Bullet::draw()
{
	//std::cout << " drawn " << std::endl;
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.5f;
	br.fill_opacity = 1.0f;
	br.gradient = true;
	br.outline_opacity = 1;
	br.texture = std::string(ASSET_PATH) + "output-onlinepngtools (17).png";
	graphics::drawDisk(m_pos_x, m_pos_y, 5.0f, br);
}

void Bullet::init()
{
}

Bullet::Bullet(float x, float y, float w, float h, std::string name) : Box(x, y, w, h), GameObject(name)
{
}

Bullet::~Bullet()
{
}

void Bullet::shoot()
{
	float direction_x = abs(mouse_x - m_pos_x);
	float direction_y = abs(mouse_y - m_pos_y);
	length = std::sqrt(direction_x * direction_x + direction_y * direction_y);


	// Normalize the direction vector (make it a unit vector)
	direction_x = direction_x / length;
	direction_y = direction_y / length;

	// Calculate the initial velocity components
	initialVelocityX = direction_x * speed * (graphics::getDeltaTime() / 30.0f);
	initialVelocityY = direction_y * speed * (graphics::getDeltaTime() / 30.0f);

	//std::cout << initialVelocityX << std::endl;
	//std::cout << initialVelocityY << std::endl;

	tangent = abs(mouse_y - m_pos_y) / abs(mouse_x - m_pos_x); \

		// We set as true only the quadrant in which the mouse cursor is located
		if (mouse_x > m_pos_x && mouse_y < m_pos_y) {
			up_right = true;
			up_left = false;
			down_right = false;
			down_left = false;
		}
		else if (mouse_x < m_pos_x && mouse_y < m_pos_y) {
			up_right = false;
			up_left = true;
			down_right = false;
			down_left = false;
		}
		else if (mouse_x > m_pos_x && mouse_y > m_pos_y) {
			up_right = false;
			up_left = false;
			down_right = true;
			down_left = false;
		}
		else if (mouse_x < m_pos_x && mouse_y > m_pos_y) {
			up_right = false;
			up_left = false;
			down_right = false;
			down_left = true;
		}

}

void Bullet::setMouse_x(float pos_x)
{
	mouse_x = pos_x;
}

void Bullet::setMouse_y(float pos_y)
{
	mouse_y = pos_y;
}

float Bullet::get_x()
{
	return m_pos_x;
}
float Bullet::get_y()
{
	return m_pos_y;
}

void Bullet::set_shot(bool s)
{
	shot = true;
}

bool Bullet::get_shot()
{
	return shot;
}

bool Bullet::collision_detected(std::vector<Obstacle*>& m_blocks)
{
	// Check for any collion with Obstacles
	for (Obstacle* ob : m_blocks) {
		if (intersect(*ob)) {
			return true;
		}
	}
	return false;
}

