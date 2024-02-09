#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
#define ASSET_PATH "assets/"
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define ASSET_PATH "/Users/basil/Downloads/cpp-project/assets/"
#endif
#elif __linux__
#define ASSET_PATH "/home/basil/cpp-project/assets/"
#else
#error "Unknown compiler"
#endif

#define WINDOW_WIDTH 1024 // for reference, NES Super Mario was 256 x 240
#define WINDOW_HEIGHT 512
#define COIN_POINTS 200
#define ENEMY_POINTS 500