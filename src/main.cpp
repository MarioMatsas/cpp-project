#include "graphics.h"
#include "Game.h"
#include "Config.h"

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->update();
}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game game;
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MK X");

    graphics::setUserData(&game);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    game.init();
    graphics::startMessageLoop();

    draw();

    return 0;
}