#include "graphics.h"
#include "GameState.h"

void draw()
{
    GameState::getInstance()->draw();
}

void update(float dt)
{
    GameState::getInstance()->update(dt);
}

void resize(int new_w, int new_h)
{
    GameState::getInstance()->resize(new_w, new_h);
}


int main(int argc, char** argv)
{
    graphics::createWindow(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight(), "Shadow_Wizard_Adventure");

    GameState::getInstance()->init();

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::setResizeFunction(resize);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}
