#include "Bullet.h"
#include <iostream>

void Bullet::update()
{	
	if (up_right) {
		//std::cout << "v" << std::endl;
		//posy -= speed * (graphics::getDeltaTime() / 60.0f);
		//posx += speed * (graphics::getDeltaTime() / 60.0f) * (1/tangent);
		posy_b -= initialVelocityY;
		posx_b += initialVelocityX;
	}
	else if (up_left) {
		//std::cout << "e" << std::endl;
		//posy -= speed * (graphics::getDeltaTime() / 60.0f);
		//posx += speed * (graphics::getDeltaTime() / 60.0f) * (1/tangent);
		posy_b -= initialVelocityY;
		posx_b -= initialVelocityX;
	}
	else if (down_left) {
		//std::cout << "d" << std::endl;
		//posy -= speed * (graphics::getDeltaTime() / 60.0f);
		//posx += speed * (graphics::getDeltaTime() / 60.0f) * (1/tangent);
		posy_b += initialVelocityY;
		posx_b -= initialVelocityX;
	}
	else if (down_right) {
		//std::cout << "k" << std::endl;
		//posy -= speed * (graphics::getDeltaTime() / 60.0f);
		//posx += speed * (graphics::getDeltaTime() / 60.0f) * (1/tangent);
		posy_b += initialVelocityY;
		posx_b += initialVelocityX;
	}
	
	
}

void Bullet::draw()
{
	graphics::Brush br_;
	br_.fill_color[0] = 0.0f;
	br_.fill_color[1] = 0.5f;
	br_.fill_color[2] = 1.0f;
	br_.fill_opacity = 5.0f;
	br_.gradient = true;
	br_.outline_opacity = 1;
	graphics::drawDisk(posx_b, posy_b, 3.0f, br_);
	std::cout << "Ay";

}

void Bullet::init()
{
}

Bullet::~Bullet()
{
}

void Bullet::shoot()
{
	std::cout << posx_b << std::endl;
	std::cout << posy_b << std::endl;
	std::cout << mouse_x << std::endl;
	std::cout << mouse_y << std::endl;

	jumping = false;
	falling = false;
	//mouse_x = mouse.cur_pos_x;
	//mouse_y = mouse.cur_pos_y;
	float direction_x = abs(mouse_x - posx_b);
	float direction_y = abs(mouse_y - posy_b);
	length = std::sqrt(direction_x * direction_x + direction_y * direction_y);


	// Normalize the direction vector (make it a unit vector)
	direction_x = direction_x / length;
	direction_y = direction_y / length;

	// Calculate the initial velocity components
	initialVelocityX = direction_x * speed * (graphics::getDeltaTime() / 30.0f);
	initialVelocityY = direction_y * speed * (graphics::getDeltaTime() / 30.0f);

	//std::cout << initialVelocityX << std::endl;
	//std::cout << initialVelocityY << std::endl;

	tangent = abs(mouse_y - posy_b) / abs(mouse_x - posx_b);
	if (mouse_x > posx_b && mouse_y < posy_b) {
		up_right = true;
		up_left = false;
		down_right = false;
		down_left = false;
	}
	else if (mouse_x < posx_b && mouse_y < posy_b) {
		up_right = false;
		up_left = true;
		down_right = false;
		down_left = false;
	}
	else if (mouse_x > posx_b && mouse_y > posy_b) {
		up_right = false;
		up_left = false;
		down_right = true;
		down_left = false;
	}
	else if (mouse_x < posx_b && mouse_y > posy_b) {
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
	return posx_b;
}
float Bullet::get_y()
{
	return posy_b;;
}

void Bullet::set_x(float pos_x) {
	posx_b = pos_x;
}
void Bullet::set_y(float pos_y) {
	posy_b = pos_y;
}

void Bullet::set_shot(bool s)
{
	shot = true;
}

bool Bullet::get_shot()
{
	return shot;
}

bool Bullet::collision_detected(int num)
{	
	/*
	std::cout << "Hello" << std::endl;
	std::cout << game.obstacle->getX()<<std::endl;
	std::cout << "Hi" << std::endl;
	// Check if the bullet has hit an obstacle
	if ((posx_b > game.obstacle->getX() - game.obstacle->getWidth() / 2 && posx_b < game.obstacle->getX() + game.obstacle->getWidth() / 2)
		&& (posy_b > game.obstacle->getY() - game.obstacle->getHeight() / 2 && posy_b < game.obstacle->getY() + game.obstacle->getHeight() / 2)) {
		return true;
	}
	*/
	if (num == 1) return true;
	return false;
}
