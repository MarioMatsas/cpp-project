#pragma once

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}
#define PLAYER m_state->getPlayer()
#define DEBUG std::cout << "here" << std::endl;
#define REAL_WW GameState::getInstance()->real_window_width
#define REAL_WH GameState::getInstance()->real_window_height
#define REAL_CH GameState::getInstance()->real_canvas_height
#define REAL_CW GameState::getInstance()->real_canvas_width