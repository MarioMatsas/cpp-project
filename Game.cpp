#include "Game.h"
#include "sgg\graphics.h"
#include "Config.h"

void Game::update(){
	if (!initialized_obstacle && graphics::getGlobalTime() > 2000) {
		obstacle1 = new Obstacle(WINDOW_WIDTH/2, 300, 700, 35);
		obstacle2 = new Obstacle(WINDOW_WIDTH/2 + 20, 300, 35, 200);
		obstacle3 = new Obstacle(WINDOW_WIDTH / 2, 100, 400, 35);
		obstacle4 = new Obstacle(WINDOW_WIDTH / 2 + 200, 300, 35, 200);
		obstacleList.push_back(obstacle1);
		obstacleList.push_back(obstacle2);
		obstacleList.push_back(obstacle3);
		obstacleList.push_back(obstacle4);
		initialized_obstacle = true;
	}
	if (!initialized_player && graphics::getGlobalTime() > 2000) {
		player = new Player(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 25, 50, obstacleList); //*this
		initialized_player = true;
	}
	
	/*
	//if (!initialized_bullet && graphics::getGlobalTime() > 2000) {
	//	bullet = new Bullet();
	//	initialized_bullet = true;
	//}
	*/
	if (player) {
		player->update();
	}

	check_colisions();
	
	if (obstacle1) {
		obstacle1->update();
	}
	if (obstacle2) {
		obstacle2->update();
	}
	if (obstacle3) {
		obstacle3->update();
	}
	if (obstacle4) {
		obstacle4->update();
	}
	/*
	//if (bullet) {
	//	bullet->update();
	//}
	*/
}

void Game::draw(){
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "background_lvl.png";
	
	graphics::drawRect(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, br);

	// Draw obstacle 
	if (obstacle1) {
		obstacle1->draw();
	}
	if (obstacle2) {
		obstacle2->draw();
	}
	if (obstacle3) {
		obstacle3->draw();
	}
	if (obstacle4) {
		obstacle4->draw();
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
{}

void Game::check_colisions()
{
	for (Obstacle* ob : obstacleList) {
		if (player->intersect(*ob)) {
			float belowCorrection = player->intersectDown(*ob);
			if (belowCorrection != 0 && player->jumping == true && player->velocityY <= 0) {
				//std::cout << "belowCorrection: "<<belowCorrection << std::endl;
				player->m_pos_y -= belowCorrection;
				player->sword_right->m_pos_y -= belowCorrection;
				player->sword_left->m_pos_y -= belowCorrection;
				player->velocityY = 0;
			}
		}
	}
	for (Obstacle* ob : obstacleList) {
		if (player->intersect(*ob)) {
			float vertCorrection = player->intersectAbove(*ob);
			if (vertCorrection != 0) {
				player->m_pos_y += vertCorrection;
				player->sword_right->m_pos_y += vertCorrection;
				player->sword_left->m_pos_y += vertCorrection;
				player->velocityY = 0;
				player->jumping = false;
			}

		}
	}
	for (Obstacle* ob : obstacleList) {
		if (player->intersect(*ob)) {
			float horizCorrection = player->intersectSideways(*ob);
			if (horizCorrection != 0) {
				player->m_pos_x += horizCorrection;
				player->sword_right->m_pos_x += horizCorrection;
				player->sword_left->m_pos_x += horizCorrection;
			}
		}
	}
}

Game::Game(){
}

Game::~Game(){
	if (player) {
		delete player;
	}
}
