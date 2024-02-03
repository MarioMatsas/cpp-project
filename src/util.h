#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
#define SPRINTF sprintf_s
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define SPRINTF sprintf
#endif
#elif __linux__
#define SPRINTF sprintf
#else
#error "Unknown compiler"
#endif

#define SETCOLOR(c, r, g, b) \
    {                        \
        c[0] = r;            \
        c[1] = g;            \
        c[2] = b;            \
    }
#define PLAYER m_state->getPlayer()
#define DEBUG std::cout << "here" << std::endl;
#define REAL_WW GameState::getInstance()->real_window_width
#define REAL_WH GameState::getInstance()->real_window_height
#define REAL_CH GameState::getInstance()->real_canvas_height
#define REAL_CW GameState::getInstance()->real_canvas_width