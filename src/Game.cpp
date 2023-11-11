#include "Game.h"
#include "graphics.h"
#include "Config.h"

void Game::update(){
	if (!initialized_player && graphics::getGlobalTime() > 2000) {
		player = new Player(*this);
		initialized_player = true;
	}
	if (!initialized_obstacle && graphics::getGlobalTime() > 2000) {
		obstacle = new Obstacle();
		initialized_obstacle = true;
	}
	//if (!initialized_bullet && graphics::getGlobalTime() > 2000) {
	//	bullet = new Bullet();
	//	initialized_bullet = true;
	//}

	if (player) {
		player->update();
	}
	if (obstacle) {
		obstacle->update();
	}
	//if (bullet) {
	//	bullet->update();
	//}
}

void Game::draw(){
	//graphics::Brush br;

	//br.texture = std::string(ASSET_PATH) + "project_background_image_asset.jpg";

	//graphics::drawRect(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, br);

	// Draw obstacle 
	if (obstacle) {
		obstacle->draw();
	}
	// Draw player
	if (player) {
		player->draw();
	}

	// Draw player
	//if (bullet) {
	//	bullet->draw();
	//}
}

void Game::init()
{
}

Game::Game(){
}

Game::~Game(){
	if (player) {
		delete player;
	}
}
